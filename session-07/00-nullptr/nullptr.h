

namespace std {

struct nullptr_t {
  template <class ParamT>
  bool operator==(const ParamT & p) { return static_cast<int>(p) == 0; }

  template <class ParamT>
  bool operator!=(const ParamT & p) { return static_cast<int>(p) != 0; }

  // int * p = nullptr;
  template <class T>
  operator T*() { return NULL; }
};

static nullptr_t nullptr;

} // namespace std


void foo(int *);
void foo(std::nullptr_t);

foo(0);
foo(nullptr);


