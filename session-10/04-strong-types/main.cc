
#include "macro.h"

#include <iostream>
#include <chrono>
#include <cstdlib>


using std::cout;
using std::endl;


namespace imperial {

  class ounces {

  };

  class pounds {

  };

  class yards {

  };

  class feet {

  };

  class miles {

  };

  class gallons {

  };

  // ... and ooooh so many more!
}

namespace metric {
  class grams {

  };

  class meters {
  };

  class liters {

  };
}



int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  using namespace metric;

//  auto work = meters(10) * kilo.grams(12);

  return EXIT_SUCCESS;
}

