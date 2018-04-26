#include "shared_config.h"

#include <iostream>
#include <sstream>
#include <string>


namespace cpppc {

// =======================================================================
// Stream operators
// =======================================================================

std::ostream & operator<<(
  std::ostream              & os,
  const cpppc::ConfigEntry  & e)
{
  std::ostringstream ss;
  ss << "ConfigEntry { " << e.key() << " -> " << e.value() << " }";

  return operator<<(os, ss.str());
}

std::ostream & operator<<(
  std::ostream              & os,
  const cpppc::SharedConfig & c)
{
  std::ostringstream ss;
  ss << "SharedConfig { " << std::endl
     << "    name("       << c.name()     << ")," << std::endl
     << "    _num_units(" << c._num_units << ")," << std::endl
     << "    _entries("   << std::endl;
  for (auto & e : c._entries) {
    ss << "      " << e << std::endl;
  }
  ss << "    )";
  return operator<<(os, ss.str());
}

} // namespace cpppc
