

shared_ptr<int *> sp(new int(234));

std::thread t_0 { sp, [](shared_ptr<int *> x) { ... } };
std::thread t_1 { sp, [](shared_ptr<int *> x) { ... } };



struct Base {
  int b_a;
  int b_b;
}

struct Derived : Base {
  int d_c;
}

struct __Derived_Base {
  int b_a;
  int b_b;
  int d_c;
}


