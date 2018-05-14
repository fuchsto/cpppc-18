#ifndef CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED
#define CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED

#include <string>
#include "macro.h"

// Also see:
// http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html

class MetaData
{
public:
  MetaData (int size, const std::string& name)
      : _name( name )
      , _size( size ) {
    LOG("MetaData(n,s)",
        ".... *** --- create " << _name);
  }

  // copy constructor
  MetaData (const MetaData& other)
      : _name( other._name )
      , _size( other._size ) {
    LOG("MetaData(const self &)",
        ".... === --- create copy of " << _name);
  }

  // move constructor
  MetaData (MetaData&& other)
      : _name( other._name )
      , _size( other._size ) {
    LOG("MetaData(self &&)",
        "((( --- move  * <-- " << _name);
  }

  ~MetaData() {
    LOG("~MetaData()",
        ".... xxx --- destroy " << _name);
  }

  std::string getName () const { return _name; }
  int         getSize () const { return _size; }

private:
  const std::string _name;
  int               _size;
};


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
      : _data( new T[64] ),
        _meta( 64, "?" ) {
    LOG("ArrayWrapper()",
        "ooo --- default construct " << _meta.getName());
  }

  ArrayWrapper(int n, std::string name)
      : _data( new T[n] ),
        _meta( n, name ) {
    LOG("ArrayWrapper(n,s)",
        "*** --- create " << _meta.getName());
  }

#if 1
  // move constructor
  ArrayWrapper(self_t && other)
      : _data(other._data),
        _meta(other._meta) {
    LOG("ArrayWrapper(self &&)",
        "((( --- move  * <-- " << _meta.getName());
    other._data = NULL;
    other._size = 0;
  }
#endif

  // copy constructor
  ArrayWrapper(const self_t & other)
      : _data( new T[other._size] ),
      , _meta( other._meta ) {
    
    LOG("ArrayWrapper(const self &)",
        "=== --- create copy of " << _meta.getName());
    
    for (int i = 0; i < _meta.getSize(); ++i) {
      _data[i] = other._data[i];
    }

    LOG("ArrayWrapper(const self &)",
        "=== --- copied " << _meta.getSize()
                          << " values *_*'");
  }

  ~ArrayWrapper() {
    LOG("~ArrayWrapper()",
        "xxx --- destroy " << _meta.getName());
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
  T         * _data;
  MetaData    _meta
};

#endif // CPPPC__SESSION_07__ARRAY_WRAPPER_H__INCLUDED
