
#include <vector>
#include "macro.h"


namespace cpppc {

// Forward-declaration
template <typename T> class vector;

// Lazy evaluation at - jeezohmegosh - compile time
//
// @Michael: as promised, here we freakin' go!

template <typename T>
struct vector_sum {
  vector_sum(const vector<T> & ix, const vector<T> & iy)
  : x(ix), y(iy)
  { }

  T operator[](int i) const {
    LOG("vector_sum", "compute index "  << i);
    return x[i] + y[i];
  }

  // Q: What are the effects of const / reference members again?
  //
  // Q: Compare instantiation constraints of references to instantiation
  //    constraints of classes with const members.
  //    Could it be that there is a conceptual relationship between those?
  const vector<T> & x, & y;
};

// Q: So, what is computed here?
//
template <typename T>
vector_sum<T> operator+(
  const vector<T> & x, const vector<T> & y) {
  return { x, y }; // <- also see: uniform and generic initialization
}


template <typename T>
class vector : public std::vector<T>
{
public:
  vector<T>(std::initializer_list<T> lst) : std::vector<T>(lst)
  { } 

  cpppc::vector<T> & operator=(const vector_sum<T> & rhs) {
    for (std::size_t i = 0; i < this->size(); i++)
      (*this)[i] = rhs[i];
    return *this;
  }
};

} // namespace cpppc
