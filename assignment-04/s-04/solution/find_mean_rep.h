#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

namespace cpppc {

// Specialization for forward iterators (avoids std::distance):
template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type      value_t;
  typedef typename std::iterator_traits<Iter>::difference_type diff_t;

  if (first == last) {
    return first;
  }

  auto   favorite = first;
  diff_t distance = 0;

  // three pass solution
  auto sum = std::accumulate(first, last, 0, [&distance](
                                               const value_t & a,
                                               const value_t & b)
                                             {
                                               ++distance;
                                               return a + b;
                                             });
  auto mean = sum / distance;

  favorite = std::min_element(first, last,
                              [&mean](const value_t & a, const value_t & b) {
                                return std::abs(mean - a) <
                                       std::abs(mean - b);
                              });
  return favorite;
}

}  // namespace cpppc

#endif  // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
