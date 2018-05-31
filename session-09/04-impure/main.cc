
#include "macro.h"

#include <iostream>
#include <chrono>
#include <cstdlib>


using std::cout;
using std::endl;

using namespace std::chrono;

/* Pure functions must not have side effects and are therefore stateless.
 * The real world is stateful, however.
 * A function printing to STDOUT is not pure: it changed the state of the
 * terminal, e.g. its line buffer, scroll position, ...
 *
 * Q: What are the disadvantage of stateful functions again?
 *    Can these be reduced to a single requirement for their
 *    correctness?
 */


/* A: The fundamental problem of stateful functions is the restriction
 *    of their invocation order.
 *
 *
 * -> If we find a way to restrict invocation order of stateful functions,
 *    their 'impurity' can be encapsulated.
 */


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);


  return EXIT_SUCCESS;
}

