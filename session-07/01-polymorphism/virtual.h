
#include <iostream>
#include <vector>


namespace vrt {

/*
 * Now here is the thing about virtual:
 *
 */
class Base {
  std::string _name;
public:
  Base() = delete;
  Base(const std::string & name) : _name(name) { }

  // Q: Destructor must be virtual - why?
  //
  // A:
  //
  //      auto w    = Wombat("Simon");
  //
  //      auto * bp = &static_cast<Base>(w);
  //
  //      auto & br = *bp;
  //
  //      auto   bc = *bp;
  //
  virtual ~Base() { }

  virtual void say_name() const {
    std::cout << " named " << _name << std::endl;
  }
};

struct Wombat : public Base {
  Wombat(const std::string & name) : Base(name) { }
  // Actually virtual once, virtual forever.
  virtual ~Wombat() { }

  virtual void say_name() const {
    std::cout << "Wombat::say_name()";
    Base::say_name();
  }
};

struct Kitten : public Base {
  Kitten(const std::string & name) : Base(name) { }
  // Actually virtual once, virtual forever.
  virtual ~Kitten() { }

  virtual void say_name() const {
    std::cout << "Kitten::say_name()";
    Base::say_name();
  }
};

} // namespace vrt
