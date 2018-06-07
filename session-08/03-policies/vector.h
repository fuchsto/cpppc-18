#ifndef CPPPC__03__VECTOR_H__INCLUDED
#define CPPPC__03__VECTOR_H__INCLUDED

#include <exception>
#include <stdexcept>
#include <algorithm>

#include <cstring>
#include <cstdlib>


namespace cpppc {

class MinimalResizePolicy
{
public:

  int grow(
    int current_size,
    int nshrink,
    int current_capacity)
  {
    wno_unused_(current_size);
    wno_unused_(current_capacity);
    return nshrink;
  }

  int shrink(
    int current_size,
    int nshrink,
    int current_capacity)
  {
    wno_unused_(current_size);
    wno_unused_(current_capacity);
    return nshrink;
  }

};


template <
  typename ElementType,
  typename ResizePolicy = MinimalResizePolicy >
class Vector
{
  // Q: How about private subclassing?

  typedef Vector<ElementType, ResizePolicy> self_t;
  typedef ElementType                       value_t;

public:
  typedef value_t             value_type;

  typedef value_t *           iterator;
  typedef value_t * const     const_iterator;
  typedef value_t &           reference;

public:
  inline Vector() noexcept = default;

  inline Vector(const self_t & other)
  {
    reserve(other._capacity);
    _size = other._size;
    std::copy(other._elements,
              other._elements + _size,
              _elements);
  }

  inline ~Vector() noexcept
  {
    clear();
  }

  self_t & operator=(const self_t & rhs)
  {
    clear();
    reserve(rhs._capacity);
    _size = rhs._size;
    std::copy(rhs._elements,
              rhs._elements + _size,
              _elements);

    return *this;
  }

  bool operator==(const self_t & rhs) const noexcept
  {
    if (_size != rhs._size) {
      return false;
    }
    for (int i = 0; i < _size; i++) {
      if (_elements[i] != rhs._elements[i]) {
        return false;
      }
    }
    return true;
  }

  inline int size() const noexcept
  {
    return _size;
  }

  inline bool empty() const noexcept
  {
    return 0 == _size;
  }

  inline void clear()
  {
    free(_elements);
    _elements = nullptr;
    _size     = 0;
    _capacity = 0;
  }

  void reserve(int new_size)
  {
    if (new_size <= _capacity) {
      return;
    }
    value_t * resized_elements = static_cast<value_t *>(
                                   realloc(_elements,
                                           sizeof(value_t) * new_size));
    if (nullptr != resized_elements) {
      _elements = resized_elements;
      _capacity = new_size;
    } else {
      throw std::runtime_error("realloc failed in cpppc::Vector.reserve()");
    }
  }

  void push_back(const value_t & value)
  {
    int add_capacity = _resize_policy.grow(_size, 1, _capacity);
    if (add_capacity > 0) {
      reserve(_capacity + add_capacity);
    }
    _elements[_size] = value;
    _size++;
  }

  void pop_back()
  {
    if (_size <= 0) {
      throw std::runtime_error("cpppc::Vector.pop_back(): vector empty");
    }

    int sub_capacity = _resize_policy.shrink(_size, 1, _capacity);
    _size--;

    if (sub_capacity > 0) {
      value_t * resized_elements = static_cast<value_t *>(
                                     realloc(_elements,
                                             sizeof(value_t) *
                                               (_capacity - sub_capacity)));
      if (nullptr != resized_elements) {
        _elements = resized_elements;
        _capacity = _capacity - sub_capacity;
      }
    }
  }

  inline reference front() const noexcept
  {
    return _elements[0];
  }

  inline reference back() const noexcept
  {
    return _elements[_size-1];
  }

  inline iterator begin() const
  {
    return &(_elements[0]);
  }

  inline iterator end() const
  {
    return &(_elements[_size]);
  }

  inline reference operator[](int offset) const
  {
    return _elements[offset];
  }

  inline reference at(int offset) const
  {
    if (offset >= _size || offset < 0) {
      throw std::out_of_range("cpppc::Vector.at()");
    }
    return _elements[offset];
  }

private:
  ResizePolicy   _resize_policy;
  value_t      * _elements       = nullptr;
  int            _size           = 0;
  int            _capacity       = 0;

};

} // namespace cpppc

#endif // CPPPC__03__VECTOR_H__INCLUDED
