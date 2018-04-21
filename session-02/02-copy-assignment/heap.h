#ifndef CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
#define CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED

#include "macro.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

typedef struct HeapElement_t {
  double coeff;
} HeapElement;

// Definition (container):
//
//   "A container is an object holding a collection of elements"
//                                     -- B. Stroustrup, TCppPL
//

class Heap
{
public:

  Heap(
    const std::string & name,
    size_t              size,
    double              base_val);

  ~Heap();

  /*
   *  "When a class is a resource handle, that is, it is responsible for
   *   an object accessed through a pointer, the default memberwise copy
   *   is typically a disaster.
   *                                            -- B. Stroustrup, TCppPL
   */
  Heap(const Heap & other);

  // int v1;
  // int v2;
  // ...
  // int v3 = v1 = v2;
  // // think:
  // int v3.=(v1.=(v2));
  // // think:
  // int v3.assign( v1.assign(v2) );
  Heap & operator=(const Heap & other);

  //
  // Heap h(...);
  // h.name() = "foo";
  // '--.---'
  //    |
  //   lhs
  //    \
  //     `---.
  //     ,---'-------------,
  inline const std::string & name() const
  {
    return _name;
  }

  inline size_t size() const
  {
    return _size;
  }

  // void treat_heap_with_respect(Heap & h) {
  //    h[34] = 34;
  // }
  //
  // void treat_heap_with_correct_pronoun(const Heap & h) {
  //    h[34] = 34;     // Nooo
  //    int v = h[34];  // OK
  // }
  //
  inline HeapElement & operator[](int index)
  {
    if (index < 0 || static_cast<int>(_size) <= index) {
      throw std::invalid_argument("index out of bounds");
    }
    return _elements[index];
  }

  inline const HeapElement & operator[](int index) const
  {
    if (index < 0 || static_cast<int>(_size) <= index) {
      throw std::invalid_argument("index out of bounds");
    }
    return _elements[index];
  }

  inline HeapElement * elements()
  {
    return _elements;
  }

  inline const HeapElement * elements() const
  {
    return _elements;
  }

private:
  std::string    _name;
  size_t         _size;

  HeapElement  * _elements = nullptr;

}; // class Heap


// =======================================================================
// Stream operators
// =======================================================================

std::ostream & operator<<(
  std::ostream             & os,
  const cpppc::HeapElement & e);

std::ostream & operator<<(
  std::ostream      & os,
  const cpppc::Heap & p);

} // namespace cpppc

#endif // CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
