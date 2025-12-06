/**
 ******************************************************************************
 * @file    bit_properties_test.cpp
 * @brief   Unit tests for bit property operations.
 ******************************************************************************
 */

#include "bit_property.h"

#include <gtest/gtest.h>

/** @brief Verifies that the one bit set checker correctly identifies values
 * with exactly one bit set. */
TEST(BitProperty, OneBitSetTrue) {
  unsigned int num = 1U;

  // Bit shift a single bit and assert that one bit set checker detects the
  // single set bit.
  for (int i = 0; i < 32; i++) {
    ASSERT_TRUE(check1BitSet(num));
    num <<= 1;
  }
}

/** @brief Verifies that the one bit set checker does not report false
 * positives. */
TEST(BitProperty, OneBitSetFalse) {
  unsigned int num = 3U;

  // bit shift the two bits and assert that the one bit checker does not report
  // that a single bit is set.
  for (int i = 0; i < 31; i++) {
    ASSERT_FALSE(check1BitSet(num));
    num <<= 1;
  }
}
