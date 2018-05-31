
class Base;
class Foo : public Base;
class Bar : public Base;

Base * base;

base = make_concrete_base_type_obj(123); // Foo* or Bar*

base->do_stuff(); // Either Foo.do_stuff or Bar.do_stuff






template <class Derived>
class IteratorBase
{
  protected:
    IteratorBase() = default;
    IteratorBase(int pos) : _pos(pos) { }

  public:
    bool operator==(const self_t & rhs) const {
      return this == &rhs; // identity only
    }
  private:
    int _pos;
};

template <class T>
class MyIterator : IteratorBase<MyIterator<T>>
{
    using self_t = MyIterator<T>;
    using base_t = IteratorBase<MyIterator<T>>;

  public:
    MyIterator() : IteratorBase(0) { }

    bool operator==(const self_t & rhs) const {
      return base_t::operator==(rhs) &&
             // ...
    }

  // ...
};





int main()
{

  auto   w3 = Widget(12);

  Widget w1 {  };
  
  Widget w0;

  Widget w2 = Widget(12);

  std::array<int, 3> a0;
  std::array<int, 3> a1 = { };


  auto w = Widget();
  {
    auto c0    = 0.12;
    auto c1    = 0.12;
    auto fun   = [&](int a) { return coeff * a * 3.1415 };

    w.use_callback(fun);
  }
  w.show();

  return 0;
}



