#ifndef CPPPC__01__VECTOR_TEST_H__INCLUDED
#define CPPPC__01__VECTOR_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class VectorTest : public ::testing::Test {

public:

  VectorTest() {
    LOG_MESSAGE("Opening test suite: VectorTest");
  }

  virtual ~VectorTest() {
    LOG_MESSAGE("Closing test suite: VectorTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__01__VECTOR_TEST_H__INCLUDED
