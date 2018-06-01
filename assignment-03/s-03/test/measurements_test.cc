
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "measurements_test.h"

#include <solution/measurements.h>
#include <gtest/gtest.h>

#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>


using cpppc::Measurements;

template <typename Iter>
void print_range(
  const std::string & name,
  const Iter        & begin,
  const Iter        & end)
{
  std::ostringstream oss;
  for (auto it = begin; it != end; ++it) {
    oss << std::setw(4) << std::fixed << *it << " ";
  }
  LOG_MESSAGE("%*s: {%s}", 10, name.c_str(), oss.str().c_str());
}

TEST_F(MeasurementsTest, SequenceContainerConcept)
{
  Measurements<int> m1;
  ASSERT_EQ(m1, m1);

  ASSERT_EQ(m1.size(), 0);
  ASSERT_EQ(m1.end() - m1.begin(), 0);
  ASSERT_TRUE(m1.empty());

  m1.insert(10);
  m1.insert(100);
  m1.insert(30);

  print_range("m1", m1.begin(), m1.end());

  ASSERT_EQ(m1.size(), 3);
  ASSERT_EQ(m1.end() - m1.begin(), 3);

  ASSERT_EQ(m1[0], 10);
  ASSERT_EQ(m1[1], 100);
  ASSERT_EQ(m1[2], 30);

  Measurements<int> m2;
  std::vector<int>  v({ 20, 40, 100 });
  m2.insert(v.begin(), v.end());
  ASSERT_EQ(m2, m2);
  ASSERT_EQ(m2.size(), 3);

  print_range("m2", m2.begin(), m2.end());

  m2[1] = 200;
  ASSERT_EQ(m2[1], 200);
  ASSERT_EQ(*(m2.begin() + 1), 200);

  print_range("m2'", m2.begin(), m2.end());

  Measurements<int> m3(m2);
  ASSERT_EQ(m2, m3);

  ASSERT_EQ(20,  m3.front());
  ASSERT_EQ(100, m3.back());

  m3 = m1;
  ASSERT_EQ(m1, m3);

  print_range("m3", m3.begin(), m3.end());
}

TEST_F(MeasurementsTest, MeasurementsConcept)
{
  Measurements<int> m;

  ASSERT_EQ(0, m.mean());
  ASSERT_EQ(0, m.median());

  std::vector<int> v1 = { 10, 22, 25, 24, 26 };
  m.insert(v1.begin(), v1.end());

  print_range("m", m.begin(), m.end());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: mean:   %f",
              m.mean());
  ASSERT_DOUBLE_EQ(21.4, m.mean());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: median: %d",
              m.median());
  ASSERT_EQ(24, m.median());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: var:    %f",
              m.variance());
  ASSERT_DOUBLE_EQ(34.24, m.variance());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: sigma:  %f",
              m.sigma());

  m.clear();
  std::vector<int> v2 = { 1, 2, 3, 4, 3, 2, 1 };
  m.insert(v2.begin(), v2.end());

  print_range("m", m.begin(), m.end());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: mean:   %f",
              m.mean());
  ASSERT_DOUBLE_EQ(2.286, round(m.mean() * 1000) / 1000);

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: median: %d",
              m.median());
  ASSERT_EQ(2, m.median());

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: var:    %f",
              m.variance());
  ASSERT_DOUBLE_EQ(1.061, round(m.variance() * 1000) / 1000);

  LOG_MESSAGE("MeasurementsTest.MeasurementsConcept: sigma:  %f",
              m.sigma());
  ASSERT_DOUBLE_EQ(1.030, round(m.sigma() * 1000) / 1000);
}


