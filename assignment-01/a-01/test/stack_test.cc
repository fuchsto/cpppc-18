
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "stack_test.h"

#include <solution/stack.h>
#include <gtest/gtest.h>


TEST_F(StackTest, StandardConcept)
{
  LOG_MESSAGE("StackTest.StandardConcept: stack__new");
  Stack * s1 = stack__new();
  Stack * s2 = stack__new();

  LOG_MESSAGE("StackTest.StandardConcept: stack__equals");
  ASSERT_EQ(1, stack__equals(s1,s2));

  stack__push(s1, 12);
  stack__push(s1, 34);

  ASSERT_EQ(0, stack__equals(s1,s2));

  LOG_MESSAGE("StackTest.StandardConcept: stack__assign");
  stack__assign(s2, s1);

  ASSERT_EQ(1, stack__equals(s1,s2));

  LOG_MESSAGE("StackTest.StandardConcept: stack__copy");
  Stack * s3 = stack__copy(s1);

  ASSERT_EQ(1, stack__equals(s1,s3));

  stack__delete(s1);
  stack__delete(s2);
  stack__delete(s3);
}

TEST_F(StackTest, StackConcept)
{
  LOG_MESSAGE("StackTest.StackConcept: stack__new");
  Stack * s = stack__new();

  ASSERT_EQ(0, stack__size(s));
  ASSERT_EQ(1, stack__empty(s));

  LOG_MESSAGE("StackTest.StackConcept: stack__push(56)");
  stack__push(s, 56);
  LOG_MESSAGE("StackTest.StackConcept: stack__push(78)");
  stack__push(s, 78);
  LOG_MESSAGE("StackTest.StackConcept: stack__push(90)");
  stack__push(s, 90);

  ASSERT_EQ(3, stack__size(s));
  ASSERT_EQ(0, stack__empty(s));

  LOG_MESSAGE("StackTest.StackConcept: stack__assign(s_empty)");
  Stack * s_empty = stack__new();
  stack__assign(s, s_empty);

  ASSERT_EQ(1, stack__equals(s,s_empty));
  ASSERT_EQ(0, stack__size(s));
  ASSERT_EQ(1, stack__empty(s));

  LOG_MESSAGE("StackTest.StackConcept: stack__delete");

  stack__delete(s);
  stack__delete(s_empty);
}

TEST_F(StackTest, StackLIFO)
{
  LOG_MESSAGE("StackTest.StackLIFO: stack__new");
  Stack * s = stack__new();

  LOG_MESSAGE("StackTest.StackLIFO: stack__push_front(...)");
  stack__push(s, 444);
  stack__push(s, 333);
  stack__push(s, 222);
  stack__push(s, 111);
  ASSERT_EQ(4,   stack__size(s));

  LOG_MESSAGE("StackTest.StackLIFO: stack__pop_front(...)");
  ASSERT_EQ(111, stack__pop(s));
  ASSERT_EQ(222, stack__pop(s));
  ASSERT_EQ(333, stack__pop(s));
  ASSERT_EQ(444, stack__pop(s));
  ASSERT_EQ(0,   stack__size(s));

  LOG_MESSAGE("StackTest.StackLIFO: stack__delete");
  stack__delete(s);
}

