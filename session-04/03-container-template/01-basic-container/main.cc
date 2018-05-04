#include "macro.h"
#include "heap.h"

#include <iostream>
#include <cstdlib>


using cpppc::Heap;

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  typedef Heap<double> DoubleHeap;
  typedef Heap<long>   LongHeap;

  DoubleHeap dh_0("double_heap_0", 3, 100.0);
  DoubleHeap dh_1("double_heap_1", 3, 100.0);
  DoubleHeap dh_2("double_heap_2", 2, 200.0);

  LongHeap   lh_0("long_heap_0",   2, 100);
  LongHeap   lh_1("long_heap_1",   3, 100);
  LongHeap   lh_2("long_heap_2",   2, 200);

  cout << dh_0 << endl;
  cout << lh_0 << endl;

  DoubleHeap dh_it("double_heap_it", 7, 10.0);
  for (auto elem : dh_it) {
    cout << "element: " << elem << endl;
  }

  dh_it.print();
  dh_it.modify();
  cout << "Modified:" << endl;
  dh_it.print();

  return EXIT_SUCCESS;
}

