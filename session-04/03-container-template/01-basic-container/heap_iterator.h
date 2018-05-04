#ifndef HEAP_ITERATOR_H__
#define HEAP_ITERATOR_H__

#include <iterator>

namespace cpppc {

template<typename ElementType>
class Heap;


template<typename ElementType>
class HeapIterator
: public std::iterator<
           std::forward_iterator_tag,
           ElementType,
           long,
           ElementType *,
           ElementType & >
{
 private:
  typedef HeapIterator<ElementType>                   self_t;
 public:
  typedef       long                              index_type;
  typedef       ElementType                       value_type;
  typedef       ElementType &                      reference;
  typedef const ElementType &                const_reference;
  typedef       ElementType *                        pointer;
  typedef const ElementType *                  const_pointer;

 public:

  HeapIterator(
    Heap<ElementType> & heap,
    index_type          index)
  : _heap(heap),
    _idx(index)
  { }

  reference operator*() const {
    return _heap[_idx];
  }

  inline self_t & operator++() {
    ++_idx;
    return *this;
  }

  inline self_t operator++(int) {
    self_t result = *this;
    ++_idx;
    return result;
  }

  inline bool operator==(const self_t & other) const {
    return (&_heap == &(other._heap) && _idx == other._idx);
  }

  inline bool operator!=(const self_t & other) const {
    return !(*this == other);
  }

 private:
  Heap<ElementType> & _heap;
  index_type          _idx;
};

} // namespace cpppc

#endif // HEAP_ITERATOR_H__
