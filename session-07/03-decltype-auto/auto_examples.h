auto          x      = 5;   // -> int
const auto  & rx     = x;   // -> int, specifier: const int &
auto       && urx1   = x;   // -> int &, specifier too

auto       && urx2   = 2;   // -> int, specifier: int &&

auto        * px     = &x;  // -> int, specifier: int*

int arr [2] = {1, 2};

auto          a      = arr; // -> int* (array decays)
auto        & ra     = arr; // -> int (&) [2]

void f(int, std::string);

auto          g      = f;   // -> void (*) (int, std::string)
auto        & g      = f;   // -> void (&) (int, std::string)

auto          a      = 5;   // -> int
auto          b(5);         // -> int

// Watch out for initializer lists:
//
auto          c      = {5}; // -> std::initializer_list<int>
auto          d {5};        // -> std::initializer_list<int>
                            //    or
                            // -> int (!)
// Fails (not only one type):
auto          e      = { 5, 1.0 };
