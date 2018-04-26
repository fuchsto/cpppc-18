#ifndef CPPPC__SESSION_02__CONFIG_H__INCLUDED
#define CPPPC__SESSION_02__CONFIG_H__INCLUDED

#include "macro.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace cpppc {

class ConfigEntry
{
  typedef ConfigEntry self_t;

public:

  ConfigEntry()
  {
    LOG("ConfigEntry", this << " Constructor()");
  }

  ConfigEntry(
    const std::string & key,
    const std::string & value)
  : _key(key), _value(value)
  {
    LOG("ConfigEntry", this << " Constructor ("
                            << _key << " -> " << _value << ")");
  }

  ~ConfigEntry()
  {
    LOG("ConfigEntry", this << " Destructor  ("
                            << _key << " -> " << _value << ")");
  }

  ConfigEntry(const self_t & other)
  : _key(other._key), _value(other._value)
  {
    LOG("ConfigEntry", this << " Copy        (other @ " << &other << ": "
                            << _key << " -> " << _value << ")");
  }

  self_t & operator=(const self_t & other)
  {
    LOG("ConfigEntry", this << " Assign      (other @ " << &other << ": "
                            << other._key << " -> " << other._value << ")");
    if (this != &other) {
      _key   = other._key;
      _value = other._value;
    }
    return *this;
  }

  void update(
    const std::string & key,
    const std::string & value) {
    _key   = key;
    _value = value;
  }

  const std::string & key() const
  {
    return _key;
  }

  const std::string & value() const
  {
    return _value;
  }

private:

  std::string _key;
  std::string _value;
};

class SharedConfig
{
  typedef SharedConfig self_t;


  friend std::ostream & operator<<(
    std::ostream              & os,
    const cpppc::SharedConfig & c);

public:

  typedef ConfigEntry                                 entry_type;
  typedef std::vector<entry_type>                   entries_type;

public:

  SharedConfig(const std::string & name, int num_units = 0)
  : _name(name), _num_units(num_units)
  {
    _entries.resize(num_units);
  }

  ConfigEntry & operator[](int unit_id)
  {
    return _entries[unit_id];
  }

  const ConfigEntry & operator[](int unit_id) const
  {
    return _entries[unit_id];
  }

  const std::vector<entry_type> & entries() const
  {
    return _entries;
  }

  const std::string & name() const
  {
    return _name;
  }

  void rename(const std::string & name)
  {
    _name = name;
  }

private:
  // NOTE:
  // This is NOT how you would implement this in the real world
  // (see std::unordered_map).

  std::string             _name;
  int                     _num_units = 0;
  std::vector<entry_type> _entries;
};

// =======================================================================
// Stream operators
// =======================================================================

std::ostream & operator<<(
  std::ostream              & os,
  const cpppc::ConfigEntry  & e);

} // namespace cpppc

#endif // CPPPC__SESSION_02__CONFIG_H__INCLUDED
