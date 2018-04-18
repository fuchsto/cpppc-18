#ifndef CPPPC__01__DEQUE_H__INCLUDED
#define CPPPC__01__DEQUE_H__INCLUDED

/* ------------------------------------------------------------------------ *
 *    NOTE: Members of the Deque type are private and not relevant to       *
 *          the Deque concept. You may change them if you want. Hint hint.  *
 * -------------------------------------------------------------------------*/

typedef int            DequeValue;

typedef struct {
  int          size;
  DequeValue * data;
} Deque;


/* ------------------------------------------------------------------------ *
 *            DO NOT MODIFIY THE FOLLOWING FUNCTION DECLARATIONS            *
 * -------------------------------------------------------------------------*/

// Interface of Standard concept:

Deque *        deque__new();
Deque *        deque__copy(Deque * other);
void           deque__delete(Deque * d);
Deque *        deque__assign(Deque * lhs, Deque * rhs);
int            deque__equals(Deque * lhs, Deque * rhs);

// Interface of Deque concept:

int            deque__size(Deque * d);
int            deque__empty(Deque * d);
void           deque__push_back(Deque * d, DequeValue value);
void           deque__push_front(Deque * d, DequeValue value);
DequeValue     deque__pop_back(Deque * d);
DequeValue     deque__pop_front(Deque * d);

#endif // CPPPC__01__DEQUE_H__INCLUDED
