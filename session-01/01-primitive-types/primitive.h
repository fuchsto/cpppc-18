#ifndef CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
#define CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

// A struct is a class where members are by default public.
typedef struct Data_t {
  int          id;
  double       coeff;
} Data;

// Definition (class):
//
//   "A class is a user-defined type provided to represent a
//    concept in the code of a program."
//                                  -- B. Stroustrup, TCppPL
//

class Primitive
{
public:

  // These are *declarations* (not definitions) of the constructor methods.

  Primitive(const std::string & name, const Data & data);

  Primitive(const std::string & name, int id, double coeff);

  inline const std::string & name() const
  {
    return _name;
  }

  inline const Data & data() const
  {
    return _data;
  }

private:
  std::string  _name;
  Data         _data = { 0, 0.0 }; // <-- in-class initializer

}; // class Primitive


// =======================================================================
// Stream operators
// =======================================================================

std::ostream & operator<<(
  std::ostream           & os,
  const cpppc::Data      & d);

std::ostream & operator<<(
  std::ostream           & os,
  const cpppc::Primitive & p);

} // namespace cpppc

#endif // CPPPC__SESSION_02__PRIMITIVE_H__INCLUDED
