

std::vector<double> vals(20);


// origin:     [------------------------]
// OK            [---------------]
// FAIL     [----------]
// FAIL                          [----------]
// FAIL                                   [----------]

// Option A: Range-Based Sub
auto sub_vals = vals | sub(2, 4);


// Option B: Iterator-Based Sub
auto sub_vals_begin = vals.begin() + 2;
auto sub_vals_end   = vals.begin() + 4;

// std::for_each(...)



// X lvalue, Y lvalue
//
//   int a = 3;
//   int b = 5;
//   fun(a, b);
//
void fun(const X &, const Y &);

// X temporary, Y lvalue
//
//   int b = 5;
//   fun(4, b);
//
//   b++;
//
void fun(X &&, const Y &);

// ...


pass_value(Blob && v);
pass_value(const Blob & v);

//
//    (const double &) --> (X: const double &) &&
//                     --> const double &
//
//    (double &&)      --> (X: double &&) &&
//                     --> double &&
//
//
template <class X, class Y>
void fun(X && x, Y &&) {
  pass_value(std::forward<X>(x));
}


// This is NOT perfect forwarding:
template <class X>
void fun(std::vector<X> && x // <-- NOT a forwarding reference
        ) {
 // does not match: const std::vector<X> &
}


template <class Domain>
class SubSequence
{
public:

  SubSequence(Domain && d, int ix_a, int ix_b)
  : _domain(std::forward<Domain>(d))
  , _ix_a(ix_a)
  , _ix_b(ix_b)

  typename std::enable_if<condition, decltype(auto)>::type
  operator[](int i) const {
    return _domain[i + _ix_a];
  }

  constexpr size_type size() const {
    return _ix_b - _ix_a;
  }

private:
  const Domain & _domain;
  int            _ix_a;
  int            _ix_b;

};




