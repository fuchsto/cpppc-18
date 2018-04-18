#ifndef CPPPC__01__STACK_H__INCLUDED
#define CPPPC__01__STACK_H__INCLUDED

/* ------------------------------------------------------------------------ *
 *    NOTE: Members of the Stack type are private and not relevant to       *
 *          the Stack concept. You may change them if you want. Hint hint.  *
 * -------------------------------------------------------------------------*/

typedef int            StackValue;

typedef struct {
  int          size;
  StackValue * data;
} Stack;


/* ------------------------------------------------------------------------ *
 *            DO NOT MODIFIY THE FOLLOWING FUNCTION DECLARATIONS            *
 * -------------------------------------------------------------------------*/

// Interface of Standard concept:

Stack *        stack__new();
Stack *        stack__copy(Stack * other);
void           stack__delete(Stack * s);
Stack *        stack__assign(Stack * lhs, Stack * rhs);
int            stack__equals(Stack * lhs, Stack * rhs);

// Interface of Stack concept:

int            stack__size(Stack * s);
int            stack__empty(Stack * s);
void           stack__push(Stack * s, StackValue value);
StackValue     stack__pop(Stack * s);

#endif // CPPPC__01__STACK_H__INCLUDED
