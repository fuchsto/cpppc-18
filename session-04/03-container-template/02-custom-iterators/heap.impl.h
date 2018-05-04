#ifndef CPPPC__SESSION_02__HEAP_IMPL_H__INCLUDED
#define CPPPC__SESSION_02__HEAP_IMPL_H__INCLUDED

#include "heap.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

template<typename Element>
Heap<Element>::Heap(
  const std::string & name,
  size_t              size,
  Element             base_val)
: _name(name),
  _size(size),
  _begin(*this, 0),
  _end(*this, size)
{
  LOG("Heap", this << " Constructor (" << _name << ", " << _size << ")");

  if (_size > 0) {
    _elements = new Element[_size];
    for (size_t i = 0; i < _size; i++) {
      _elements[i] = Element {
                       base_val + static_cast<Element>(i + 1) };
    }
  }
}

template<typename Element>
Heap<Element>::~Heap()
{
  LOG("Heap", this << " Destructor  (" << _name << "), "
                   << "delete[] " << _elements);

  if (nullptr != _elements) {
    delete[] _elements;
  }
}

// Copy- and assignment operators are implicit friends.

template<typename Element>
Heap<Element>::Heap(const Heap & other)
: _name(other._name),
  _size(other._size),
  _begin(other._begin),
  _end(other._end)
{
  LOG("Heap", this << " Copy        (" << other._name << " @ " << &other
                                       << ")");
  _elements = new Element[_size];
  for (size_t i = 0; i < _size; i++) {
    _elements[i] = other._elements[i];
  }
}

template<typename Element>
Heap<Element> & Heap<Element>::operator=(const Heap & other)
{
  LOG("Heap", this << " Assign      (" << other._name << " @ " << &other
                                       << ")");
  if (this != &other) {
    _size  = other._size;
    _name  = other._name;
    _begin = other._begin;
    _end   = other._end;
    if (nullptr != _elements) {
      delete[] _elements;
    }
    if (_size > 0) {
      _elements = new Element[_size];
      for (size_t i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
      }
    }
  }
  return *this;
}


// ========================================================================
// Stream operators
// ========================================================================

template<typename E>
std::ostream & operator<<(
  std::ostream         & os,
  const cpppc::Heap<E> & p)
{
  std::ostringstream ss;
  ss << "Heap { " << std::endl
     << "    name(\""     << p.name()  << "\"),"  << std::endl
     << "    size("       << p.size()  << "),"    << std::endl
     << "    elements @ " << p.elements() << " (" << std::endl;
  for (size_t i = 0; i < p.size(); i++) {
    ss << "      " << p[i];
    if (i < p.size() - 1) {
      ss << ",";
    }
    ss << std::endl;
  }
  ss << "    )";
  return operator<<(os, ss.str());
}

} // namespace cpppc

#endif // CPPPC__SESSION_02__HEAP_IMPL_H__INCLUDED
