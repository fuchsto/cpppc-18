
#include <utility>


class resource {
  int x = 0;
};


class rule_of_5 {

public:
	rule_of_5()
    : p { new resource { } }
  { }

  rule_of_5(const rule_of_5 & other)
		: p { new resource { *(other.p) } }
  { }

  rule_of_5(rule_of_5 && other)
    : p { other.p } {
	  other.p = nullptr;
  }

  rule_of_5 & operator=(const rule_of_5 & other) {
    if (&other != this) {
      delete p;
      p = new resource { *(other.p) };
    }
    return *this;
  }

  rule_of_5 & operator=(rule_of_5 && other) {
    if (&other != this) {
      delete p;
      p       = other.p;
      other.p = nullptr;
    }
    return *this;
  }

  ~rule_of_5() {
    delete p;
  }

private:
  resource * p = nullptr;
};

