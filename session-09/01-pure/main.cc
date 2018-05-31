
#include "macro.h"

#include <iostream>
#include <chrono>
#include <cstdlib>


using std::cout;
using std::endl;

using namespace std::chrono;

/*
 * Functional programming is programming with *mathematical* functions.
 *
 *
 * Some properties of mathematical functions:
 *
 * - Referencial transparency (deterministic)
 * - No side effects, no concept of "state"
 *
 * Notable effects:
 *
 * - Function invocation can be replaced by the result in any context
 * - Independent function invocations can be reordered and performed
 *   in parallel
 * - Function invocation is equivalent to data -> Higher order functions
 *
 * Q: Find some more important consequences of pure functional
 *    programming. Consider:
 *    - Disadvantages
 *    - PFP vs. OOP
 *
 *
 * Typical elements of the functional programming style:
 *
 * - Automatic type deduction
 * - First-class functions (related: functors)
 * - Lambda-functions
 * - Closures
 * - Partial function application (currying)
 * - Higher-order functions
 * - Lazy evaluation
 * - Pattern matching and recursive definition
 *   -> declarative, supported in the *type system*
 *   -> allows list processing
 * - List comprehension, for example:
 *      lst := [ x * x | x % 2 = 0 ]
 * - Function composition
 *
 * Q: How can these be realized in C++?
 *
 */

inline double f1(double a, double b)
{
  return (a + 1) / b;
}

inline double f2(double a, double b)
{
  return (a - 1) / b;
}

inline double g(double a, double b)
{
 return f1(a,b) / ((2 * f2(a,b)) - 1);
}


int main(int argc, char * argv[]) {
  wno_unused_(argc);
  wno_unused_(argv);

  cout << "g(45,34) = " << g(45,34) << endl;

  // Q: Can you name some pure-functional concepts of DASH?

  return EXIT_SUCCESS;
}

