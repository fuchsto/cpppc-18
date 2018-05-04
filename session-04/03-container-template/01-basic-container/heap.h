#ifndef CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
#define CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED

#include "macro.h"

#include "heap_iterator.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

// Definition (container):
//
//   "A container is an object holding a collection of elements"
//                                     -- B. Stroustrup, TCppPL
//

template<typename Element>
class Heap
{
public:
  typedef HeapIterator<Element> iterator;

public:

  Heap(
    const std::string & name,
    size_t              size,
    Element             base_val);

  ~Heap();

  //  "When a class is a resource handle, that is, it is responsible for
  //   an object accessed through a pointer, the default memberwise copy
  //   is typically a disaster."
  //                                              -- B. Stroustrup, TCppPL
  Heap(const Heap & other);

  Heap & operator=(const Heap & other);

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
    return _elements[index];
  }

  inline const Element & operator[](int index) const {
    if (index < 0 || static_cast<int>(_size) <= index) {
      throw std::invalid_argument("index out of bounds");
    }
    return _elements[index];
  }

  inline Element * elements() {
    return _elements;
  }

  inline const Element * elements() const {
    return _elements;
  }

  iterator begin() const {
    return _begin;
  }

  iterator end() const {
    return _end;
  }

  void print() const {
    for (auto elem : *this) {
      std::cout << "element: " << elem << std::endl;
    }
  }

  // Q: Why const?
  void modify() const {
    for (auto it = begin(); it != end(); ++it) {
      *it += 2;
    }
  }

private:
  std::string            _name;
  size_t                 _size     = 0;

  Element              * _elements = nullptr;

  iterator               _begin    = iterator(*this, -1);
  iterator               _end      = iterator(*this, -1);

}; // class Heap


// =======================================================================
// Stream operators
// =======================================================================

template<typename E>
std::ostream & operator<<(
  std::ostream               & os,
  const cpppc::Heap<E>       & p);

} // namespace cpppc

#include "heap.impl.h"

#endif // CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
