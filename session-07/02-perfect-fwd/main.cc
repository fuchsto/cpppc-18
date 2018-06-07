
#include <iostream>
#include <utility>

#include <iostream>
#include <memory>
#include <utility>
#include <array>

#include "TypeInfo.h"


class Foo {
public:
  constexpr Foo(int v) : _value(v) { }

  constexpr int value() const noexcept {
    return _value;
  }
private:
  int _value = 0;
};


template <class T>
void show_param_types(T && a) {
    std::cout << "T && a: " << typestr<decltype(std::forward<T>(a))>() << "\n";
}

struct A {
    A(int && n) { std::cout << "A(int &&): rvalue overload, n=" << n << "\n"; }
    A(int &  n) { std::cout << "A(int  &): lvalue overload, n=" << n << "\n"; }
};
 
class B {
public:
  // Universal / Forwarding References:
  template<class T1, class T2, class T3>
  B(T1&& t1, T2&& t2, T3&& t3) :
      a1_{ std::forward<T1>(t1) },
      a2_{ std::forward<T2>(t2) },
      a3_{ std::forward<T3>(t3) }
  { }

private:
  A a1_,
    a2_,
    a3_;
};
 
namespace cpppc {

template<class T, class U>
std::unique_ptr<T> make_unique(U && u)
{
  return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

// Variadic Template Arguments
template<class T, class... U>
std::unique_ptr<T> make_unique(U &&... u)
{
  return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

} // namespace cpppc
 
int main()
{
  show_param_types(A(2));
  
  return 0;

  std::cout << "make_unique<A>(2)\n";
  auto p1 = cpppc::make_unique<A>(2); // rvalue
  int i   = 1;
  std::cout << "make_unique<A>(i)\n";
  auto p2 = cpppc::make_unique<A>(i); // lvalue

  std::cout << "B\n";
  std::cout << "make_unique<B>(2, i, 3)\n";
  auto t  = cpppc::make_unique<B>(2, i, 3);
  
  return 0;
}


