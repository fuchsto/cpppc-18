
#include <vector>

template <typename T>
inline std::vector<T> operator+(
  const std::vector<T> & x, const std::vector<T> & y)
{
  std::vector<T> sum(size(x));
  for (int i = 0; i < size(x); i++) {
    sum[i] = x[i] + y[i];
  }
  return sum;
}

template <typename T>
inline void add(
  const std::vector<T> & x, const std::vector<T> & y,
  std::vector<T> & sum)
{
  for (int i = 0; i < size(x); i++) {
    sum[i] = x[i] + y[i];
  }
}

// Q: Okay.
//    - What if we need three, four, ... vectors?
//    - What if we need another arithmetic expression like SAXPY (a * x + y)?

