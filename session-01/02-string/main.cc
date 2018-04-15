
#include "macro.h"
#include "oo-string.h"

#include <iostream>
#include <cstdlib>


using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  String * s_empty = string__new();

  String * s0 = string__create("Ich moechte einfach nur hier sitzen.");
  String * s1 = string__create("Mein Name ist Lohse! Ich kaufe hier ein!");
  String * s2 = string__create("Lassen Sie uns zur Sitzgruppe gehen.");
  String * s3 = string__create("Ein Klavier! Ein Klavier!");


  string__delete(s0);
  string__delete(s1);
  string__delete(s2);
  string__delete(s3);

  return EXIT_SUCCESS;
}
