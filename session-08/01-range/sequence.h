

int  size = 20;
auto ls   = lazy_sequence<int>(
              size,
              [](int offset) {
                  return offset * offset;
              });


auto ls_end   = std::end(ls);
auto ls_begin = std::begin(ls);


namespace std {

// template <class T>
// decltype(auto)
// begin(T && range) { return std::forward<T&&>(range).begin(); }

  template <class T>
  decltype(auto)
  begin(lazy_sequence<T> & ls) { return std::advance(ls.begin(), 1); }

}


auto ls   = lazy_sequence<int>(
              [](int offset) {
                  return offset * offset;
              });

// Iterate [0..20] ... ?

// Prereqs:
//    - std::begin(range)
//    - std::end(range)
int count = 20;
for (const auto & value : range) {
  if (--count == 0) { break; }
}



std::list<int> l(...);

// Iterate first 20 elements of l ... ?



