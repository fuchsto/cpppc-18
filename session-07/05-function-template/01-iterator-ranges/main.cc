#include "macro.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include <array>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::endl;


static const int NElem = 10;

// Not (until C++20 prolly)
std::vector v = { 20, 30 };

int x = 4;

auto   c = x; // -> int
auto & r = x; // -> int &
const auto & cr = x; // -> const int &


using cr_type = decltype(*(&x));


template <class T>
decltype(auto) make_type_deduced_vector(T && ctor_arg) {
  return std::vector< std::remove_reference<T>::type >(
            std::forward<T &&>(ctor_arg) );
}


auto v = make_type_deduced_vector(3.4); // -> std::vector<double>

const int & a = x;

std::typeid(x) -> "PK3int"



template<class Iter>
Iter find_nth_between(Iter start, Iter end, int n)
{
  auto range_len = std::distance(start, end);
  if (n >= range_len) {
    return end;
  }
  // Advance start iterator:
  return start + n;
}

int main(int argc, char * argv[])
{
  using std::cout;
  using std::endl;

  wno_unused_(argc);
  wno_unused_(argv);

  typedef double val_t;

  val_t                    c_arr[NElem];
  std::array<val_t, NElem> stl_arr;
  std::vector<val_t>       stl_vec(NElem);
  std::list<val_t>         stl_lst(NElem);

  std::fill(c_arr,           c_arr + NElem, 1.23);
  std::fill(stl_arr.begin(), stl_arr.end(), 2.34);
  std::fill(stl_vec.begin(), stl_vec.end(), 3.45);
  std::fill(stl_lst.begin(), stl_lst.end(), 4.56);

#if 1
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
#endif

#if 1
  cout << "Find element at offset 4 in C array:" << endl;
  auto c_arr_4th = find_nth_between(c_arr, c_arr + NElem, 4);
  cout << " -> " << *c_arr_4th << endl;


  cout << "Find element at offset 4 in array range:" << endl;
  auto stl_arr_4th = find_nth_between(stl_arr.begin(), stl_arr.end(), 4);
  cout << " -> " << *stl_arr_4th << endl;


  cout << "Find element at offset 4 in vector range:" << endl;
  auto stl_vec_4th = find_nth_between(stl_vec.begin(), stl_vec.end(), 4);
  cout << " -> " << *stl_vec_4th << endl;


  cout << "Find element at offset 4 in list range:" << endl;
  auto stl_lst_4th = find_nth_between(stl_lst.begin(), stl_lst.end(), 4);
  cout << " -> " << *stl_lst_4th << endl;
#endif

  return EXIT_SUCCESS;
}

