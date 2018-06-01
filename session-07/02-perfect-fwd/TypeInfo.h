#ifndef DASH__META__TYPE_INFO_H__INCLUDED
#define DASH__META__TYPE_INFO_H__INCLUDED

#include <string>
#include <typeinfo>

namespace internal {
  std::string demangle(const char * typeid_name);
}

/**
 * Returns string containing the type name of the given object.
 *
 * Similar to the `typeid` operator but ensures human-readable, demangled
 * format.
 */
#if 0
template <class T>
std::string typestr(const T & obj) {
  return internal::demangle(
           typeid(obj).name()
         );
}
#else
template <class T>
std::string typestr(T && obj) {
  return internal::demangle(
           typeid(obj).name()
         );
}
#endif

/**
 * Returns string containing the name of the specified type.
 *
 * Similar to the `typeid` operator but ensures human-readable, demangled
 * format.
 */
template <class T>
std::string typestr() {
  return internal::demangle(
           typeid(T).name()
         );
}

#endif // DASH__META__TYPE_INFO_H__INCLUDED
