#ifndef CPPPC__03__VECTOR_H__INCLUDED
#define CPPPC__03__VECTOR_H__INCLUDED

#include <exception>
#include <stdexcept>
#include <cstring>
#include <cstdlib>


namespace cpppc {

// Vector<double> vd;

// Q: Difference between `typename` and `class` here?
template <typename ElementType>
class Vector
{

  // Q: Difference between `typedef` and `using` here?
  typedef Vector<ElementType> self_t;
  typedef ElementType         value_t;

  static const int            _chunk_size = 2;

public:

  typedef value_t             value_type;

  typedef value_t *           iterator;
  typedef value_t * const     const_iterator;
  typedef value_t &           reference;

public:

  Vector() noexcept
  { }

  Vector(const self_t & other);

  // Q: Why use inline? It's a header-definition,
  //    the compiler should know what to do?
  inline ~Vector() noexcept
  {
    clear();
  }

  self_t & operator=(const self_t & rhs);

  bool operator==(const self_t & rhs) const noexcept;

  inline int size() const noexcept
  {
    return _size;
  }

  inline bool empty() const noexcept
  {
    return 0 == _size;
  }

  void clear();

  void resize(int new_size);

  void push_back(const value_t & value);

  // Q: Could we return a reference here? Compare with std::vector!
  value_type pop_back();

  inline iterator begin() const
  {
    return &(_elements[0]);
  }

  inline iterator end() const
  {
    return &(_elements[_size]);
  }

  inline reference operator[](int offset) const
  {
    return _elements[offset];
  }

  inline reference at(int offset) const
  {
    return _elements[offset];
  }

private:

  value_t * _elements = nullptr;
  int       _size     = 0;
  int       _capacity = 0;

};

} // namespace cpppc

// Q: Why include implementation instead of regular .cc -> .o compilation?
#include "vector.impl.h"

#endif // CPPPC__03__VECTOR_H__INCLUDED
