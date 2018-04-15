#include "primitive.h"

#include <iostream>
#include <sstream>
#include <string>


// Definition of class methods are placed in .cc files and will be linked
// as object (.o) files.

namespace cpppc {

Primitive::Primitive(
  const std::string & name,
  const Data        & data)
: _name(name), _data(data)
{ }

Primitive::Primitive(
  const std::string & name,
  int                 id,
  double              coeff)
: _name(name), _data { id, coeff }
{ }

std::ostream & operator<<(
  std::ostream      & os,
  const cpppc::Data & d)
{
  std::ostringstream ss;
  ss << "Data { " << std::endl
     << "      id("     << d.id    << ")," << std::endl
     << "      coeff("  << d.coeff << ") }";
  return operator<<(os, ss.str());
}

std::ostream & operator<<(
  std::ostream           & os,
  const cpppc::Primitive & p)
{
  std::ostringstream ss;
  ss << "Primitive { " << std::endl
     << "    name(\"" << p.name()  << "\")," << std::endl
     << "    data("   << p.data()  << ") }";
  return operator<<(os, ss.str());
}

} // namespace cpppc
