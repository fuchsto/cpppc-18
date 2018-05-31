
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
#include <memory>
#include <chrono>

#include "logged_object.h"

using std::cout;
using std::endl;


template<typename SharedPtrT>
void access_shared(SharedPtrT sptr)
{
  std::this_thread::sleep_for(
    std::chrono::milliseconds(500));
  cout << "access_shared(" << sptr.get() << "): "
       << "use_count(" << sptr.use_count() << ")"
       << endl;
}

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  typedef double               val_t;
  typedef LoggedObject<val_t>  elem_t;

  cout.sync_with_stdio(true);

  int n_threads = 4;

  std::vector<std::thread> threads;

  // ------------------------------------------------------------------------

  std::shared_ptr<elem_t> sptr(new elem_t(cout, 20.0));
  for (int t = 0; t < n_threads; t++) {
    threads.push_back(
      std::thread(
        access_shared< std::shared_ptr<elem_t> >, sptr
      ));
  }
  for (auto & thread : threads) {
    thread.join();
  }
  threads.clear();

  return EXIT_SUCCESS;
}

