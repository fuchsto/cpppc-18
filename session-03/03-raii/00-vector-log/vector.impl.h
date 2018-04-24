#ifndef CPPPC__03__VECTOR__IMPL__H__INCLUDED
#define CPPPC__03__VECTOR__IMPL__H__INCLUDED

namespace cpppc {

template <typename T>
Vector<T>::Vector(const std::string & name) noexcept
: _name(name)
{
  LOG("Vector", this << " Constructor (" << name << ")");
}

template <typename T>
Vector<T>::Vector(const self_t & other)
: _name(other._name)
{
  LOG("Vector", this << " Copy        (" << &other << ")");
  resize(other._capacity);
  _size = other._size;
  memcpy(_elements, other._elements, _size * sizeof(value_t));
}

template <typename T>
Vector<T>::~Vector() noexcept
{
  LOG("Vector", this << " Destructor");
  clear();
}

template <typename T>
Vector<T> & Vector<T>::operator=(const self_t & rhs)
{
  LOG("Vector", this << " Assign      (" << &other << ")");
  clear();
  resize(rhs._capacity);
  _size = rhs._size;
  memcpy(_elements, rhs._elements, _size * sizeof(value_t));

  return *this;
}

template <typename T>
bool Vector<T>::operator==(const self_t & rhs) const noexcept
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

template <typename T>
void Vector<T>::clear()
{
  // Q: Are destructors of elements called? Why (not)?
  free(_elements);
  _elements = nullptr;
  _size     = 0;
  _capacity = 0;
}

template <typename T>
void Vector<T>::resize(int new_size)
{
  if (new_size <= _capacity) {
    return;
  }
  LOG("Vector", this << " resize      (" << new_size << ") "
                                         << "_capacity: " << _capacity);
  value_t * resized_elements = static_cast<value_t *>(
                                 realloc(_elements,
                                         sizeof(value_t) * new_size));
  if (nullptr != resized_elements) {
    _elements = resized_elements;
    _capacity = new_size;
  } else {
    throw std::runtime_error("realloc failed in cpppc::Vector.resize()");
  }
}

template <typename T>
void Vector<T>::push_back(const value_type & value)
{
  LOG("Vector", this << " push_back    (" << value << ")");
  if (_size >= _capacity) {
    resize(_capacity + _chunk_size);
  }
  _elements[_size] = value;
  _size++;
}

template <typename T>
T Vector<T>::pop_back()
{
  LOG("Vector", this << " pop_back");

  // Q: Could we return a reference here? Compare with std::vector!

  if (_size <= 0) {
    throw std::runtime_error("cpppc::Vector.pop_back(): vector empty");
  }

  _size--;

  if (_capacity - _size > _chunk_size) {
    value_t * resized_elements = static_cast<value_t *>(
                                   realloc(_elements,
                                           sizeof(value_t) * _size));
    if (nullptr != resized_elements) {
      _elements = resized_elements;
      _capacity = _size;
    }
  }

  return _elements[_size];
}

} // namespace cpppc

#endif // CPPPC__03__VECTOR__IMPL__H__INCLUDED
