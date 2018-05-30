/**
 *  Most useful advice for you at this point:
 *  
 *     When introducing any new type, just pretend
 *     it already exists. Which expressions would
 *     it support?
 *     This will reveal which methods and type
 *     definitions are required
 *
 */

#include <functional>
#include <iterator>
#include <algorithm>
#include <stdexcept>


namespace cpppc {

namespace detail {

template <class LazySequence>
class lazy_sequence_iterator {
    using self_t            = lazy_sequence_iterator;
    using lazy_sequence_t   = LazySequence;
  public:
    using iterator_category = std::random_access_iterator_tag;
    using size_type         = std::size_t;
    using difference_type   = typename std::make_signed<
                                         size_type
                                       >::type;
    using value_type        = typename lazy_sequence_t::value_type;
    using reference         = const value_type &;
    using pointer           = const value_type *;
    using const_reference   = const value_type &;
    using const_pointer     = const value_type *;
  public:
    lazy_sequence_iterator() = default;
    lazy_sequence_iterator(const lazy_sequence_t & seq, int pos)
      : _seq(&seq),
        _pos(pos)
    { }

    bool operator==(const self_t & rhs) const {
      return _pos == rhs._pos &&
             _seq == rhs._seq;
    }

    bool operator!=(const self_t & rhs) const {
      return !(*this == rhs);
    }

    value_type operator*() const {
      return (*_seq)[_pos];
    }

    self_t & operator+=(int offset) { 
      _pos += offset;
      return *this;
    }

    self_t & operator++(int) { 
      _pos++;
      return *this;
    }

    self_t operator++() { 
      auto old = *this;
      _pos++;
      return old;
    }

    self_t operator+(int offset) const { 
      auto it = *this;
      it += offset;
      return it;
    }

    self_t & operator-=(int offset) { 
      _pos -= offset;
      return *this;
    }

    self_t & operator--(int) { 
      _pos--;
      return *this;
    }

    self_t operator--() { 
      auto old = *this;
      _pos--;
      return old;
    }

    self_t operator-(int offset) const { 
      auto it = *this;
      it -= offset;
      return it;
    }

    difference_type operator-(const self_t & rhs) const { 
      return _pos - rhs._pos;
    }

  private:
    const lazy_sequence_t * _seq = nullptr;
    int                     _pos = 0;
};

} // namespace detail

template <class T>
class lazy_sequence
{
    using self_t            = lazy_sequence<T>;

  public:
    using size_type         = std::size_t;
    using difference_type   = typename std::make_signed<
                                         size_type
                                       >::type;
    using value_type        = T;
    using iterator          = detail::lazy_sequence_iterator<self_t>;
    using const_iterator    = iterator;

  public:
    lazy_sequence()                        = default;
    lazy_sequence(const self_t & other)    = default;
    lazy_sequence(self_t && other)         = default;

    self_t & operator=(const self_t & rhs) = default;
    self_t & operator=(self_t && rhs)      = default;

    lazy_sequence(int size, std::function<T(int)> fun)
      : _size(size)
      , _fun(fun)
    { }

  public:
    T operator[](int pos) const {
      return _fun(pos);
    }

    T at(int pos) const {
      if (pos < 0 || pos >= _size) {
        throw std::out_of_range("index out of range");
      }
      return _fun(pos);
    }

    T front() const {
      return _fun(0);
    }

    T back() const {
      return _fun(size() - 1);
    }

    iterator begin() const {
      return iterator(*this, 0);
    }

    iterator end() const {
      return iterator(*this, _size);
    }

    size_type size() const {
      return _size;
    }

    bool empty() const {
      return size() == 0;
    }

    bool operator==(const self_t & rhs) const {
      return ( _size == rhs._size ) &&
             std::equal(begin(), end(), rhs.begin());
    }

    bool operator!=(const self_t & rhs) const {
      return !(*this == rhs);
    }

  private:
    int                   _size = 0;
    std::function<T(int)> _fun;
};

} // namespace cpppc
