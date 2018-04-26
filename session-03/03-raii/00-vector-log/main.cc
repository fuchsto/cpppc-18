#include "macro.h"

#include "vector.h"

#include <iostream>
#include <cstdlib>
#include <cassert>


using std::cout;
using std::endl;

using cpppc::Vector;

template <typename SeqContainerType>
void print_values(const SeqContainerType & sc)
{
  std::cout << "{ ";
  for (auto it = sc.begin(); it != sc.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "}" << std::endl;
}

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  Vector<int> v0("v0");
  Vector<int> v1("v1");

  assert(v0 == v1 && v1 == v0);

  assert(v0.size() == 0 && v0.empty());
  assert(v1.size() == 0 && v1.empty());

  v0.push_back(1);
  v0.push_back(2);
  v0.push_back(3);
  print_values(v0);

  assert(v0.size() == 3 && !v0.empty());
  assert(v0.at(0) == 1);
  assert(v0.at(1) == 2);
  assert(v0.at(2) == 3);

  v1 = v0;
  print_values(v1);

  assert(v0 == v1 && v1 == v0);

  assert(v0.at(0) == v1.at(0));
  assert(v0.at(1) == v1.at(1));
  assert(v0.at(2) == v1.at(2));

  Vector<int> v2(v1);
  v2.push_back(4);
  v2.push_back(5);
  v2.push_back(6);
  print_values(v2);

  return EXIT_SUCCESS;
}
