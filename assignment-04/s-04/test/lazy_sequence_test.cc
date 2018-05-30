
#include "lazy_sequence_test.h"

#include <solution/lazy_sequence.h>

#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

using namespace cpppc;


TEST_F(LazySequenceTest, StandardConcept)
{
  LOG_MESSAGE("LazySequenceTest.StandardConcept: default ctor");
  lazy_sequence<int> sa1 { };
  lazy_sequence<int> sa2 { };

  LOG_MESSAGE("LazySequenceTest.StandardConcept: ==");
  ASSERT_EQ(sa1, sa1);
  ASSERT_EQ(sa2, sa2);

  ASSERT_EQ(0, sa1.size());
  ASSERT_EQ(0, sa2.size());

  sa1 = lazy_sequence<int> { 100,
                             [](int idx) {
                               return idx + 100;
                             } 
                           };

  LOG_MESSAGE("LazySequenceTest.StandardConcept: =");
  sa2 = sa1;
  ASSERT_EQ(sa1, sa2);
  ASSERT_EQ(sa2, sa1);
}

TEST_F(LazySequenceTest, RandomAccess)
{
  LOG_MESSAGE("LazySequenceTest.RandomAccess");

  lazy_sequence<int> sa { 100,
                          [](int idx) {
                            return idx + 100;
                          } 
                        };

  auto it = sa.begin() + 23;

  ASSERT_EQ(it,       std::find(sa.begin(), sa.end(),  123));
  ASSERT_EQ(sa.end(), std::find(sa.begin(), sa.end(), 2340));

  int idx = 0;
  std::for_each(sa.begin(),
                sa.end(),
                [&](int v) { ASSERT_EQ(100 + idx, v); ++idx; });
}

TEST_F(LazySequenceTest, ArrayInterface)
{
  LOG_MESSAGE("LazySequenceTest.ArrayInterface");

  lazy_sequence<int> sa1;
  lazy_sequence<int> sa2;

  ASSERT_TRUE(sa1.empty());
  ASSERT_TRUE(sa2.empty());

  lazy_sequence<int> sa { 100,
                          [](int idx) {
                            return idx + 100;
                          } 
                        };

  ASSERT_EQ(*sa.begin(), sa.front());
  ASSERT_EQ(*sa.begin(), 100);

  ASSERT_EQ(sa2.begin(), std::find(sa2.begin(), sa2.end(), 100));

  int idx = 0;
  std::for_each(sa2.begin(),
                sa2.end(),
                [&](int v) { ASSERT_EQ(100 + idx, v); ++idx; });

  LOG_MESSAGE("LazySequenceTest.ArrayInterface: sa = { %s }",
              range_to_string(sa.begin(), sa.begin() + 16).c_str());
}

