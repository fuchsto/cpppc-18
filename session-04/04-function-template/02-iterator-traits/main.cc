#include "macro.h"

#include <cstdlib>
#include <iostream>

#include <array>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::endl;


static const int NElem = 10;

template<typename Iter>
typename
  std::enable_if<
    std::is_base_of<
      std::random_access_iterator_tag,
      typename std::iterator_traits<Iter>::iterator_category
    >::value,
    Iter
  >::type
find_nth_between(Iter start, Iter end, int n)
{
  cout << "random access find" << endl;
  auto range_len = std::distance(start, end);
  if (n >= range_len) {
    return end;
  }
  // Advance start iterator:
  return start + n;
}

template<typename Iter>
typename
  std::enable_if<
    !std::is_base_of<
      std::random_access_iterator_tag,
      typename std::iterator_traits<Iter>::iterator_category
    >::value,
    Iter
  >::type
find_nth_between(Iter start, Iter end, int n)
{
  cout << "forward find" << endl;
  auto range_len = std::distance(start, end);
  if (n >= range_len) {
    return end;
  }
  // Advance start iterator:
  std::advance(start, n);
  return start;
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

  // Templates to the rescue!

  return EXIT_SUCCESS;
}

