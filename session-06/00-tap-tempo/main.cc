
#include <thread>
#include <iostream>
#include <chrono>
#include <cstdlib>


class event_period {
  public:
    event_period() = default;

    uint64_t trigger() {
      _tp_last = std::chrono::duration();
    }

  private:
    std::chrono::time_point _tp_last;
};


int main()
{
  tap_listener;

  tap_listener(std::cin, std::cout);

  return 0;
}

