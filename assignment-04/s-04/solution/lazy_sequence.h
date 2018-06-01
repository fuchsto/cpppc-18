
#include <iterator>
#include <functional>
#include <algorithm>



namespace cpppc {

// Nothing better to do now, let's implement this iterator.

namespace detail {

template <class LazySequence>
class lazy_sequence_iterator {
  using self_t          = lazy_sequence_iterator<LazySequence>;
  using lazy_sequence_t = LazySequence;

public:
  // Iterators must provide (public) member types.
  // Again, just look them up on cppreference.
  using iterator_category = std::random_access_iterator_tag;
  using value_type 	      = typename LazySequence::value_type;
  using pointer           = typename LazySequence::pointer;
  using reference         = typename LazySequence::reference;
  using difference_type   = std::ptrdiff_t;

public:
  // Remember: iterators are default-constructible.
  lazy_sequence_iterator()                     = default;
  ~lazy_sequence_iterator()                    = default;

  lazy_sequence_iterator(const lazy_sequence_t & seq, int pos)
  : _seq(&seq)
  , _pos(pos)
  { }

  lazy_sequence_iterator(const self_t & other) = default;
  lazy_sequence_iterator(self_t && other)      = default;

  self_t & operator=(const self_t & rhs)       = default;
  self_t & operator=(self_t && rhs)            = default;

public:
  // No non-const variant, returning by value
  // --> no assignment
  value_type operator*() const {
    return (*_seq)[_pos];
  }
  // Same here
  value_type operator[](int offset) const {
    return (*_seq)[_pos + offset];
  }

  // Ufffzz ... here we go ... :S

  // *cracking fingers*
  
  self_t & operator++() {
    ++_pos;
    return *this;
  }
  
  self_t operator++(int) {
    auto old = *this;
    ++_pos;
    return old;
  }

  self_t & operator+=(int offset) {
    _pos += offset;
    return *this;
  }

  self_t operator+(int offset) const {
    auto it = *this;
    it += offset;
    return it;
  }

  difference_type operator-(const self_t & rhs) const {
    return _pos - rhs._pos;
  }

  bool operator==(const self_t & rhs) const {
    // These operators look always the same! (signature I mean)
    return _pos == rhs._pos && _seq == rhs._seq;
    // Nah, well, for iterators the implementation is actually
    // also unsurprising every time.
    // That's why we replace those by CRTP base iterators, right.
    //
  }

  bool operator!=(const self_t & rhs) const {
    return not (*this == rhs);
  }

private:
  const lazy_sequence_t *  _seq = nullptr;
  int                      _pos = 0;
};

}

template <class T>
class lazy_sequence {
  using self_t = lazy_sequence<T>;

public:
  using value_type      = T;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  using       iterator  = detail::lazy_sequence_iterator<const self_t>;
  using const_iterator  = detail::lazy_sequence_iterator<const self_t>;

  using       reference = const T &;
  using const_reference = const T &;
 
  using       pointer   = const T *;
  using const_pointer   = const T *;

public:
  lazy_sequence()  = default;
  ~lazy_sequence() = default;

  lazy_sequence(const self_t & other)    = default;
  lazy_sequence(self_t && other)         = default;

  self_t & operator=(const self_t & rhs) = default;
  self_t & operator=(self_t && rhs)      = default;

public:

  // Obvious from the assignment
  lazy_sequence(int size, std::function<T(int)> fun)
  : _size(size)
  , _fun(fun)
  { }

  size_type size() const {
    return _size;
  }

  bool empty() const {
    return size() == 0;
  }

  value_type front() const {
    return *begin();
  }

  value_type back() const {
    return *(begin() + _size - 1);
  }

  const_iterator begin() const {
    return const_iterator(*this, 0);
  }

  const_iterator end() const {
    return const_iterator(*this, _size);
  }

  value_type operator[](int offset) const {
    return _fun(offset);
  }

  bool operator==(const self_t & rhs) const {
    if (this == &rhs)       { return true;  }
    if (_size != rhs._size) { return false; }
    return std::equal(begin(), end(), rhs.begin());
  }

  bool operator!=(const self_t & rhs) const {
    return not (*this == rhs);
  }

private:
  int                            _size = 0;
  std::function<value_type(int)> _fun;

};

} // namespace cpppc

