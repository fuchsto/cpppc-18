#ifndef CPPPC__SESSION_04__BUCKET_HEAP_IMPL_H__INCLUDED
#define CPPPC__SESSION_04__BUCKET_HEAP_IMPL_H__INCLUDED

#include "bucket_heap.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

template<typename Element>
BucketHeap<Element>::BucketHeap(
  const std::string & name,
  size_t              size,
  Element             base_val)
: _name(name),
  _begin(*this, 0),
  _end(*this, size)
{
  LOG("BucketHeap", this << " Constructor (" << name << ", "
                                             << size << ")");
  if (size > 0) {
    grow(size, base_val);
  }
}

template<typename Element>
BucketHeap<Element>::~BucketHeap()
{
  LOG("BucketHeap", this << " Destructor  (" << _name << ")");
}

// Copy- and assignment operators are implicit friends.

template<typename Element>
BucketHeap<Element>::BucketHeap(const BucketHeap & other)
: _name(other._name),
  _size(other._size),
  _begin(other._begin),
  _end(other._end)
{
  LOG("BucketHeap", this << " Copy        (" << other._name << " @ "
                                             << &other      << ")");
  // Q: Implement this!
}

template<typename Element>
BucketHeap<Element> & BucketHeap<Element>::operator=(
  const BucketHeap & other)
{
  LOG("BucketHeap", this << " Assign      (" << other._name << " @ "
                                             << &other      << ")");
  if (this != &other) {
    // Q: Implement this!
  }
  return *this;
}

template<typename Element>
void BucketHeap<Element>::grow(
  int     nelem,
  Element base_val)
{
  _buckets.push_back(bucket_t(nelem));
  _bucket_sizes.push_back(_size);
  _size += nelem;

  for (size_t i = 0; i < _size; i++) {
    _buckets.back()[i] = Element {
                           base_val + static_cast<Element>(i + 1) };
  }

  // Q: Do you see why _end is defined as iterator(-1) instead of
  //    iterator(_size)?
}


// ========================================================================
// Stream operators
// ========================================================================

template<typename E>
std::ostream & operator<<(
  std::ostream               & os,
  const cpppc::BucketHeap<E> & p)
{
  std::ostringstream ss;
  ss << "BucketHeap { " << std::endl
     << "    name(\""     << p.name()  << "\"),"  << std::endl
     << "    size("       << p.size()  << "),"    << std::endl
     << "    bucket_sizes(" << std::endl;
  for (size_t i = 0; i < p._bucket_sizes; i++) {
    ss << "      " << p._bucket_sizes[i];
    if (i < p._bucket_sizes().size() - 1) {
      ss << ",";
    }
    ss << std::endl;
  }
  ss << "    )";
  return operator<<(os, ss.str());
}

} // namespace cpppc

#endif // CPPPC__SESSION_04__BUCKET_HEAP_IMPL_H__INCLUDED
