/**
 ******************************************************************************
 * @file    stats_median_test.cpp
 * @brief   Unit tests for stats median function.
 ******************************************************************************
 */

#include <gtest/gtest.h>

#include "stats.h"

/** @brief Tests median on a vector of odd size. */
TEST(StatsMedian, SizeOdd) {
  std::vector<int32_t> input{9, 3, 7, 5, 1};

  ASSERT_EQ(median(input), 5);
}

/** @brief Tests median on a vector of even size. */
TEST(StatsMedian, SizeEven) {
  std::vector<int32_t> input{10, 4, 8, 6, 2, 12};

  ASSERT_EQ(median(input), 7);
}

/** @brief Tests median on a vector of size one. */
TEST(StatsMedian, SizeOne) {
  std::vector<int32_t> input{9};

  ASSERT_EQ(median(input), 9);
}

/** @brief Tests median on a vector of size two. */
TEST(StatsMedian, SizeTwo) {
  std::vector<int32_t> input{10, 14};

  ASSERT_EQ(median(input), 12);
}
