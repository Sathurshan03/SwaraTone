/**
 ******************************************************************************
 * @file    bit_reversal.cpp
 * @brief   Unit tests for bit reversal.
 ******************************************************************************
 */

#include "bit_reversal.h"

#include <gtest/gtest.h>

/**
 * @brief Tests bit reversal correctly for 16 bits.
 */
TEST(BitReversal, bits16) {
  std::map<uint16_t, uint16_t> inputMap{{0x0001, 0x8000}, {0x0002, 0x4000}};

  for (const auto& [in, expOut] : inputMap) {
    ASSERT_EQ(bitReversal16(in), expOut);
  }
}

// TODO do property based testing of reversal of reversal gives original back.
