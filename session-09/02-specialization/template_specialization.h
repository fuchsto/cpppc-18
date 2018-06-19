
// General type declaration:
template<class X, class Y>
class Foo;


// Default implementation:
template<class X, class Y>
class Foo { .. };


// Specializations:
template<class X>
class Foo<X, int> { .. };

template<class Y>
class Foo<int, Y> { .. };


namespace std {

  // Implementation in STL:
  template <class First, class Second>
  struct pair {
    First  first;
    Second second;
  };

  template <class T>
  decltype(auto) begin(T && range) {
    return std::forward<T>(range).begin();
  }

  // Our specializations:

  template <
    class First,
    class Second,
    class ItCat
      = typename std::iterator_traits<First>::iterator_category >
  struct pair {
    First  first;
    Second second;

    First  begin() { return first; }
  };

}

