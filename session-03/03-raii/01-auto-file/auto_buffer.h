#ifndef AUTO_BUFFER_H_INCLUDED
#define AUTO_BUFFER_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cstring>


template <typename ValueT>
class auto_buffer
{
  typedef auto_buffer<ValueT> self_t;

public:

  auto_buffer(int nvalues = 0)
  : _nval(nvalues)
  {
    std::cerr << "auto_buffer: construct(nvalues = " << nvalues << ")"
              << std::endl;

    if (_nval > 0) {
      std::cerr << "               new T[" << _nval << "]" << std::endl;
      _buf = new ValueT[_nval];
    }
    std::cerr << "               buf       = " << static_cast<void *>(_buf)
              << std::endl;
    std::cerr << "             construct done" << std::endl;
  }

  ~auto_buffer()
  {
    std::cerr << "auto_buffer: destruct"   << std::endl;

    if (nullptr != _buf) {
      std::cerr << "               free(" << static_cast<void *>(_buf) << ")"
                << std::endl;
      delete[] _buf;
    }

    std::cerr << "             destruct done" << std::endl;
  }

  auto_buffer(const self_t & other)
  : _nval(other._nval)
  {
    std::cerr << "auto_buffer: copy(nvalues = " << _nval << ")"
              << std::endl;

    if (_nval > 0) {
      _buf = new ValueT[_nval];
      std::copy(_buf, _buf + _nval, other._buf);
    }

    std::cerr << "auto_buffer: copy"       << std::endl
              << "               buf       = " << static_cast<void *>(_buf)
              << std::endl;
    std::cerr << "             copy done" << std::endl;
  }

  self_t & operator=(const self_t & rhs)
  {
    std::cerr << "auto_buffer: assign"     << std::endl
              << "               r.nvalues = " << rhs._nval << std::endl
              << "               r.buf     = " << static_cast<void *>(rhs._buf)
              << std::endl;

    if (nullptr != _buf) {
      std::cerr << "               free("  << static_cast<void *>(rhs._buf)
                                           << ")"
                << std::endl;
      delete[] _buf;
      _buf = nullptr;
    }

    _nval = rhs._nval;

    if (_nval > 0) {
      std::cerr << "               new T[" << _nval << "]" << std::endl;

      _buf = new ValueT[_nval];

      std::cerr << "               buf       = " << static_cast<void *>(_buf)
                << std::endl
                << "               copy("  << static_cast<void *>(_buf)
                                           << " <- "
                                           << static_cast<void *>(rhs._buf)
                                           << ")"
                << std::endl;
      strcpy(_buf, rhs._buf);
    }

    std::cerr << "             assign done" << std::endl;
    return *this;
  }

  ValueT * begin()
  {
    return _buf;
  }

  ValueT * end()
  {
    if (nullptr == _buf) {
      return nullptr;
    }
    return _buf + _nval;
  }

  int size() const
  {
    return _nval;
  }

private:

  int      _nval = 0;
  ValueT * _buf  = nullptr;

};

#endif // AUTO_BUFFER_H_INCLUDED
