#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

#include <unordered_map>
#include <limits>
#include <iterator>


namespace cpppc {

namespace detail {

// Forward-declaration
template <class SparseArrayT>
class sparse_array_proxy_ref;

// Forward-declaration
template <class SparseArrayT>
class sparse_array_iterator;


template <class SparseArrayT>
class sparse_array_iterator
{
  using self_t            = sparse_array_iterator<SparseArrayT>;
  using sparse_array_t    = SparseArrayT;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type        = typename SparseArrayT::value_type;
  using difference_type   = std::ptrdiff_t;
  using reference         = sparse_array_proxy_ref<SparseArrayT>;
                            // what about const-references?
                            // Well: SparseArrayT would be a
                            // const SparseArrayT then.
                            // With reference type:
                            //   SparseArrayT::reference
                            // =>
                            //   sparse_array_proxy_ref<const sparse_array<int, N>>
                            // So all should be well.

public:
  // Iterators must be default-constructible
  sparse_array_iterator()                     = default;
  ~sparse_array_iterator()                    = default;

  sparse_array_iterator(const self_t & other) = default;
  sparse_array_iterator(self_t && other)      = default;

  sparse_array_iterator(sparse_array_t & sa, int pos)
  : _sa(&sa), _pos(pos)
  { }

  self_t & operator=(const self_t & other)      = default;
  self_t & operator=(self_t && other)           = default;

  bool operator==(const self_t & rhs) const {
    return this == &rhs || (_sa == rhs._sa && _pos == rhs._pos);
  }

  bool operator!=(const self_t & rhs) const {
    return not (*this == rhs);
  }

  bool operator<(const self_t & rhs) const {
    return _pos < rhs._pos;
  }
  bool operator<=(const self_t & rhs) const {
    return !(*this > rhs);
  }

  bool operator>(const self_t & rhs) const {
    return _pos > rhs._pos;
  }
  bool operator>=(const self_t & rhs) const {
    return !(*this < rhs);
  }

  reference operator*() {
    return reference(*_sa, _pos);
  }

  self_t operator++(int) {
    auto old = *this;
    ++_pos;
    return old;
  }

  self_t & operator++() {
    ++_pos;
    return *this;
  }

  self_t operator--(int) {
    auto old = *this;
    --_pos;
    return old;
  }

  self_t & operator--() {
    --_pos;
    return *this;
  }

  self_t operator+(int offset) {
    auto it = *this;
    it += offset;
    return it;
  }

  self_t operator-(int offset) {
    auto it = *this;
    it -= offset;
    return it;
  }

  self_t & operator+=(int offset) {
    _pos += offset;
    return *this;
  }

  self_t & operator-=(int offset) {
    _pos -= offset;
    return *this;
  }

  reference operator[](int offset) const {
    _pos += offset;
    return *(*this);
  }

private:
  // ... and default-construction means we can't use a reference member.
  // And actually reference members are (usually) not what you want
  // anyways.
  sparse_array_t * _sa  = nullptr;
  int              _pos = 0;
};

template <class SparseArrayT>
class sparse_array_proxy_ref
{
  using self_t         = sparse_array_proxy_ref<SparseArrayT>;
  using sparse_array_t = SparseArrayT;
  using value_type     = typename SparseArrayT::value_type;

  public:
    // This type should mimic a reference, like T&.
    // So it cannot be constructed without an element if refers to.
    sparse_array_proxy_ref() = delete;

    sparse_array_proxy_ref(sparse_array_t & sa, int index)
    : _sa(sa), _index(index)
    { }

    //
    //  auto & value = (sa[1] = sa[2]) = sa[3];
    //
    //
    self_t & operator=(const value_type & rhs) {
      _sa._set_value(_index, rhs);
      return *this;
    }

    operator value_type() const {
      return _sa[_index];  // *this : const sparse_array_proxy_ref<...>
                           // _sa   : const sparse_array_t
    
    }

    //  int value_a = 12;
    //  int value_b = 12;
    //
    //  int & ref_a = value_a;
    //  int & ref_b = value_b;
    //
    //  ref_a == ref_b
    //
    bool operator==(const self_t & rhs) const {
      return (this == &rhs) ||
             static_cast<value_type>(*this) == static_cast<value_type>(rhs);
    }

  private:
    sparse_array_t & _sa;
    int              _index;
};

} // namespace detail


template <class T, std::size_t N>
class sparse_array
{
  // Just a suggestion:

  typedef sparse_array<T, N>                      self_t;
  typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
  typedef int                                     index_t;

public:
  using value_type 	           = T;
  using size_type 	           = std::size_t;
  using difference_type 	     = std::ptrdiff_t;

  using reference 	           = detail::sparse_array_proxy_ref<self_t>;
  using const_reference 	     = const T &; // Ha!

  using pointer 	             = value_type*;
  using const_pointer 	       = const value_type*;

  using iterator               = detail::sparse_array_iterator<self_t>;
  using const_iterator         = detail::sparse_array_iterator<const self_t>;
  using reverse_iterator 	     = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  friend iterator;
  friend reference;

public:
  // Using = default unless there is a reason not to.
  sparse_array()                           = default;
  ~sparse_array()                          = default;

  sparse_array(const self_t & other)       = default;
  sparse_array(self_t && other)            = default;

  self_t & operator=(const self_t & other) = default;
  self_t & operator=(self_t && other)      = default;

  bool operator==(const self_t & rhs) const {
    // Just starting off with the usual stuff ...
    return    (this == &rhs)                // identity
           || (   _default == rhs._default  // equality, member-wise
               && true // TODO
              );
    // Hm, actually looks really "default" until now.
  }

  bool operator!=(const self_t & rhs) const {
    return not (*this == rhs);
  }

  constexpr size_type max_size() const noexcept {
    return std::numeric_limits<int>::max();
  }

  constexpr size_type size() const noexcept {
    // can use constexpr as N is known at compile time
    return N;
  }

  constexpr bool empty() const noexcept {
    return size() > 0;
  }

  iterator begin() noexcept {
    return iterator(*this, 0);
  }

  const_iterator begin() const noexcept {
    return const_iterator(*this, 0);
  }

  iterator end() noexcept {
    return iterator(*this, size());
  }

  const_iterator end() const noexcept {
    return const_iterator(*this, size());
  }

  reference front() {
    return *begin();
  }

  const_reference front() const {
    return *begin();
  }

  reference back() {
    return *(begin() + size() - 1);
  }

  const_reference back() const {
    return *(begin() + size() - 1);
  }

  // Write-access:
  //
  //   sa[34] /* proxy ref */ = 324;
  //
  reference operator[](int index) {
    return reference(
             // Now, what would this proxy reference depend on ...
             // Well, we could make it depend on this sparse_array
             // instance for starters:
             *this,
             // And the index, obviously:
             index);
  }

  // Read-only-access
  //
  //   auto & val = sa[34];
  //
  const_reference operator[](int index) const {
    return _value_or_default(index);
  }

  void fill(const value_type & value) {
    // Assigning value to all values in container?
    // HELL NO.
    _values.clear();
    // All elements will have the same value after this operation,
    // so essentially we are changing the default.
    //
    // Dang, so witty.
    //
    _default = value;
  }

private:
  const_reference _value_or_default(int index) const {
    if (_values.find(index) != _values.end()) {
      return _values[index];
    }
    return _default;
  }

  void _set_value(int _index, const T & value) {
    _values[_index] = value;
  }

private:
  T                               _default;
  std::unordered_map<index_t, T>  _values;

};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
