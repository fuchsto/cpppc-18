

MoveOnly<int *> mo;

auto    c = mo; // FAIL
auto &  x = mo; // OK
auto && r = mo; // OK

int a   = 123;
int & r = a;

auto c  = r;
c       = 321;

