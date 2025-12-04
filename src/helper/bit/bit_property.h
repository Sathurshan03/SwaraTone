/**
 *******************************************************************************
 * @file    bit_property.h
 * @brief   bits property header.
 *******************************************************************************
 */

#pragma once

/**
 * @brief Checks whether only one bit is set in the input.
 *
 * @param num Input number.
 * @return true when only one bit is set in the input, otherwise false.
 */
bool inline check1BitSet(unsigned int num) {
  return (num != 0) && (num & (num - 1)) == 0;
}
