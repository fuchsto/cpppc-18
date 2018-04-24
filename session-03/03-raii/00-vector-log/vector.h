#ifndef CPPPC__03__VECTOR_H__INCLUDED
#define CPPPC__03__VECTOR_H__INCLUDED

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <cstring>
#include <cstdlib>


namespace cpppc {

template <typename ElementType>
class Vector
{

  typedef Vector<ElementType> self_t;
  typedef ElementType         value_t;

  static const int            _chunk_size = 2;

private:

  template<typename E_>
    friend std::ostream & operator<<(
      std::ostream            & os,
      const cpppc::Vector<E_> & p);

public:

  typedef value_t             value_type;

  typedef value_t *           iterator;
  typedef value_t * const     const_iterator;
  typedef value_t &           reference;

public:

  Vector() = delete;

  Vector(const std::string & name) noexcept;

  Vector(const self_t & other);

  // Q: Why use inline? It's a header-definition,
  //    the compiler should know what to do?
  ~Vector() noexcept;

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

  std::string _name     = "";
  value_t *   _elements = nullptr;
  int         _size     = 0;
  int         _capacity = 0;

};

// ========================================================================
// Stream operators
// ========================================================================

template<typename E>
std::ostream & operator<<(
  std::ostream           & os,
  const cpppc::Vector<E> & p)
{
  std::ostringstream ss;
  ss << "Vector { " << std::endl
     << "    name(\""     << p._name     << "\"),"  << std::endl
     << "    size("       << p.size()    << "),"    << std::endl
     << "    capacity("   << p._capacity << "),"    << std::endl
     << "    elements @ " << p._elements << " (" << std::endl;
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

// Q: Why include implementation instead of regular .cc -> .o compilation?
#include "vector.impl.h"

#endif // CPPPC__03__VECTOR_H__INCLUDED
