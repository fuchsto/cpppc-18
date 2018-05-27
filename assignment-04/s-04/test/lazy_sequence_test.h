#ifndef CPPPC__A03__LAZY_SEQUENCE_TEST_H__INCLUDED
#define CPPPC__A03__LAZY_SEQUENCE_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class LazySequenceTest : public ::testing::Test {

public:

  LazySequenceTest() {
    LOG_MESSAGE("Opening test suite: LazySequenceTest");
  }

  virtual ~LazySequenceTest() {
    LOG_MESSAGE("Closing test suite: LazySequenceTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__LAZY_SEQUENCE_TEST_H__INCLUDED
