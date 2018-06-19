
#include "macro.h"

#include <iostream>
#include <chrono>
#include <cstdlib>

#include <functional>


using std::cout;
using std::endl;

using namespace std::chrono;


int main(int argc, char * argv[]) {
  wno_unused_(argc);
  wno_unused_(argv);

  double coeff = 0.5;

  // Q: What's the type of fun1, fun2?
  //
  auto fun1v = [=](double a, double b) { return coeff * (a + 1) / b;   };
  auto fun2v = [=](double a, double b) { return coeff * a / (b * 0.1); };

  cout << "fun1v(fun2v(10,20),3) = " << fun1v(fun2v(10,20),3) << endl;

  coeff = 2.0;

  // Lambdas can access variables from their parent scope by reference.
  //
  // Q: What is a 'parent scope'?
  // Q: What is un-functional about this?
  //
  auto fun1r = [&](double a, double b) { coeff = 1.0; return coeff * a / b; };
  auto fun2r = [&](double a, double b) { coeff = 2.0; return coeff * b / a; };

  cout << "fun1r(fun2r(10,20),3) = " << fun1r(fun2r(10,20),3) << endl;
  cout << "fun1r(fun2r(10,20),3) = " << fun1r(fun2r(10,20),3) << endl;

  // Higher-order functions: Functions that depend on functions.

  return EXIT_SUCCESS;
}

