

struct Base {
  int _base_member;
};

struct Derived
{
  Base _base;

  int _derived_member;
}










class Base {
  protected:
    Base() { }
  public:
    int compute() = delete;
};

class Foo : public Base {
public:
  Foo()
  : Base() { }

  int compute() { return 1; }
};

class Bar : public Base {
public:
  Bar()
  : Base() { }

  int compute() { return 2; }
};


Foo f; // { Base(); Foo(); }

Base * b = &f;

void pass_base(Base * b) {
  b->compute();
}















class AbstractBase {

public:
  virtual int compute() = 0;

};

class ConcreteFoo : public AbstractBase
{
public:
  virtual int compute() { return 1; }
};

class ConcreteBar : public AbstractBase
{
public:
  virtual int compute() { return 2; }
};

AbstractBase * make_concrete(int val) {
  return std::is_equal<2,val>::value
         ? new ConcreteFoo()
         : new ConcreteBar();
}

constexpr int a = 2;

make_concrete(a);


AbstractBase * ab;

ab = make_concrete(); // either Foo* or Bar*
ab->compute();        // either Foo::compute or Bar::compute

