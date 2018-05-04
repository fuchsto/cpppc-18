#include "macro.h"
#include "heap.h"
#include "bucket_heap.h"

#include <cstdlib>
#include <iostream>

#include <array>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::endl;


int main(int argc, char * argv[])
{
  using std::cout;
  using std::endl;
  using cpppc::Heap;
  using cpppc::BucketHeap;

  wno_unused_(argc);
  wno_unused_(argv);

  Heap<double> heap("heap", 5, 100.0);

  cout << heap << endl;

  cout << "Testing shorthand for: ";
  for (auto val : heap) {
    cout << val << " ";
  }
  cout << endl;


  BucketHeap<double> bucket_heap("bucket_heap", 1, 100.0);
  bucket_heap.grow(2, 200.0);
  bucket_heap.grow(3, 300.0);

  cout << "Testing shorthand for: ";
  for (auto val : bucket_heap) {
    cout << val << " ";
  }
  cout << endl;

  return EXIT_SUCCESS;
}

