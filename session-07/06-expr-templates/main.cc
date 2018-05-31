
#include <iostream>

// #include "vector_ops.h"
#include "vector_et_ops.h"

int main()
{
  // Now everybody, sing along!
  
  
  //
  // "With your state on the stack and your op well-defined ..."
  //
  cpppc::vector<int> v1 { 1, 2, 3, 4 };
  cpppc::vector<int> v2 { 5, 6, 7, 8 };
  cpppc::vector<int> v3 { 9, 0, 1, 2 };

  // 
  // "You try this trick, and spin it, yeah ..."
  //
  std::cout << "instantiate vector_sum:" << std::endl;
  // ,--- cpppc::vector_sum<int>
  auto vsum = v1 + v2;

  //
  // "Your op will collapse, 'cause there's nothing in it, and
  //  you ask yourself: where is my sum?"
  //
  std::cout << "assign vector_sum:" << std::endl;

  //
  // "There is my sum, there is my sum, theeeere is my sum ...
  //
  v3 = vsum;

  //
  //  log it out, on the stream, see it streamin' ...
  //
  for (auto e : v3) { std::cout << e << " "; }
  std::cout << std::endl;

  //
  // "OOooooh-ooooooh ... oooooh-ooooh ..."
  //

  return 0;
}

