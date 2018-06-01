#include "macro.h"

#include "bucket_vector.h"

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>


using std::cout;
using std::endl;

using cpppc::BucketVector;

template <typename SeqContainerType>
void print_values(const SeqContainerType & sc)
{
  // Methods used in the iterator interface:
  //   - operator*
  //   - operator!=
  //
  // --> ForwardIterator is sufficient
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

  BucketVector<int> v0;
  BucketVector<int> v1;

  v0.push_back(1);
  v0.push_back(2);
  v0.push_back(3);

  v1 = v0;

  cout << "v1: ";
  print_values(v1);

  BucketVector<int> v2(v1);
  v2.push_back(6);
  v2.push_back(5);
  v2.push_back(4);

  cout << "v2: ";
  print_values(v2);

  auto it_found_4 = std::find(v2.begin(), v2.end(), 4);
  if (it_found_4 == v2.end()) {
    cout << "value 4 not found in v2!" << endl;
  } else {
    cout << "value 4 found in v2" << endl;
  }

#if 0
  // Fails because std::sort expects iterators in the RandomAccessIterator
  // category (see std::list.sort for an alternative):
  BucketVector<int> v2_s(v2);
  std::sort(v2_s.begin(), v2_s.end());
#endif

  return EXIT_SUCCESS;
}
