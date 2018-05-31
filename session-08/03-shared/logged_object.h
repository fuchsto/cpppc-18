#ifndef LOGGED_OBJECT_H__INCLUDED
#define LOGGED_OBJECT_H__INCLUDED

#include <iostream>
#include <string>


template <typename ValueT>
class LoggedObject
{
  typedef LoggedObject<ValueT> self_t;

public:
  LoggedObject(std::ostream & os, ValueT val)
  : _os(os), _val(val)
  {
    log("construct");
  }

  ~LoggedObject()
  {
    log("destruct");
  }

  LoggedObject(const self_t & other)
  : _os(other._os), _val(other._val)
  {
    log("copy from", &other);
  }

  self_t & operator=(const self_t & rhs)
  {
    log("assign from", &rhs);

    _os  = rhs._os;
    _val = rhs._val;

    return *this;
  }

private:
  template <typename VarT>
  void log(std::string msg, const VarT & var)
  {
    _os << "LoggedObject @(" << this << "): " << msg << "(" << var << ")"
        << std::endl;
  }

  void log(std::string msg)
  {
    _os << "LoggedObject @(" << this << "): " << msg
        << std::endl;
  }

private:
  std::ostream & _os;
  ValueT         _val;
};

#endif // LOGGED_OBJECT_H__INCLUDED
