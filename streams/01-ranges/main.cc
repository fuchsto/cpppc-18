
// Sketching out some use cases here.
//
//
// Remember: We never start with the actual implementation.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template <class ItA, class ItB>
void cout_range(ItA && first, ItB && last) {
  std::for_each(first, last, [](
    const decltype(*first) & value) {
      std::cout << value << " ";
    });
}

template <class Range>
void cout_range(Range && r) {
  for (const auto & value : r) {
    std::cout << value << " ";
  }
}



template <
  class Predicate,
  class InIterator,
  class InSentinel >
class RangeFilter
{
  // There are more sophisticated ways, but those would confuse you at
  // the moment.
  // We want to get the value_type of `Iterator`.
  // If we restrict `Iterator` to STL-style iterator types, we can use
  // iterator traits.
  // 
  using value_type = typename std::iterator_traits<InIterator>::value_type;

public:
  // Could also be a private type, ranges don't have to specify a
  // public type `iterator` like containers.
  //
  //     BECAUSE RANGES ARE NOT CONTAINERS.
  //
  //     BECAUSE THEY DO NOT CONTAIN ANYTHING.
  //     (no elements at least)
  //
  class iterator {
    using self_t = iterator;
  public:

    iterator(InSentinel input_end,
             Predicate  predicate)
    : _input_it(input_end)
    , _input_end(input_end)
    , _predicate(predicate)
    { }

    iterator(InIterator input_it,
             InSentinel input_end,
             Predicate  predicate)
    : _input_it(input_it)
    , _input_end(input_end)
    , _predicate(predicate)
    { }

    // Aha! operator* is not const because it could lead to operator++.
    // We could use mutable, but for now, let's just see if we can do
    // without const here.
    const value_type & operator*() {
      // We could also use decltype(auto) here and not define value_type
      // at all.
      const value_type & v = *_input_it;
      if (_predicate(v)) { return v; }
      else {
        // Element is filtered, advancing to next position in input
        // range.
        ++(*this);
        return *(*this);
      }
    }

    // Range iterators are forward iterators.
    // In principle.
    self_t & operator++() noexcept {
      if (_input_it != _input_end) {
        ++_input_it;
      }
      return *this;
    }

    // Well, let's just go on with what we know.
    bool operator==(const self_t & rhs) const noexcept {
      return _input_it == rhs._input_it;
    }

    bool operator!=(const self_t & rhs) const noexcept {
      return !(*this == rhs);
    }

  private:
    InIterator  _input_it;
    InSentinel  _input_end;
    Predicate   _predicate;
  };

public:
  RangeFilter(
    Predicate   p,       // We might have to refine the parameter types
    InIterator  r_begin, // later, for perfect forwarding or const & or
    InIterator  r_end)   // something, but we don't know enough at this
                         // point, so we stick to a primitive working
                         // version
  : _predicate(p)
  , _r_begin(r_begin)
  , _r_end(r_end)
  { }

public:
  // Range filters are non-modifying
  iterator begin() const {
    // Hm! The iterator type we want to return is NOT the input iterator
    // type.
    // Hm!
    // Are range iterators random access? No.
    // Ranges allow std::begin and std::end. No mentioning of random access.
    return iterator(_r_begin, _r_end, _predicate);
  }

  iterator end() const {
    // Ah, no predicate here. Perhaps we should not use `iterator`?
    // But for now:
    return iterator(
            _r_end,
            _predicate); // unused for end iterator
  }

private:
  Predicate   _predicate;
  InIterator  _r_begin;
  InSentinel  _r_end;
};


// Okay, back to thinking about "valid expressions"
//
//   auto output = input | filter(predicate)
//
//                 => filter_impl(predicate, input)
//
//                 => RangeFilter<Predicate,Iterator,Sentinel>(
//                        predicate,
//                        std::begin(input),
//                        std::end(input))
//
// What are the valid expressions for `output`?
// So we now know the type of `output` (RangeFilter).
//
// And we know that `output` should be a range.
// Ranges have the valid expressions:
//
//     std::begin(range)
//     std::end(range)
// 
// Is RangeFilter a range? Nope, not yet.
//
template<class Predicate, class Range>
decltype(auto) filter_impl(
    Predicate    predicate,
    Range     && input) // This is a forwarding reference, not an 
                        // rvalue reference.
                        // But you all know that well at this point.
                        // Or else.
{ 
  return RangeFilter<
            decltype(predicate),
            decltype(std::begin(input)),
            decltype(std::end(input))
         >(predicate,
           std::begin(
             std::forward<Range &&>(
               input)),
           std::end(
             std::forward<Range &&>(
               input)));
}

int main() {
  using std::cout;
  using std::endl;

  std::vector<int> values_a { 1, 2, 3, 23, 42 };
  std::vector<int> values_b { 23, 42, 5, 4, 3 };

  // Now please don't be afraid, there will be a ton of compiler
  // errors.
  // See?
  // And you noticed that I did EXACTLY what I told you over and over:
  // start with the first compiler error.
  // Ignore the rest.
  // Recompile.
  // It wasn't so bad after all, was it? Just some typos.
  
  cout << "values_a: ";
  cout_range(values_a);
  cout << '\n';

  auto filtered = filter_impl([](int v) { return v < 10; },
                              values_a);
  cout << "filtered: ";
  cout_range(filtered);
  cout << '\n';

  cout << "values_b: ";
  cout_range(values_b.begin(), values_b.end());
  cout << '\n';

  std::transform(values_a.begin(), values_a.end(), // input range a
                 values_b.begin(),                 // input range b
                 values_b.begin(),                 // output range start
                 [](int a, int b) {
                    return a + (b * 2);
                 });

  cout << "values_b (transformed) ";
  cout_range(values_b);
  cout << '\n';

  // Okay, now about composing STL algorithms

  //   auto result = values_a | filter( [](? value) { return value > 10 })
  //                             // returns range containing all values_a
  //                             // greater than 10
  //                          | transform( ... yadayada ...)

  // We first implement this using classic STL algorithms.
  
  // How do we "filter" values in a range?
  // Well, we could copy all remaining (un-filtered) values to a
  // temporary range. Not fancy, but it's a start.
  //
  
  // Or: overwrite the input range. Meh.
  
  // So this is the most simplistic first approach I can come up with
  // right now (it's not what you should do):
  // This "for_each_if" coincidentally implements a filter.
  //
  std::vector<int> values_a_filtered;
  std::for_each( // you should already feel a bit guilty here
      values_a.begin(),
      values_a.end(),
      [&](int v) {
        if (v > 40) { values_a_filtered.push_back(v); }
      });

  cout << "values_a (filtered: > 40) ";
  cout_range(values_a_filtered);
  cout << '\n';

  // What we actually want:
  //  
  //   auto output = input | filter(predicate)
  //   `--> range object
  //
  //   auto output_it = output.begin();
  //   `--> a custom iterator which skips elements that don't
  //        match the predicate we used in `filter(predicate)`


  return 0;
}

