#ifndef CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED
#define CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED

#include <string>
#include "macro.h"

// Also see:
// http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html


// Q: How can we make the name a compile time parameter?
//
// Q: How could we count the overall memory allocated by all instances
//    of ArrayWrapper?

template <class T>
class ArrayWrapper {
  typedef ArrayWrapper<T> self_t;

public:
  typedef T   value_type;
  typedef T * iterator;

public:

  ArrayWrapper()
  : _data(new T[64]),
    _size(64),
    _name("d") {
    LOG("ArrayWrapper()",
        "ooo --- default construct " << _name);
  }

  ArrayWrapper(int n, std::string name)
  : _data(new T[n]),
    _size(n),
    _name(name) {
    LOG("ArrayWrapper(n,s)",
        "*** --- create " << _name);
  }

  // move constructor
  ArrayWrapper(self_t && other)
      : _data(other._data),
        _size(other._size),
        _name(other._name) {
    LOG("ArrayWrapper(self &&)",
        "((( --- move  * <-- " << _name);
    other._data = NULL;
    other._size = 0;
  }

  // copy constructor
  ArrayWrapper(const self_t & other)
  : _data(new T[other._size]),
    _size(other._size),
    _name(other._name) {
    LOG("ArrayWrapper(const self &)",
        "=== --- create copy of " << _name);
    for (int i = 0; i < _size; ++i) {
      _data[i] = other._data[i];
    }
    LOG("ArrayWrapper(const self &)",
        "=== --- copied " << _size << " values *_*'");
  }

  ~ArrayWrapper() {
    LOG("~ArrayWrapper()",
        "xxx --- destroy " << _name << (
          ((NULL != _data) ? " and free data" : " and go home")));
    delete[] _data;
  }

  iterator begin() const {
    return _data;
  }

  iterator end() const {
    return _data + _size;
  }

  int size() const {
    return _size;
  }

 private:
  T               * _data;
  int               _size;
  const std::string _name;
};

#endif // CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED
