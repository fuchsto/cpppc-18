#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

#include <map>


namespace cpppc {

namespace detail {

template <class SparseArrayT>
class sparse_array_proxy_ref;

template <class SparseArrayT>
class sparse_array_iterator {
  using self_t    = sparse_array_iterator<SparseArrayT>;
  using element_t = typename SparseArrayT::value_t;

 public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type   = typename SparseArrayT::difference_type;
  using value_type        = element_t;
  using pointer           = element_t *;
  using reference         = element_t &;
  using proxy_reference_t = sparse_array_proxy_ref<SparseArrayT>;

 public:
  sparse_array_iterator() = delete;
  sparse_array_iterator(SparseArrayT & sarr, difference_type pos)
      : _sarr(&sarr), _pos(pos) {}

  inline proxy_reference_t operator*() {
    return proxy_reference_t(*_sarr, _pos);
  }

  inline const element_t &operator*() const {
    return _sarr->_cgetValueOrDefault(_pos);
  }

  inline self_t &operator++() {
    ++_pos;
    return *this;
  }

  inline self_t &operator--() {
    --_pos;
    return *this;
  }

  inline self_t operator++(int) {
    self_t copy(*this);
    ++_pos;
    return copy;
  }
  inline self_t operator--(int) {
    self_t copy(*this);
    --_pos;
    return copy;
  }
  inline self_t operator+(const int &n) {
    self_t copy(*this);
    copy._pos += n;
    return copy;
  }
  inline self_t operator-(const int &n) {
    self_t copy(*this);
    copy._pos -= n;
    return copy;
  }
  inline difference_type operator-(const self_t &rhs) const {
    return _pos - rhs._pos;
  }

  inline self_t &operator+=(const difference_type n) {
    _pos += n;
    return *this;
  }
  inline self_t &operator-=(const difference_type n) {
    _pos -= n;
    return *this;
  }
  inline self_t &operator=(const self_t &other) {
    _pos = other._pos;
    return *this;
  }

  inline self_t operator[](int offset) const {
    return *(*this + offset);
  }

  // Comparison
  inline bool operator==(const self_t &other) const {
    return (_sarr == other._sarr && _pos == other._pos);
  }
  inline bool operator!=(const self_t &other) const {
    return !(_sarr == other._sarr && _pos == other._pos);
  }
  inline bool operator<=(const self_t &other) const {
    return _pos <= other._pos;
  }
  inline bool operator<(const self_t &other) const {
    return _pos < other._pos;
  }
  inline bool operator>=(const self_t &other) const {
    return _pos >= other._pos;
  }
  inline bool operator>(const self_t &other) const {
    return _pos > other._pos;
  }

 private:
  SparseArrayT * _sarr = nullptr;
  size_t         _pos  = 0;
};

template <class SparseArrayT>
class sparse_array_proxy_ref {
  typedef sparse_array_proxy_ref<SparseArrayT> self_t;
  using element_t = typename SparseArrayT::value_t;
  using index_t   = typename SparseArrayT::difference_type;

 private:
  SparseArrayT & _sarr;
  index_t        _pos;

 public:
  sparse_array_proxy_ref() = delete;
  sparse_array_proxy_ref(SparseArrayT &sarr, const index_t &pos)
    : _sarr(sarr), _pos(pos) {}
  sparse_array_proxy_ref(self_t && other) = default;
  self_t & operator=(self_t && other) {
    if (this == &other) {
      return *this;
    }
    _sarr[_pos] = static_cast<element_t>(other._sarr[other._pos]);
    _pos        = other._pos;
    return *this;
  }
  sparse_array_proxy_ref(const self_t &other) = delete;
  self_t &operator=(const self_t &other) = delete;

  self_t &operator=(const element_t &t) {
    if (t != _sarr._default_value) {
      _sarr._values[_pos] = t;
    } else {
      _sarr._values.erase(_pos);
    }
    return *this;
  }

  operator element_t() const {
    element_t ret = _sarr._cgetValueOrDefault(_pos);
    return ret;
  }

  bool operator==(const self_t &other) const {
    if (this == &other) {
      return true;
    }
    if (_pos != other._pos) {
      return false;
    }
    return static_cast<element_t>(*this) == static_cast<element_t>(other);
  }
  bool operator!=(const self_t &other) const { return !(*this == other); }

  template <class T1, class T2>
  friend inline void swap(sparse_array_proxy_ref<T1> &&first,
                          sparse_array_proxy_ref<T2> &&second);
};

template <class T1, class T2>
inline void swap(sparse_array_proxy_ref<T1> &&first,
                 sparse_array_proxy_ref<T2> &&second) {
  typedef typename T1::value_t value_t;
  value_t                      vfirst  = first;
  value_t                      vsecond = second;
  if (vfirst == vsecond) {
    return;
  }

  const auto pfirst  = first._pos;
  const auto psecond = second._pos;
  first._sarr[pfirst]   = vsecond;
  second._sarr[psecond] = vfirst;
  return;
}

}  // namespace detail

template <class T, std::size_t N>
class sparse_array {
  typedef sparse_array<T, N> self_t;
  typedef int                                    index_t;
  typedef T                                      element_t;

 public:
  typedef index_t                                     difference_type;

  typedef T                                           value_type;

  typedef detail::sparse_array_iterator<self_t>       iterator;
  typedef detail::sparse_array_iterator<const self_t> const_iterator;

  typedef detail::sparse_array_proxy_ref<self_t>      reference;
  typedef const T &                                   const_reference;

  friend iterator;
  friend const_iterator;
  friend reference;

 public:
  T _getValueOrDefault(const size_t pos) {
    auto &it = _values.find(pos);
    if (it == _values.end()) {
      return _default_value;
    }
    return std::get<1>(*it);
  }

  const T &_cgetValueOrDefault(const size_t pos) const {
    const auto &it = _values.find(pos);
    if (it == _values.end()) {
      return _default_value;
    }
    return std::get<1>(*it);
  }

 private:
  template <typename Compare = std::less<T>>
  bool _compare(const self_t &other, Compare comp = Compare()) const {
    if (_default_value != other._default_value) {
      return comp(_default_value, other._default_value);
    }
    auto myit = _values.cbegin();
    auto otit = other._values.cbegin();
    while (myit != _values.end() && otit != other._values.end()) {
      if (std::get<0>(*myit) == std::get<0>(*otit)) {
        auto mval = std::get<1>(*myit);
        auto oval = std::get<1>(*otit);
        if (mval != oval) {
          return comp(mval, oval);
        }
      } else {
        if (std::get<0>(*myit) < std::get<0>(*otit)) {
          return comp(std::get<1>(*myit), other._default_value);
        } else {
          return comp(_default_value, std::get<1>(*otit));
        }
      }
      ++myit;
      ++otit;
    }
    if (myit != _values.end()) {
      return comp(std::get<1>(*myit), other._default_value);
    } else if (otit != other._values.end()) {
      return comp(_default_value, std::get<1>(*otit));
    }
    // empty containers
    return comp(0, 0);
  }

 private:
  std::map<size_t, T> _values;
  T              _default_value = 0;
  iterator       _begin         = iterator(*this, 0);
  iterator       _end           = iterator(*this, N);
  const_iterator _cbegin        = const_iterator(*this, 0);
  const_iterator _cend          = const_iterator(*this, N);

 public:
  bool operator==(const self_t &other) const {
    if (this == &other) {
      return true;
    }
    if (_default_value != other._default_value) {
      return false;
    }
    return _values == other._values;
  }
  bool operator!=(const self_t &other) const {
    return !(*this == other);
  }
  bool operator<=(const self_t &other) const {
    return _compare<std::less_equal<T>>(other);
  }
  bool operator>=(const self_t &other) const {
    return _compare<std::greater_equal<T>>(other);
  }
  bool operator<(const self_t &other) const {
    return _compare<std::less<T>>(other);
  }
  bool operator>(const self_t &other) const {
    return _compare<std::greater<T>>(other);
  }

  const_reference at(const size_t pos) const {
    if (!(pos < N)) {
      throw std::out_of_range("index out of range");
    }
    return _cgetValueOrDefault(pos);
  }

  reference at(const size_t pos) {
    if (!(pos < N)) {
      throw std::out_of_range("index out of range");
    }
    return reference(*this, pos);
  }

  const_reference operator[](const size_t pos) const {
    return _cgetValueOrDefault(pos);
  }

  reference operator[](const size_t pos) {
    return reference(*this, pos);
  }

  reference       front() { return at(0); }
  const_reference front() const { return at(0); }
  reference       back() { return at(N - 1); }
  const_reference back() const { return at(N - 1); }

  // iterators
  iterator        begin() { return _begin; }
  const_iterator  begin() const { return const_iterator(*this, 0); }
  const_iterator cbegin() const { return const_iterator(*this, 0); }
  iterator       rbegin() { return --end(); }
  const_iterator rbegin() const { return --end(); }

  iterator          end() { return _end; }
  const_iterator    end() const { return const_iterator(*this, N); }
  const_iterator  &cend() const { return const_iterator(*this, N); }

  // capacity
  bool empty() const { return (N == 0); }

  size_t size() const { return N; }

  size_t max_size() const { return N; }

  // operations
  void fill(const T &value) {
    _values.clear();
    _default_value = value;
  }
};

}  // namespace cpppc

#endif  // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
