
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "deque_test.h"

#include <solution/deque.h>
#include <gtest/gtest.h>


TEST_F(DequeTest, StandardConcept)
{
  LOG_MESSAGE("DequeTest.StandardConcept: deque__new");
  Deque * d1 = deque__new();
  Deque * d2 = deque__new();

  LOG_MESSAGE("DequeTest.StandardConcept: deque__equals");
  ASSERT_EQ(1, deque__equals(d1,d2));

  deque__push_back(d1, 12);
  deque__push_back(d1, 34);

  ASSERT_EQ(0, deque__equals(d1,d2));

  LOG_MESSAGE("DequeTest.StandardConcept: deque__assign");
  deque__assign(d2, d1);

  ASSERT_EQ(1, deque__equals(d1,d2));

  LOG_MESSAGE("DequeTest.StandardConcept: deque__copy");
  Deque * d3 = deque__copy(d1);

  ASSERT_EQ(1, deque__equals(d1,d3));

  deque__delete(d1);
  deque__delete(d2);
  deque__delete(d3);
}

TEST_F(DequeTest, DequeConcept)
{
  LOG_MESSAGE("DequeTest.DequeConcept: deque__new");
  Deque * d = deque__new();

  ASSERT_EQ(0, deque__size(d));
  ASSERT_EQ(1, deque__empty(d));

  LOG_MESSAGE("DequeTest.DequeConcept: deque__push_back(56)");
  deque__push_back(d, 56);
  LOG_MESSAGE("DequeTest.DequeConcept: deque__push_back(78)");
  deque__push_back(d, 78);
  LOG_MESSAGE("DequeTest.DequeConcept: deque__push_back(90)");
  deque__push_back(d, 90);

  ASSERT_EQ(3, deque__size(d));
  ASSERT_EQ(0, deque__empty(d));

  LOG_MESSAGE("DequeTest.DequeConcept: deque__push_front(34)");
  deque__push_front(d, 34);
  LOG_MESSAGE("DequeTest.DequeConcept: deque__push_front(12)");
  deque__push_front(d, 12);

  ASSERT_EQ(5, deque__size(d));
  deque__push_front(d, 111);
  deque__push_front(d, 222);
  ASSERT_EQ(222, deque__pop_front(d));
  ASSERT_EQ(111, deque__pop_front(d));
  ASSERT_EQ(5, deque__size(d));

  LOG_MESSAGE("DequeTest.DequeConcept: deque__assign(d_empty)");
  Deque * d_empty = deque__new();
  deque__assign(d, d_empty);

  ASSERT_EQ(1, deque__equals(d,d_empty));
  ASSERT_EQ(0, deque__size(d));
  ASSERT_EQ(1, deque__empty(d));

  LOG_MESSAGE("DequeTest.DequeConcept: deque__delete");
  deque__delete(d);
  deque__delete(d_empty);
}

TEST_F(DequeTest, DequeFIFO)
{
  LOG_MESSAGE("DequeTest.DequeFIFO: deque__new");
  Deque * d = deque__new();

  LOG_MESSAGE("DequeTest.DequeFIFO: deque__push_front(...)");
  deque__push_front(d, 444);
  deque__push_front(d, 333);
  deque__push_front(d, 222);
  deque__push_front(d, 111);
  ASSERT_EQ(4,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeFIFO: deque__pop_back(...)");
  ASSERT_EQ(444, deque__pop_back(d));
  ASSERT_EQ(333, deque__pop_back(d));
  ASSERT_EQ(222, deque__pop_back(d));
  ASSERT_EQ(111, deque__pop_back(d));
  ASSERT_EQ(0,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeFIFO: deque__push_back(...)");
  deque__push_back(d, 111);
  deque__push_back(d, 222);
  deque__push_back(d, 333);
  deque__push_back(d, 444);
  ASSERT_EQ(4,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeFIFO: deque__pop_front(...)");
  ASSERT_EQ(111, deque__pop_front(d));
  ASSERT_EQ(222, deque__pop_front(d));
  ASSERT_EQ(333, deque__pop_front(d));
  ASSERT_EQ(444, deque__pop_front(d));
  ASSERT_EQ(0,   deque__size(d));

  deque__delete(d);
}

TEST_F(DequeTest, DequeLIFO)
{
  LOG_MESSAGE("DequeTest.DequeLIFO: deque__new");
  Deque * d = deque__new();

  LOG_MESSAGE("DequeTest.DequeLIFO: deque__push_front(...)");
  deque__push_front(d, 444);
  deque__push_front(d, 333);
  deque__push_front(d, 222);
  deque__push_front(d, 111);
  ASSERT_EQ(4,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeLIFO: deque__pop_front(...)");
  ASSERT_EQ(111, deque__pop_front(d));
  ASSERT_EQ(222, deque__pop_front(d));
  ASSERT_EQ(333, deque__pop_front(d));
  ASSERT_EQ(444, deque__pop_front(d));
  ASSERT_EQ(0,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeLIFO: deque__push_back(...)");
  deque__push_back(d, 111);
  deque__push_back(d, 222);
  deque__push_back(d, 333);
  deque__push_back(d, 444);
  ASSERT_EQ(4,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeLIFO: deque__pop_back(...)");
  ASSERT_EQ(444, deque__pop_back(d));
  ASSERT_EQ(333, deque__pop_back(d));
  ASSERT_EQ(222, deque__pop_back(d));
  ASSERT_EQ(111, deque__pop_back(d));
  ASSERT_EQ(0,   deque__size(d));

  LOG_MESSAGE("DequeTest.DequeLIFO: deque__delete");
  deque__delete(d);
}
