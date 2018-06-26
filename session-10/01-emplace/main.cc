
#include "macro.h"

#include <iostream>
#include <chrono>
#include <cstdlib>

#include <vector>



template <int N, class T>
class array {
private:
  T _data[N];
};


template <class T>
class vector {
  vector(int size) {
    _data = malloc(sizeof(T) * size);
    _size = size;
  }
private:
  T   * _data = nullptr;
  int   _size = 0;
};




using std::cout;
using std::endl;


class Foo {
public:
  Foo(int, std::string);
};





void outer(int);
void inner(double);

void outer(int a) { inner(a + 3); }







Foo * alloc_on_stack() {
  char data[sizeof(Foo)];

  return new(data) Foo(2, "bla");
}

int main(int argc, char * argv[]) {
  wno_unused_(argc);
  wno_unused_(argv);


  std::vector<Foo> v;

  v.reserve(2);


  v.emplace_back(4, "bla");

  v.push_back(Foo(4, "bla"));


  return EXIT_SUCCESS;
}

