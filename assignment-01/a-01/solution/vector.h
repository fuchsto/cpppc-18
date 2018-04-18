#ifndef CPPPC__01__VECTOR_H__INCLUDED
#define CPPPC__01__VECTOR_H__INCLUDED

typedef int             VectorValue;
typedef VectorValue *   VectorIterator;

typedef struct {
  int           size;
  VectorValue * data;
} Vector;


/* ------------------------------------------------------------------------ *
 *            DO NOT MODIFIY THE FOLLOWING FUNCTION DECLARATIONS            *
 * -------------------------------------------------------------------------*/

// Interface of Standard concept:

Vector *       vector__new();
Vector *       vector__copy(Vector * other);
void           vector__delete(Vector * v);
Vector *       vector__assign(Vector * lhs, Vector * rhs);
int            vector__equals(Vector * lhs, Vector * rhs);

// Interface of Vector concept:

int            vector__size(Vector * v);
int            vector__empty(Vector * v);
VectorIterator vector__begin(Vector * v);
VectorIterator vector__end(Vector * v);
void           vector__push_back(Vector * v, VectorValue value);
void           vector__push_front(Vector * v, VectorValue value);
VectorValue    vector__pop_back(Vector * v);
VectorValue    vector__pop_front(Vector * v);
VectorValue    vector__at(Vector * v, int offset);

#endif // CPPPC__01__VECTOR_H__INCLUDED
