#ifndef CPPPC__03__VECTOR_T__H__INCLUDED
#define CPPPC__03__VECTOR_T__H__INCLUDED

#include <memory.h>
#include <string.h>
#include <stdlib.h>

/**
 * Usage:
 *
 *   DECLARE_GENERIC__VECTOR(ulong, unsigned long); // declares Vector_ulong
 */
#define DECLARE_GENERIC__VECTOR(QUAL_TYPE, VECTOR_VALUE_TYPE) \
  typedef VECTOR_VALUE_TYPE \
          Vector_##QUAL_TYPE##_Value;  \
  \
  typedef Vector_##QUAL_TYPE##_Value * \
          Vector_##QUAL_TYPE##_Iterator; \
  \
  typedef struct { \
    int                          size; \
    Vector_##QUAL_TYPE##_Value * data; \
  } Vector_##QUAL_TYPE; \
  \
  Vector_##QUAL_TYPE *          vector_##QUAL_TYPE##__new(); \
  \
  Vector_##QUAL_TYPE *          vector_##QUAL_TYPE##__copy( \
                                  Vector_##QUAL_TYPE * other); \
  \
  void                          vector_##QUAL_TYPE##__delete( \
                                  Vector_##QUAL_TYPE * v); \
  \
  Vector_##QUAL_TYPE *          vector_##QUAL_TYPE##__assign( \
                                  Vector_##QUAL_TYPE * lhs, \
                                  Vector_##QUAL_TYPE * rhs); \
  \
  int                           vector_##QUAL_TYPE##__equals( \
                                  Vector_##QUAL_TYPE * lhs, \
                                  Vector_##QUAL_TYPE * rhs); \
  \
  int                           vector_##QUAL_TYPE##__size( \
                                  Vector_##QUAL_TYPE * v); \
  \
  int                           vector_##QUAL_TYPE##__empty( \
                                  Vector_##QUAL_TYPE * v); \
  \
  Vector_##QUAL_TYPE##_Iterator vector_##QUAL_TYPE##__begin( \
                                  Vector_##QUAL_TYPE * v); \
  \
  Vector_##QUAL_TYPE##_Iterator vector_##QUAL_TYPE##__end( \
                                  Vector_##QUAL_TYPE * v); \
  \
  void                          vector_##QUAL_TYPE##__push_back(\
                                  Vector_##QUAL_TYPE * v, \
                                  Vector_##QUAL_TYPE##_Value value); \
  \
  void                          vector_##QUAL_TYPE##__push_front( \
                                  Vector_##QUAL_TYPE * v, \
                                  Vector_##QUAL_TYPE##_Value value); \
  \
  Vector_##QUAL_TYPE##_Value    vector_##QUAL_TYPE##__pop_back( \
                                  Vector_##QUAL_TYPE * v); \
  \
  Vector_##QUAL_TYPE##_Value    vector_##QUAL_TYPE##__pop_front( \
                                  Vector_##QUAL_TYPE * v); \
  \
  Vector_##QUAL_TYPE##_Value    vector_##QUAL_TYPE##__at( \
                                  Vector_##QUAL_TYPE * v, int offset); \
\
\
\
  Vector_##QUAL_TYPE * \
  vector_##QUAL_TYPE##__new() \
  { \
    Vector_##QUAL_TYPE * v = (Vector_##QUAL_TYPE *)( \
                               malloc(sizeof(Vector_##QUAL_TYPE))); \
    v->size = 0; \
    v->data = 0; \
    return v; \
  } \
\
\
  void \
  vector_##QUAL_TYPE##__delete( \
    Vector_##QUAL_TYPE * v) \
  { \
    free(v->data); \
    free(v); \
  } \
\
\
  typedef int Vector_##QUAL_TYPE##__Defined

#endif // CPPPC__03__VECTOR_T__H__INCLUDED
