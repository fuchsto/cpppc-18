
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
  virtual ~Base() { }

  virtual void ducky() const {
    std::cout << " named " << _name << std::endl;
  }
};

struct Wombat : public Base {
  Wombat(const std::string & name) : Base(name) { }
  // Actually virtual once, virtual forever.
  virtual ~Wombat() { }

  virtual void ducky() const {
    std::cout << "Wombat::ducky()";
    Base::ducky();
  }
};

struct Kitten : public Base {
  Kitten(const std::string & name) : Base(name) { }
  // Actually virtual once, virtual forever.
  virtual ~Kitten() { }

  virtual void ducky() const {
    std::cout << "Kitten::ducky()";
    Base::ducky();
  }
};

} // namespace vrt
