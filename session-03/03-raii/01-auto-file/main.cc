
#include "macro.h"
#include "auto_file.h"
#include "auto_buffer.h"

#include <iostream>
#include <chrono>
#include <cstdlib>


using std::cout;
using std::endl;

using namespace std::chrono;


int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  // Code in this example defines a useful RAII helper:
  //
  //   auto_buffer<T>(n)
  //
  // creates an RAII handle on a buffer of n elements of type T,
  // so the buffer is freed when the handle goes out of scope.

#if 0
  {
    auto_buffer<double> abuf(10);
    std::fill(abuf.begin(), abuf.end(), 123.0);
  }
#endif
  // Q: How can we test if memory is leaked at this point?


  unsigned long ts_now = duration_cast<milliseconds>(
                           system_clock::now().time_since_epoch()
                         ).count();

  if (ts_now % 2 == 0) {
    auto_file af("mary.txt");
    cout << "-- file content --------------------------"
         << endl
         << af.string()
         << "-- end file content ----------------------"
         << endl;
  } else {
    auto_file af("limmerick.txt");
    cout << "-- file content --------------------------"
         << endl
         << af.string()
         << "-- end file content ----------------------"
         << endl;
  }

  // Q: Add support for this use case:
  //
  //      auto_file af;
  //      if (...) { af = auto_file("filename"); }
  //


  // Q: Also consider behavior of RAII for failed resource
  //    acquisition:
  //
  // auto_file af("missing_file");

  return EXIT_SUCCESS;
}

