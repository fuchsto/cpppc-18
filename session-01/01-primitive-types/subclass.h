#ifndef CPPPC__SESSION_02__SUBCLASS_H__INCLUDED
#define CPPPC__SESSION_02__SUBCLASS_H__INCLUDED

#include "primitive.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

class Subclass : public Primitive
{
public:

  Subclass(const std::string & name, const Data & data, double factor)
  : Primitive(name, data), // delegating constructor
    _factor(factor)
  { }

  Subclass(const std::string & name, int id, double coeff, double factor)
  : Primitive(name, id, coeff), // delegating constructor
    _factor(factor)
  { }

  inline double factor() const
  {
    return _factor;
  }

private:

  double _factor;

}; // class Subclass


// =======================================================================
// Stream operators
// =======================================================================

std::ostream & operator<<(
  std::ostream          & os,
  const cpppc::Subclass & s)
{
  std::ostringstream ss;
  ss << "Subclass { " << std::endl
     << "  " << *(dynamic_cast<const cpppc::Primitive *>(&s)) << "),"
             << std::endl
     << "  factor(" << s.factor() << ") }";
  return operator<<(os, ss.str());
}

} // namespace cpppc

#endif // CPPPC__SESSION_02__SUBCLASS_H__INCLUDED
