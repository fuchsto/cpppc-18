#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

// Might come in handy:
#include <unordered_map>


namespace cpppc {

namespace detail {

template <class SparseArrayT>
class sparse_array_iterator
{
  // Just a suggestion
};

template <class SparseArrayT>
class sparse_array_proxy_ref
{
  // Just a suggestion
};

} // namespace detail


template <class T, std::size_t N>
class sparse_array
{
  // Just a suggestion:

  typedef sparse_array<T, N>                      self_t;
  typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
  typedef int                                     index_t;

public:

  typedef detail::sparse_array_iterator<self_t>   iterator;
  typedef index_t                                 difference_type;

  friend iterator;

public:

  // YOUR IMPLEMENTATION HERE

};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
