

template <class Derived>
class RAIIteratorBase
{
  using self_t = RAIIteratorBase<Derived>;

  Derived & derived() {
    return static_cast<Derived &>(*this);
  }

public:
  // using ...

public:
  self_t & operator+=(int step) {
    derived().increment(step);
    return (*this);
  }

  self_t operator+(const difference_type & step) {
    Derived & tmp(*this);
    tmp.increment(step);
    return tmp;
  }

  T & operator*() {
    return derived().dereference();
  }

};

template <class T>
class MyDerivedIterator
: public RAIIteratorBase<MyDerivedIterator<T> >
{

public:
  T &  dereference()         { /* ... */ }
  void increment(int offset) { _pos += offset; }
  void decrement(int offset) { increment(-offset); }

private:
  int _pos = 0;
  MyContainer * _container = nullptr;
};


