#ifndef CPPPC__SESSION_04__BUCKET_HEAP_H__INCLUDED
#define CPPPC__SESSION_04__BUCKET_HEAP_H__INCLUDED

#include "macro.h"

#include "bucket_heap_iterator.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>


namespace cpppc {

template<typename Element>
class BucketHeap
{
public:
  typedef       BucketHeapIterator<Element>       iterator;
  typedef const BucketHeapIterator<Element> const_iterator;

  friend iterator;

private:
  typedef std::vector<Element> bucket_t;

public:

  BucketHeap(
    const std::string & name,
    size_t              size,
    Element             base_val);

  ~BucketHeap();

  BucketHeap(const BucketHeap & other);

  BucketHeap & operator=(const BucketHeap & other);

  void grow(int nelem, Element base_val);

  inline const std::string & name() const {
    return _name;
  }

  inline size_t size() const {
    return _size;
  }

  inline Element & operator[](int index) {
    if (index < 0 || static_cast<int>(_size) <= index) {
      throw std::invalid_argument("index out of bounds");
    }
    return _begin[index];
  }

  inline const Element & operator[](int index) const {
    if (index < 0 || static_cast<int>(_size) <= index) {
      throw std::invalid_argument("index out of bounds");
    }
    return _begin[index];
  }

  iterator begin() const {
    return _begin;
  }

  iterator end() const {
    return _end;
  }

private:
  std::string            _name;
  size_t                 _size          = 0;

  std::list<bucket_t>    _buckets;
  std::vector<size_t>    _bucket_sizes;

  iterator               _begin         = iterator(*this, -1);
  iterator               _end           = iterator(*this, -1);

}; // class BucketHeap


// =======================================================================
// Stream operators
// =======================================================================

template<typename E>
std::ostream & operator<<(
  std::ostream               & os,
  const cpppc::BucketHeap<E> & p);

} // namespace cpppc

#include "bucket_heap.impl.h"

#endif // CPPPC__SESSION_04__BUCKET_HEAP_H__INCLUDED
