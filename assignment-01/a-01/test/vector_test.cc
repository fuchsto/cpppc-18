
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "vector_test.h"

#include <solution/vector.h>
#include <gtest/gtest.h>


TEST_F(VectorTest, StandardConcept)
{
  LOG_MESSAGE("VectorTest.StandardConcept: vector__new");
  Vector * v1 = vector__new();
  Vector * v2 = vector__new();

  LOG_MESSAGE("VectorTest.StandardConcept: vector__equals");
  ASSERT_EQ(1, vector__equals(v1,v2));

  vector__push_back(v1, 12);
  vector__push_back(v1, 34);

  ASSERT_EQ(0, vector__equals(v1,v2));

  LOG_MESSAGE("VectorTest.StandardConcept: vector__assign");
  vector__assign(v2, v1);

  ASSERT_EQ(1, vector__equals(v1,v2));

  LOG_MESSAGE("VectorTest.StandardConcept: vector__copy");
  Vector * v3 = vector__copy(v1);

  ASSERT_EQ(1, vector__equals(v1,v3));

  vector__delete(v1);
  vector__delete(v2);
  vector__delete(v3);
}

TEST_F(VectorTest, VectorConcept)
{
  LOG_MESSAGE("VectorTest.VectorConcept: vector__new");
  Vector * v = vector__new();

  ASSERT_EQ(0,  vector__size(v));
  ASSERT_EQ(1,  vector__empty(v));

  LOG_MESSAGE("VectorTest.VectorConcept: vector__begin, vector__end");
  ASSERT_EQ(vector__begin(v), vector__end(v));
  ASSERT_EQ(vector__end(v), vector__begin(v) + vector__size(v));

  LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(56)");
  vector__push_back(v, 56);
  LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(78)");
  vector__push_back(v, 78);
  LOG_MESSAGE("VectorTest.VectorConcept: vector__push_back(90)");
  vector__push_back(v, 90);

  ASSERT_EQ(vector__end(v), vector__begin(v) + vector__size(v));

  LOG_MESSAGE("VectorTest.VectorConcept: vector__at");
  ASSERT_EQ(3,  vector__size(v));
  ASSERT_EQ(0,  vector__empty(v));
  ASSERT_EQ(56, vector__at(v, 0));
  ASSERT_EQ(78, vector__at(v, 1));
  ASSERT_EQ(90, vector__at(v, 2));

  for (int i = 0; i < vector__size(v); i++) {
    LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                i, vector__at(v, i));
  }

  LOG_MESSAGE("VectorTest.VectorConcept: vector__push_front(34)");
  vector__push_front(v, 34);
  LOG_MESSAGE("VectorTest.VectorConcept: vector__push_front(12)");
  vector__push_front(v, 12);

  for (int i = 0; i < vector__size(v); i++) {
    LOG_MESSAGE("VectorTest.VectorConcept: v[%d] : %d",
                i, vector__at(v, i));
  }

  LOG_MESSAGE("VectorTest.VectorConcept: vector__at");
  ASSERT_EQ(5,  vector__size(v));
  ASSERT_EQ(0,  vector__empty(v));
  ASSERT_EQ(12, vector__at(v, 0));
  ASSERT_EQ(34, vector__at(v, 1));
  ASSERT_EQ(90, vector__at(v, 4));

  LOG_MESSAGE("VectorTest.VectorConcept: vector__copy");
  Vector * vcopy = vector__copy(v);

  LOG_MESSAGE("VectorTest.VectorConcept: vector__begin, vector__end");
  VectorIterator viter = vector__begin(v);
  VectorIterator vend  = vector__end(v);

  for (; viter != vend; ++viter) {
    *viter += 100;
  }

  LOG_MESSAGE("VectorTest.VectorConcept: vector__at");
  for (int i = 0; i < vector__size(vcopy); i++) {
    ASSERT_EQ(vector__at(v, i), vector__at(vcopy, i) + 100);
  }

  LOG_MESSAGE("VectorTest.VectorConcept: vector__assign(v_empty)");
  Vector * v_empty = vector__new();
  vector__assign(v, v_empty);

  ASSERT_EQ(1, vector__equals(v,v_empty));
  ASSERT_EQ(0, vector__size(v));
  ASSERT_EQ(1, vector__empty(v));
}

TEST_F(VectorTest, VectorFIFO)
{
  LOG_MESSAGE("VectorTest.VectorFIFO: vector__new");
  Vector * v = vector__new();

  LOG_MESSAGE("VectorTest.VectorFIFO: vector__push_front(...)");
  vector__push_front(v, 444);
  vector__push_front(v, 333);
  vector__push_front(v, 222);
  vector__push_front(v, 111);
  ASSERT_EQ(4,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorFIFO: vector__pop_back(...)");
  ASSERT_EQ(444, vector__pop_back(v));
  ASSERT_EQ(333, vector__pop_back(v));
  ASSERT_EQ(222, vector__pop_back(v));
  ASSERT_EQ(111, vector__pop_back(v));
  ASSERT_EQ(0,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorFIFO: vector__push_back(...)");
  vector__push_back(v, 111);
  vector__push_back(v, 222);
  vector__push_back(v, 333);
  vector__push_back(v, 444);
  ASSERT_EQ(4,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorFIFO: vector__pop_front(...)");
  ASSERT_EQ(111, vector__pop_front(v));
  ASSERT_EQ(222, vector__pop_front(v));
  ASSERT_EQ(333, vector__pop_front(v));
  ASSERT_EQ(444, vector__pop_front(v));
  ASSERT_EQ(0,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorFIFO: vector__delete");
  vector__delete(v);
}

TEST_F(VectorTest, VectorLIFO)
{
  LOG_MESSAGE("VectorTest.VectorLIFO: vector__new");
  Vector * v = vector__new();

  LOG_MESSAGE("VectorTest.VectorLIFO: vector__push_front(...)");
  vector__push_front(v, 444);
  vector__push_front(v, 333);
  vector__push_front(v, 222);
  vector__push_front(v, 111);
  ASSERT_EQ(4,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorLIFO: vector__pop_front(...)");
  ASSERT_EQ(111, vector__pop_front(v));
  ASSERT_EQ(222, vector__pop_front(v));
  ASSERT_EQ(333, vector__pop_front(v));
  ASSERT_EQ(444, vector__pop_front(v));
  ASSERT_EQ(0,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorLIFO: vector__push_back(...)");
  vector__push_back(v, 111);
  vector__push_back(v, 222);
  vector__push_back(v, 333);
  vector__push_back(v, 444);
  ASSERT_EQ(4,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorLIFO: vector__pop_back(...)");
  ASSERT_EQ(444, vector__pop_back(v));
  ASSERT_EQ(333, vector__pop_back(v));
  ASSERT_EQ(222, vector__pop_back(v));
  ASSERT_EQ(111, vector__pop_back(v));
  ASSERT_EQ(0,   vector__size(v));

  LOG_MESSAGE("VectorTest.VectorLIFO: vector__delete");
  vector__delete(v);
}
