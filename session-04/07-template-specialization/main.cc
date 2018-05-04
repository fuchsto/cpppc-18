#include <iostream>

using std::cout;
using std::endl;



template <typename T>
T foo(T a, T b)
{
  return a * b * b;
}

template <>
double foo(double a, double b)
{
  return a * 1.0e-2 + b;
}


int main()
{
  auto fi = foo(10, 20);
  auto fd = foo(10.0, 20.0);

  cout << "fi = " << fi << endl;
  cout << "fd = " << fd << endl;

  return 0;
}

