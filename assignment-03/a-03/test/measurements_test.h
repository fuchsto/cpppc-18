#ifndef CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED
#define CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class MeasurementsTest : public ::testing::Test {

public:

  MeasurementsTest() {
    LOG_MESSAGE("Opening test suite: MeasurementsTest");
  }

  virtual ~MeasurementsTest() {
    LOG_MESSAGE("Closing test suite: MeasurementsTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A02__MEASUREMENTS_TEST_H__INCLUDED
