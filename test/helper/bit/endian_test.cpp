/**
 ******************************************************************************
 * @file    endian_test.cpp
 * @brief   Unit tests for endian.
 ******************************************************************************
 */

#include "endian.h"

#include <gtest/gtest.h>

/** @brief Tests endian swap correctly for 2 bytes. */
TEST(EndianSwap, bytes2) {
  std::map<uint16_t, uint16_t> inputMap{{0x0001, 0x0100}, {0xaf00, 0x00af}};

  for (const auto& [in, expOut] : inputMap) {
    ASSERT_EQ(endianSwap2B(in), expOut);
  }
}

/** @brief Tests endian swap correctly for 4 bytes. */
TEST(EndianSwap, bytes4) {
  std::map<uint32_t, uint32_t> inputMap{{0x00000001, 0x01000000},
                                        {0x0000af00, 0x00af0000}};

  for (const auto& [in, expOut] : inputMap) {
    ASSERT_EQ(endianSwap4B(in), expOut);
  }
}
