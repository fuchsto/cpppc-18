#ifndef CPPPC__A03__FIND_MEAN_REP_TEST_H__INCLUDED
#define CPPPC__A03__FIND_MEAN_REP_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class FindMeanRepTest : public ::testing::Test {

public:

  FindMeanRepTest() {
    LOG_MESSAGE("Opening test suite: FindMeanRepTest");
  }

  virtual ~FindMeanRepTest() {
    LOG_MESSAGE("Closing test suite: FindMeanRepTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__FIND_MEAN_REP_TEST_H__INCLUDED
