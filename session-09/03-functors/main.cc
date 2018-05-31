/* vim: set foldmethod=marker: */

#include "macro.h"
#include "functor.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <functional>


using std::cout;
using std::endl;

using namespace std::chrono;

/*
 * Functions are first-class types, so they can be
 * ... passed as function arguments (they should be equivalent to data
 *     anyways, remember)
 * ... returned as the result of callables
 *     that is: functions and methods, or anything implementing operator()
 *
 * Q: What's the difference between a function and a method again?
 *
 */


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  Functor ftor(12.34);

  cout << "ftor(12.34)(100) = " << ftor(100) << endl;

  return EXIT_SUCCESS;
}

