
#include "find_mean_rep_test.h"

#include <solution/find_mean_rep.h>

#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using cpppc::find_mean_rep;

TEST_F(FindMeanRepTest, RandomAccessIterators)
{
  LOG_MESSAGE("FindMeanRepTest.RandomAccessIterators");
  std::vector<int> v_empty;
  ASSERT_EQ(v_empty.end(), find_mean_rep(v_empty.begin(), v_empty.end()));

  std::vector<int> v1 { 5, 0, 10, 5 };
  ASSERT_EQ(v1.begin(), find_mean_rep(v1.begin(), v1.end()));

  std::vector<int> v2 { -5, 0, -10, -5 };
  ASSERT_EQ(v2.begin(), find_mean_rep(v2.begin(), v2.end()));

  std::vector<int> v3 { 9, 0, -10, -5, 0, 1 };
  ASSERT_EQ(v3.begin() + 1, find_mean_rep(v3.begin(), v3.end()));

  std::vector<int> v4 { 9, 0, -10, -5, 0, 1, std::numeric_limits<int>::max() };
  ASSERT_EQ(v4.begin(), find_mean_rep(v4.begin(), v4.end()));

  std::vector<double> v5 { 9, 0, -10, -5, 0, 1 };
  ASSERT_EQ(v5.begin() + 1, find_mean_rep(v5.begin(), v5.end()));
}

TEST_F(FindMeanRepTest, InputIterators)
{
  LOG_MESSAGE("FindMeanRepTest.InputIterators");
  std::list<int> v_empty;
  ASSERT_EQ(v_empty.end(), find_mean_rep(v_empty.begin(), v_empty.end()));

  std::list<int> v1 { 5, 0, 10, 5 };
  ASSERT_EQ(v1.begin(), find_mean_rep(v1.begin(), v1.end()));

  std::list<int> v2 { -5, 0, -10, -5 };
  ASSERT_EQ(v2.begin(), find_mean_rep(v2.begin(), v2.end()));

  std::list<int> v3 { 9, 0, -10, -5, 0, 1 };
  ASSERT_EQ(++v3.begin(), find_mean_rep(v3.begin(), v3.end()));

  std::list<int> v4 { 9, 0, -10, -5, 0, 1, std::numeric_limits<int>::max() };
  ASSERT_EQ(v4.begin(), find_mean_rep(v4.begin(), v4.end()));

  std::list<double> v5 { 9, 0, -10, -5, 0, 1 };
  ASSERT_EQ(++v5.begin(), find_mean_rep(v5.begin(), v5.end()));
}

