
#include "macro.h"

#include <iostream>
#include <algorithm>

#include <string>
#include <array>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::endl;

static const int NElem = 10;


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  typedef double val_t;

  val_t                      c_arr[NElem];
  std::array<val_t, NElem>   stl_arr;
  std::vector<val_t>         stl_vec(NElem);
  std::list<val_t>           stl_lst(NElem);

  std::fill(c_arr,           c_arr + NElem, 1.23);
  std::fill(stl_arr.begin(), stl_arr.end(), 2.34);
  std::fill(stl_vec.begin(), stl_vec.end(), 3.45);
  std::fill(stl_lst.begin(), stl_lst.end(), 4.56);

  {
    // Raw, verbosive iteration using pointers:
    cout << "c_arr:   ";
    for (val_t * p = c_arr; p != (c_arr + NElem); p++) {
      cout << *p << " ";
    }
    cout << endl;

    // Raw, verbosive iteration using iterators:
    cout << "stl_arr: ";
    for (std::array<val_t, NElem>::iterator i = stl_arr.begin();
         i != stl_arr.end(); ++i) {
      cout << *i << " ";
    }
    cout << endl;

    // Raw, verbosive iteration using iterators:
    cout << "stl_vec: ";
    for (std::vector<val_t>::iterator i = stl_vec.begin();
         i != stl_vec.end(); ++i) {
      cout << *i << " ";
    }
    cout << endl;

    // Raw, verbosive iteration using iterators:
    cout << "stl_lst: ";
    for (std::list<val_t>::iterator i = stl_lst.begin();
         i != stl_lst.end(); ++i) {
      cout << *i << " ";
    }
    cout << endl;
  }

  // Q: How about stl_lst?
  stl_arr.back() = 1.0;
  std::sort(stl_arr.begin(), stl_arr.end());

  cout << "for_each(stl_arr): ";
  std::for_each(stl_arr.begin(), stl_arr.end(),
                [](const val_t & v) {
                  cout << v << " ";
                });
  cout << endl;

  return EXIT_SUCCESS;
}
