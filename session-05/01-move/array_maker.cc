
#include "array_wrapper.h"
#include "array_maker.h"

ArrayWrapper<int>
return_array_by_value(
  int         size,
  std::string name)
{
  if (size % 2 == 0) {
    return ArrayWrapper<int>(size / 2, name);
  } else {
    return ArrayWrapper<int>(size * 2, name);
  }
}

int
accept_array_by_value(
  ArrayWrapper<int> a)
{
  ArrayWrapper<int> mine(std::move(a));

  mine.begin()[0] = 345;

  return mine.begin()[0];
}
