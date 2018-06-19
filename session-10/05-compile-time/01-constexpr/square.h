
// Talk by Peter Gottschling:
// https://www.youtube.com/watch?v=EkdfiHs78DY

template <typename T>
T square(T x) { return x * x; }

// Q: Difference between these functions?

template <typename T>
constexpr T square_ce(T x) { return x * x; }


const int c = square_ce(argv[1]);  // <-- calculation at run time
const int c = square_ce(45);       // <-- evaluated at compile time

int a = 40;




// Q: Is there a difference?
//
//           long sq1 = square_ce(400);
// constexpr long sq2 = square_ce(400);
//
// Q: Is this allowed?
//
// int sq3 = square_ce(atoi(argv[0]));

constexpr int factorial(int n)
{
    return n <= 1? 1 : (n * factorial(n - 1));
}

constexpr int f = factorial(4);


