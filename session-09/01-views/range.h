

class Sentinel {
  public:

    Sentinel() = delete;
    Sentinel(int n) : _num_compare(n) { }

    template <class Iter>
    bool operator!=(const Iter &) {
      return --_num_compare > 0;
    }

  private:
    int _num_compare;
};


auto sentinel = Sentinel(20);

for (auto it = std::advance(std::begin(range), 40);
     it != sentinel;
     ++it)
{

}

