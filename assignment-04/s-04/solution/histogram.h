#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>

template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type value_t;
    // Guards
    if(first == last) { return last; }

    std::unordered_map<value_t, Iter> histogram;

    auto nextpos = first;
    std::for_each(first, last, [&](value_t val) {
      if (histogram.count(val) == 0) {
        (*nextpos) = 1;
        histogram[val] = nextpos;
        nextpos++;
      } else {
        ++(*(histogram[val]));
      }
    });
    return nextpos;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
