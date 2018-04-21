#include "macro.h"
#include "heap.h"

#include <iostream>
#include <cstdlib>


using cpppc::Heap;
using cpppc::HeapElement;

using std::cout;
using std::endl;

void read_heap(const Heap & h)
{

}


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  // NOTE:
  //   It is a commonly accepted guideline that `new` and `delete`
  //   should never appear in program code.
  //   Heap allocation is resource management.
  //   All resource management tasks can and should be encapsulated
  //   (see RAII, coming soon).

  Heap * p_0_ptr = new Heap("pool_0", 0, 100.0);

  Heap * p_1_ptr = new Heap("pool_1", 3, 100.0);
  Heap * p_2_ptr = new Heap("pool_2", 2, 200.0);
  Heap * p_3_ptr = new Heap(*p_1_ptr);

  Heap & p_0     = *p_0_ptr;
  Heap & p_1     = *p_1_ptr;
  Heap & p_2     = *p_2_ptr;
  Heap & p_3     = *p_3_ptr;

  p_3[0] = HeapElement { 310.0 };
  p_3[1] = HeapElement { 320.0 };

  cout << p_0 << endl;
  cout << p_1 << endl;
  cout << p_2 << endl;
  cout << p_3 << endl;

  cout << endl;
  cout << "Assignment:" << endl;
  cout << endl;

  p_3 = p_2;

  cout << endl;
  cout << "After assignment:" << endl;
  cout << endl;

  delete p_1_ptr;
  delete p_2_ptr;
  delete p_3_ptr;

  delete p_0_ptr;

  return EXIT_SUCCESS;
}
