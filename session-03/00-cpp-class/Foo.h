#ifndef FOO_H__INCLUDED
#define FOO_H__INCLUDED

template <typename T>
class Foo
{

public:

  Foo()
  {
    _value = 0;
  }

  Foo(T value)
  {
    _value = value;
  }

  T value() const
  {
    return _value;
  }

private:

  T _value;

};

#endif // FOO_H__INCLUDED
