
#include "macro.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;


template <typename T>
class Defaults
{

  typedef Defaults<T> self_t;

public:

  // Q: Why is there no default comparison operator?
  // Q: Is operator!= defined implicitly?
  //
  bool operator==(const self_t & rhs) const noexcept {
    if (this == &rhs) {
      return true;
    }
    return _values == rhs._values;
  }

  void add(const T & value) {
    _values.push_back(value);
  }

  size_t size() const noexcept {
    return _values.size();
  }

private:

  std::vector<T> _values;
};


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  Defaults<int> d_1;
  Defaults<int> d_2;

  d_1.add(123);
  d_2.add(123);

  if (d_1 == d_2) { cout << "equal"     << endl; }
  else            { cout << "not equal" << endl; }

  Defaults<int> d_3(d_1);

  if (d_1 == d_3) { cout << "equal"     << endl; }
  else            { cout << "not equal" << endl; }

  return EXIT_SUCCESS;
}
