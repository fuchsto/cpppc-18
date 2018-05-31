
#include <iostream>
#include <vector>


namespace svt {

template <class Derived>
class Base
{
  std::string _name;

  Derived & derived() const {
    // Cast to concrete/subclass type.
    // First cast `this` to `Derived *`, then dereference.
    return *(static_cast<Derived *>(this));
  }
public:
  Base() = delete;
  Base(const std::string & name) : _name(name) { }

  void ducky() const {
    derived().ducky();
    std::cout << " named " << _name << std::endl;
  }
};

struct Wombat : public Base<Wombat>
{
  Wombat(const std::string & name) : Base(name) { }

  void ducky() const {
    std::cout << "Wombat::ducky()";
  }
};

struct Kitten : public Base<Kitten>
{
  Kitten(const std::string & name) : Base(name) { }

  void ducky() const {
    std::cout << "Kitten::ducky()";
  }
};

} // namespace svt
