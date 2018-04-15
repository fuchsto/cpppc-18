#ifndef CPPPC__01__STACK_TEST_H__INCLUDED
#define CPPPC__01__STACK_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class StackTest : public ::testing::Test {

public:

  StackTest() {
    LOG_MESSAGE("Opening test suite: StackTest");
  }

  virtual ~StackTest() {
    LOG_MESSAGE("Closing test suite: StackTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__01__STACK_TEST_H__INCLUDED
