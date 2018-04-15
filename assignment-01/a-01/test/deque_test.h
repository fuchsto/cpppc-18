#ifndef CPPPC__01__DEQUE_TEST_H__INCLUDED
#define CPPPC__01__DEQUE_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class DequeTest : public ::testing::Test {

public:

  DequeTest() {
    LOG_MESSAGE("Opening test suite: DequeTest");
  }

  virtual ~DequeTest() {
    LOG_MESSAGE("Closing test suite: DequeTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__01__DEQUE_TEST_H__INCLUDED
