#include "heap.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

Heap::Heap(
  const std::string & name,
  size_t              size,
  size_t              max_size,
  double              base_val)
: _name(name), _size(size)
{
  LOG("Heap", this << " Constructor (" << _name << ", " << _size << ")");

  if (_size > 0) {
    _elements = new HeapElement[_size];
    for (size_t i = 0; i < _size; i++) {
      _elements[i] = HeapElement { base_val + (i + 1) };
    }
  }
}

Heap::~Heap()
{
  LOG("Heap", this << " Destructor  (" << _name << "), "
                   << "delete[] " << _elements);

  if (nullptr != _elements) {
    delete[] _elements;
  }
}

// Copy- and assignment operators are implicit friends.

Heap::Heap(const Heap & other)
: _name(other._name), _size(other._size)
{
  LOG("Heap", this << " Copy        (" << other._name << " @ " << &other
                                       << ")");
  _elements = new HeapElement[_size];
  for (size_t i = 0; i < _size; i++) {
    _elements[i] = other._elements[i];
  }
}

Heap & Heap::operator=(const Heap & other)
{
  LOG("Heap", this << " Assign      (" << other._name << " @ " << &other
                                       << ")");
  if (this != &other) {
    _size = other._size;
    _name = other._name;
    if (nullptr != _elements) {
      delete[] _elements;
    }
    if (_size > 0) {
      _elements = new HeapElement[_size];
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

std::ostream & operator<<(
  std::ostream             & os,
  const cpppc::HeapElement & e)
{
  std::ostringstream ss;
  ss << "HeapElement { coeff(" << e.coeff << ") }";

  return operator<<(os, ss.str());
}

std::ostream & operator<<(
  std::ostream      & os,
  const cpppc::Heap & p)
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
