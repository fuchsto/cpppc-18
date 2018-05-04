#ifndef HEAP_ITERATOR_H__
#define HEAP_ITERATOR_H__

#include <iterator>

namespace cpppc {

template<typename ElementType>
class Heap;


/**
 * For specification of random access iterator concept, see:
 *
 * http://en.cppreference.com/w/cpp/concept/RandomAccessIterator
 *
 * Q: Why is the concept specified using "expressions" instead of
 *    function signatures?
 */
template<typename ElementType>
class HeapIterator {
 private:
  typedef HeapIterator<ElementType> self_t;

 public:
  // Required type definitions specified in std::iterator_traits:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = ElementType;
  using pointer           = ElementType *;
  using reference         = ElementType &;

 public:
  // Type definitions for heap iterator:
  typedef long index_type;

 public:

  HeapIterator(
    Heap<ElementType> & heap,
    index_type          index)
  : _heap(heap),
    _idx(index)
  { }

  inline reference operator*() const {
    return _heap[_idx];
  }

  inline reference operator[](int offset) const {
    return *(*this + offset);
  }

  inline self_t & operator++() {
    ++_idx;
    return *this;
  }

  inline self_t operator++(int) const {
    // Q: Remember from last session why this is bad style?
    self_t result = *this;
    ++result;
    return result;
  }

  inline self_t & operator--() {
    --_idx;
    return *this;
  }

  inline self_t operator--(int) const {
    // Q: Remember from last session why this is bad style?
    self_t result = *this;
    --result;
    return result;
  }

  inline self_t & operator+=(int offset) {
    _idx += offset;
    return *this;
  }

  inline self_t operator+(int offset) const {
    // Q: Remember from last session why this is bad style?
    self_t result = *this;
    result += offset;
    return result;
  }

  inline self_t & operator-=(int offset) {
    _idx -= offset;
    return *this;
  }

  inline self_t operator-(int offset) const {
    // Q: Remember from last session why this is bad style?
    self_t result = *this;
    result -= offset;
    return result;
  }

  inline bool operator==(const self_t & other) const {
    return (&_heap == &(other._heap) && _idx == other._idx);
  }

  inline bool operator!=(const self_t & other) const {
    // Q: What's wrong with this?
    //    Hint: the actual issue is not in this function.
    return !(*this == other);
  }

  inline bool operator<=(const self_t & other) const {
    return _idx <= other._idx;
  }

  inline bool operator<(const self_t & other) const {
    return _idx < other._idx;
  }

  inline bool operator>=(const self_t & other) const {
    return _idx >= other._idx;
  }

  inline bool operator>(const self_t & other) const {
    return _idx > other._idx;
  }

 private:
  Heap<ElementType> & _heap;
  index_type          _idx;
};

} // namespace cpppc

#endif // HEAP_ITERATOR_H__
