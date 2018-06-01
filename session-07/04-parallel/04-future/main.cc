#include "macro.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include <vector>
#include <chrono>

#include <mutex>
#include <future>

/*
 * Note that std::async is often referred to as 'task parallelism', but
 * that's not exactly true: it's just a convenience interface for threads.
 *
 * True task parallelism (Cilk, Intel TBB, Siemens EMBB, ...) is based on
 * light-weight callable objects that are maintained in task queues and
 * executed in (usually pinned) worker threads:
 *
 *     ,-'-'-'-.         ,-'-'-'-.
 *    -|       |-       -|       |-
 *    -| CPU 0 |-       -| CPU 1 |-    ...
 *    -|       |-       -|       |-
 *     `-;-;-;-'         `-;-;-;-'
 *         o                 o
 *         | pinned          :
 *         |                 :
 *     ,---^----.                ,----------------.
 *   ,-| thread | task queue     | task scheduler |
 *   | `--------'---.            `------.---------'
 *   |   | task obj |        :          |   |                   .
 *   |   |^^^^^^^^^^|        `-------<--X   |                   :
 *   |   | task obj |                   |   |                   :
 *   |   |^^^^^^^^^^|  enqueue tasks    v   |       create task |
 *   v   :   ...    : <-----------------'   `--<---.  ,----<----| Application
 *   |                                             |  |         |
 *   |                         acquire task object |  |         `............
 *   |                                             |  |
 *   | release task object                 ,-------^--+-------.
 *   `---------------->------------------->| task object pool |
 *                                         `------------------'
 */


using std::cout;
using std::clog;
using std::endl;

#define NElem 100000

#define WITH_LOG_SYNC() \
  static std::mutex io_mx

#define LOG_SYNC(smsg) \
  do { \
    std::lock_guard<std::mutex> io_lg(io_mx); \
    clog << smsg << endl; \
  } while(0)


// Recursive concurrent subdivision, a classic.
//
// Q: Use this method to implement merge sort and quick sort.
//
template<typename Iter>
double range_acc(Iter first, Iter last, int depth = 0)
{
  WITH_LOG_SYNC();

  auto nrange = std::distance(first, last);
  if (nrange < 10000) {
    // Break condition
    return std::accumulate(first, last, 0);
  }
  // Recurse
  Iter   pivot   = first + nrange / 2;

  LOG_SYNC(std::string(depth * 2, ' ') << "split ... ");
  std::future<double> acc_fut = std::async(std::launch::async,
                                           range_acc<Iter>,
                                             pivot, last, depth+1);

  double acc_loc = range_acc(first, pivot, depth+1);
  double acc_otr = acc_fut.get();

  LOG_SYNC(std::string(depth * 2, ' ')
           << "join: acc_fut: " << acc_otr << " acc_loc: " << acc_loc);

  return acc_loc + acc_otr;
}

double long_running(int seconds)
{
  clog << "long_running(" << seconds << ")" << endl;

  std::this_thread::sleep_for(
    std::chrono::seconds(seconds));

  clog << "long_running done" << endl;
  return 123.45;
}

//
// Q: Use std::async / futures to implement data flow / task DAG
//

int main(int argc, char * argv[])
{
  using std::cout;
  using std::endl;

  wno_unused_(argc);
  wno_unused_(argv);

  typedef double                        val_t;
  typedef std::vector<val_t>::iterator  vec_iterator;

  cout.sync_with_stdio(true);

  std::vector<val_t>       vec(NElem);
  std::vector<std::thread> threads;

  // ------------------------------------------------------------------------

  std::fill(vec.begin(), vec.end(), 1.0);
  double acc = range_acc<vec_iterator>(vec.begin(), vec.end());

  for (auto & thread : threads) {
    thread.join();
  }
  threads.clear();

  cout << "acc: " << static_cast<int>(acc)
       << endl;

  // ------------------------------------------------------------------------

#if 0
  // Q: These calls are synchronous. Why?
  //
  std::async(std::launch::async, long_running, 3);
  std::async(std::launch::async, long_running, 4);
  std::async(std::launch::async, long_running, 5);
#endif

  return EXIT_SUCCESS;
}

