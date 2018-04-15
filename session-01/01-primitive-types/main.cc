#include "macro.h"
#include "primitive.h"
#include "subclass.h"

#include <iostream>
#include <cstdlib>


using cpppc::Primitive;
using cpppc::Data;
using cpppc::Subclass;

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  cout << "sizeof(std::string): " << sizeof(std::string) << endl;
  cout << "sizeof(Data):        " << sizeof(Data)        << endl;
  cout << "sizeof(Primitive):   " << sizeof(Primitive)   << endl;
  cout << "sizeof(Subclass):    " << sizeof(Subclass)    << endl;

  Primitive p_1("primitive_1", 12, 1.23);
  Primitive p_2("primitive_2", 23, 2.34);
  Primitive p_3(p_1);

  cout << "sizeof(p_1): " << sizeof(p_1) << endl;
  cout << "sizeof(p_2): " << sizeof(p_2) << endl;
  cout << "sizeof(p_3): " << sizeof(p_3) << endl;

  Primitive p_l("Instance of Primitive with a rather long name. "
                "Wonder how long this string has to be to actually "
                "increase the object's size", 23, 2.34);
  cout << "sizeof(p_l): " << sizeof(p_l) << endl;

  cout << endl;
  cout << "---- Primitive ---------" << endl;
  cout << p_1 << endl;
  cout << p_2 << endl;
  cout << p_3 << endl;

//return EXIT_SUCCESS;

  p_1 = p_2;
  cout << endl;
  cout << "After assignment:" << endl;
  cout << endl;

  cout << p_1 << endl;
  cout << p_2 << endl;

  Subclass s_1("subclass_1", 34, 3.45, 100.0);
  Subclass s_2("subclass_2", 34, 4.56, 200.0);
  Subclass s_3(s_1);

  cout << endl;
  cout << "---- Subclass ----------" << endl;
  cout << s_1 << endl;
  cout << s_2 << endl;
  cout << s_3 << endl;

  s_1 = s_2;
  cout << endl;
  cout << "After assignment:" << endl;
  cout << endl;

  cout << s_1 << endl;
  cout << s_2 << endl;

  return EXIT_SUCCESS;
}
