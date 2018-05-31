#include "macro.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include <array>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using std::cout;
using std::endl;

#define NElem 10000000

template<typename Iter, typename ValueT>
void range_inc(Iter first, Iter last, ValueT d)
{
  for (auto it = first; it != last; ++it) {
    *it += d;
  }
}

template<typename Iter, typename ValueT>
void range_acc(Iter first, Iter last, ValueT & ref)
{
  for (auto it = first; it != last; ++it) {
    ref += *it;
  }
}

void print_msg(int tid, std::string msg)
{
#if MUTEX_IO
  static std::mutex io_mx;
  std::lock_guard<std::mutex> io_lg(io_mx);
#endif

  for (int i = 0; i < 100; i++) {
    cout << "[ thread " << tid << " ]: " << msg;
  }
}

int main(int argc, char * argv[])
{
  using std::cout;
  using std::endl;

  wno_unused_(argc);
  wno_unused_(argv);

  typedef long                          val_t;
  typedef std::vector<val_t>::iterator  vec_iterator;

  int n_threads = 4;

  std::vector<val_t>       vec(NElem);
  std::vector<std::thread> threads;

  // ------------------------------------------------------------------------

  std::fill(vec.begin(), vec.end(), 1);
  for (int t = 0; t < n_threads; t++) {
    threads.push_back(
      std::thread(
        range_inc<vec_iterator, val_t>, vec.begin(), vec.end(), 1
      ));
  }
  for (auto & thread : threads) {
    thread.join();
  }
  threads.clear();

  cout << "sum: "
       << static_cast<val_t>(
            std::accumulate(vec.begin(), vec.end(), 0, std::plus<val_t>()))
       << endl;

  return EXIT_SUCCESS;

  // ------------------------------------------------------------------------

  val_t acc = 0;
  std::fill(vec.begin(), vec.end(), 1);
  for (int t = 0; t < n_threads; t++) {
    threads.push_back(
      std::thread(
        range_acc<vec_iterator, val_t>, vec.begin(), vec.end(), std::ref(acc)
      ));
  }
  for (auto & thread : threads) {
    thread.join();
  }
  threads.clear();

  cout << "acc: "
       << static_cast<val_t>(acc)
       << endl;

  return EXIT_SUCCESS;
}

