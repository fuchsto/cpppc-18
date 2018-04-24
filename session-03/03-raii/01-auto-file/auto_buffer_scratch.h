
#include <stdint.h>

typedef uint64_t size_t;


template <typename T>
class auto_buffer
{
public:

  auto_buffer() = default;

  auto_buffer(int nelem) {
    alloc(nelem);
  }

  ~auto_buffer() {
    if (nullptr != _buf) {
      delete[] _buf;
    }
  }

  void alloc(int nelem) {
    if (nullptr == _buf) {
      _nelem = nelem;
      _buf   = new T[_nelem];
    }
  }

  T * begin() { return _buf; }
  T * end()   { return _buf + _nelem; }

private:

  T *    _buf   = nullptr;
  size_t _nelem = 0;

};

