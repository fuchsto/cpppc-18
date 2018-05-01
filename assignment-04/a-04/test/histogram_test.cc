
#include "histogram_test.h"

#include <solution/histogram.h>

#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <list>


TEST_F(HistogramTest, RandomAccessIterators)
{
  LOG_MESSAGE("HistogramTest.RandomAccessIterators");
  std::vector<int> v_empty;
  ASSERT_EQ(v_empty.end(), histogram(v_empty.begin(), v_empty.end()));

  std::vector<int> v1 { 1, 5, 5, 3, 4, 1, 5, 7 };

  auto h1_end = histogram(v1.begin(), v1.end());

  LOG_MESSAGE("HistogramTest.RandomAccessIterators: histogram v1: %s",
              range_to_string(v1.begin(), h1_end).c_str());

  std::vector<int> h1_exp { 2, 3, 1, 1, 1 };

  ASSERT_EQ(std::distance(h1_exp.begin(), h1_exp.end()),
            std::distance(v1.begin(), h1_end));
  ASSERT_TRUE(std::equal(h1_exp.begin(), h1_exp.end(), v1.begin()));

  std::array<size_t, 7> v2 {{ 10, 52, 31415, 52, 23, 31415, 1001 }};
  auto h2_end = histogram(v2.begin(), v2.end());

  std::vector<int> h2_exp { 1, 2, 2, 1, 1 };

  ASSERT_EQ(std::distance(h2_exp.begin(), h2_exp.end()),
            std::distance(v2.begin(), h2_end));
  ASSERT_TRUE(std::equal(h2_exp.begin(), h2_exp.end(), v2.begin()));

  LOG_MESSAGE("HistogramTest.RandomAccessIterators: histogram v2: %s",
              range_to_string(v2.begin(), h2_end).c_str());
}

TEST_F(HistogramTest, BidirectionalIterators)
{
  LOG_MESSAGE("HistogramTest.BidirectionalIterators");

  std::list<size_t> v2 {{ 10, 52, 31415, 52, 23, 31415, 1001 }};
  auto h2_end = histogram(v2.begin(), v2.end());

  std::vector<int> h2_exp { 1, 2, 2, 1, 1 };

  ASSERT_EQ(std::distance(h2_exp.begin(), h2_exp.end()),
            std::distance(v2.begin(), h2_end));
  ASSERT_TRUE(std::equal(h2_exp.begin(), h2_exp.end(), v2.begin()));

  LOG_MESSAGE("HistogramTest.RandomAccessIterators: histogram v2: %s",
              range_to_string(v2.begin(), h2_end).c_str());
}

