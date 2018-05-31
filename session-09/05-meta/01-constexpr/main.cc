#include <iostream>


// See: http://en.cppreference.com/w/cpp/concept/LiteralType
class Point {
  int _x;
  int _y;
public:
  constexpr Point(int ix, int iy) : _x{ix}, _y{iy} { }
  constexpr int x() const { return _x; }
  constexpr int y() const { return _y; }
};


// Q: This works for char, int, long, ... but: why can't we use float
//    or double?
//
template <long N>
struct fibonacci_tpl {
  static const long value = fibonacci_tpl<N-1>::value +
                            fibonacci_tpl<N-2>::value;
};

template <>
struct fibonacci_tpl<1> {
  static const long value = 1;
};

template <>
struct fibonacci_tpl<2> {
  static const long value = 1;
};

// const int f = fibonacci_tpl<40>::value;


// Q: Could we use float or double here?
//
//    What if the code is compiled on a system with an FPU type
//    different from the FPU at the system the program is run?
//
constexpr long fibonacci(long i) {
  return (i <= 1l) ? i : (fibonacci(i-1) + fibonacci(i-2));
}


int main(int argc, char * argv[])
{
  char int_values[fibonacci(6)] = { };

  constexpr long fib_9 = fibonacci(9);

  std::cout << sizeof(int_values) << std::endl;
  std::cout << fib_9              << std::endl;
  std::cout << fibonacci(argc)    << std::endl;

  constexpr Point p { 23, 42 };
  constexpr int py = p.y();
  double darr[py] {};

  std::cout << sizeof(darr) << std::endl;

  // Q: This is identical to instance p. Can the compiler memoize it?
  constexpr Point p2 { 23, 42 };

#if 0
  // Q: Why does this fail?
  std::cout << sizeof(std::array<char, fibonacci(argc)>) << '\n';

  // Q: Why does this fail and not fall back to run-time variant?
  constexpr long fib_arg = fibonacci(argc);
#endif
}

