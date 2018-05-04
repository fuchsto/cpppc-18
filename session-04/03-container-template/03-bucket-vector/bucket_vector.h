#ifndef CPPPC__S04__BUCKET_VECTOR__H__INCLUDED
#define CPPPC__S04__BUCKET_VECTOR__H__INCLUDED

#include <vector>
#include <stdexcept>


namespace cpppc {

namespace detail {

  template <class BucketVectorT>
  class BucketVectorIterator
  {
    typedef BucketVectorIterator<BucketVectorT> self_t;
    typedef typename BucketVectorT::value_type  value_type;

  public:

    BucketVectorIterator(BucketVectorT * bv)
    : _bucket_vector(bv)
    { }

    // Pre-increment
    self_t & operator++() {
      increment(1);
      return *this;
    }

    // Post-increment
    self_t operator++(int) {
      self_t old(*this);
      increment(1);
      return old;
    }

    self_t & operator+=(int offset) {
      increment(offset);
      return *this;
    }

    self_t operator+(int offset) const {
      self_t res(*this);
      res += offset;
      return res;
    }

    bool operator==(const self_t & rhs) const noexcept {
      return (this == &rhs ||
              ( _bucket_vector == rhs._bucket_vector &&
                _position      == rhs._position ));
    }

    bool operator!=(const self_t & rhs) const noexcept {
      return !(*this == rhs);
    }

    value_type & operator*() {
      return _bucket_vector->at(_position);
    }

    value_type & operator->() {
      return _bucket_vector->at(_position);
    }

  private:

    void increment(int offset) {
      _position += offset;
    }

  private:

    BucketVectorT * _bucket_vector;
    int             _position        = 0;
  };

}



template <typename ValueType>
class BucketVector
{

  typedef BucketVector<ValueType>      self_t;
  typedef ValueType                   value_t;

  typedef std::vector<value_t>       bucket_t;

  template <class BucketVectorT>
  friend class BucketVectorIterator;

public:

  typedef       ValueType                                value_type;
  typedef       detail::BucketVectorIterator<self_t>       iterator;
  typedef const detail::BucketVectorIterator<self_t> const_iterator;

public:

  BucketVector()
  : _begin(iterator(this)) {
  }

  ~BucketVector() = default;

//  self_t operator=(const self_t & rhs) const noexcept {
//  }

  bool operator==(const self_t & rhs) const noexcept {
    return (this == &rhs ||
            ( _buckets == rhs._buckets));
  }

  bool operator!=(const self_t & rhs) const noexcept {
    return !(*this == rhs);
  }

  size_t size() const noexcept {
    size_t s = 0;
    for (auto & b : _buckets) {
      s += b.size();
    }
    return s;
  }

  bool empty() const noexcept {
    return (size() == 0);
  }

  iterator begin() {
    return _begin;
  }

  const_iterator begin() const {
    return const_iterator(_begin);
  }

  const_iterator end() const {
    return _begin + size();
  }

  value_t & back() const {
    return _buckets.back().back();
  }

  void push_back(const value_t & value) {
    if (_buckets.back().size() == _bucket_size) {
      bucket_t bucket;
      bucket.push_back(value);
      _buckets.push_back(bucket);
    } else {
      _buckets.back().push_back(value);
    }
  }

  void pop_back() {
    if (_buckets.back().size() > 1) {
      _buckets.back().pop_back();
    } else {
      _buckets.pop_back();
    }
  }

  value_t & operator[](int index) {
    int bucket_index  = index / _bucket_size;
    int element_phase = index % _bucket_size;
    return _buckets[bucket_index][element_phase];
  }

  const value_t & operator[](int index) const {
    int bucket_index  = index / _bucket_size;
    int element_phase = index % _bucket_size;
    return _buckets[bucket_index][element_phase];
  }

  value_t & at(int index) {
    if (static_cast<size_t>(index) < size()) {
      return this->operator[](index);
    }
    throw std::out_of_range("invalid index");
  }

  const value_t & at(int index) const {
    if (static_cast<size_t>(index) < size()) {
      return this->operator[](index);
    }
    throw std::out_of_range("invalid index");
  }

private:

  std::vector<bucket_t>              _buckets;
  size_t                             _bucket_size = 3;
  iterator                           _begin;
};

} // namespace cpppc

#endif // CPPPC__S04__BUCKET_VECTOR__H__INCLUDED
