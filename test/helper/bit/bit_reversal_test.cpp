/**
 ******************************************************************************
 * @file    bit_reversal_test.cpp
 * @brief   Unit tests for bit reversal.
 ******************************************************************************
 */

#include "bit_reversal.h"

#include <gtest/gtest.h>

#include <limits>

#include "test_helper.h"

/** @brief Tests bit reversal correctly for 16 bits. */
TEST(BitReversal, bits16) {
  std::map<uint16_t, uint16_t> inputMap{{0x0001, 0x8000}, {0x0002, 0x4000}};

  for (const auto& [in, expOut] : inputMap) {
    ASSERT_EQ(bitReversal16(in), expOut);
  }
}

/** @brief Tests bit reversal correctly for 32 bits. */
TEST(BitReversal, bits32) {
  std::map<uint32_t, uint32_t> inputMap{{0x00000001, 0x80000000},
                                        {0x00000002, 0x40000000}};

  for (const auto& [in, expOut] : inputMap) {
    ASSERT_EQ(bitReversal32(in), expOut);
  }
}

/**
 * @brief Test that bit reversal of on a number twice returns the original
 * number.
 */
TEST(BitReversal, DualReverse) {
  uint16_t num = static_cast<uint16_t>(
      generateRandomInt(0, std::numeric_limits<uint16_t>::max()));

  // Bit reversal on the input twice.
  uint16_t out = bitReversal16(num);
  out = bitReversal16(out);

  // Assert that after dual reversing, the output is the same as the original
  // input.
  ASSERT_EQ(out, num);
}
