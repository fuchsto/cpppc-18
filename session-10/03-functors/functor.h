#ifndef FUNCTOR_H__INCLUDED
#define FUNCTOR_H__INCLUDED

#include <functional>

/*
 * Functors are quite a common technique. One might think the STL
 * provides a standard mechanism for this.
 */

class Functor
{
public:

  Functor(double coeff)
  : _coeff(coeff)
  { }

  double operator()(int value)
  {
    return _coeff * value;
  }

private:

  double _coeff;

};

#endif // FUNCTOR_H__INCLUDED
