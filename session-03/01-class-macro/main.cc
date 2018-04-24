#include "macro.h"

#include "vector_t.h"


DECLARE_GENERIC__VECTOR(ulong, unsigned long);
DECLARE_GENERIC__VECTOR(float, float);

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  Vector_ulong * v_ulong = vector_ulong__new();
  Vector_float * v_float = vector_float__new();

  vector_ulong__delete(v_ulong);
  vector_float__delete(v_float);
}
