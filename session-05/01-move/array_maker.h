#ifndef CPPPC__SESSION_07__ARRAY_MAKER_H__INCLUDED
#define CPPPC__SESSION_07__ARRAY_MAKER_H__INCLUDED

#include "array_wrapper.h"

ArrayWrapper<int>
return_array_by_value(
  int         size,
  std::string name);

int
accept_array_by_value(
  ArrayWrapper<int> a);

#endif
