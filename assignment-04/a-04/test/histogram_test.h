#ifndef CPPPC__A03__HISTOGRAM_TEST_H__INCLUDED
#define CPPPC__A03__HISTOGRAM_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class HistogramTest : public ::testing::Test {

public:

  HistogramTest() {
    LOG_MESSAGE("Opening test suite: HistogramTest");
  }

  virtual ~HistogramTest() {
    LOG_MESSAGE("Closing test suite: HistogramTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__HISTOGRAM_TEST_H__INCLUDED
