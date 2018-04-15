#ifndef EX__02_STRING_H__INCLUDED
#define EX__02_STRING_H__INCLUDED

#include <string.h>
#include <stdlib.h>


// {{{
typedef struct {
  char  * data;
  char    size;
} String;
// }}}

String * string_new() {
   String * target = (String *)(malloc(sizeof(String));
   target->data = NULL;
   target->size = 0;
   return target;
}

String * string_create(const char * str) {
  String * target = string_new();
  target->size = strlen(str);
  target->data = (char *)malloc(sizeof(char) * target->size);
  strcpy(target->data, str);
  return target;
}

String * string_assign(String * lhs, String * rhs) {
  if (lhs->size != rhs->size) {
    lhs->size = rhs->size;
    lhs->data = realloc(lhs->data, lhs->size);
  }
  strcpy(target->data, str);
  return lhs;
}

String * string_copy(String * other);

#endif /* EX__02_STRING_H__INCLUDED */
