/**
 *******************************************************************************
 * @file    bit_reversal.cpp
 * @brief   Bit reversal source.
 *******************************************************************************
 */

#include "bit_reversal.h"

std::map<uint8_t, uint8_t> NIBBLE_REVERSAL_TABLE = {
    {0x0, 0x0}, {0x1, 0x8}, {0x2, 0x4}, {0x3, 0xc}, {0x4, 0x2}, {0x5, 0xa},
    {0x6, 0x6}, {0x7, 0xe}, {0x8, 0x1}, {0x9, 0x9}, {0xa, 0x5}, {0xb, 0xd},
    {0xc, 0x3}, {0xd, 0xb}, {0xe, 0x7}, {0xf, 0xf}};

uint16_t bitReversal16(uint16_t in) {
  return NIBBLE_REVERSAL_TABLE[(in >> 0) & 0xf] << 12 |
         NIBBLE_REVERSAL_TABLE[(in >> 4) & 0xf] << 8 |
         NIBBLE_REVERSAL_TABLE[(in >> 8) & 0xf] << 4 |
         NIBBLE_REVERSAL_TABLE[(in >> 12) & 0xf];
}

uint32_t bitReversal32(uint32_t in) {
  return NIBBLE_REVERSAL_TABLE[(in >> 0) & 0xf] << 28 |
         NIBBLE_REVERSAL_TABLE[(in >> 4) & 0xf] << 24 |
         NIBBLE_REVERSAL_TABLE[(in >> 8) & 0xf] << 20 |
         NIBBLE_REVERSAL_TABLE[(in >> 12) & 0xf] << 16 |
         NIBBLE_REVERSAL_TABLE[(in >> 16) & 0xf] << 12 |
         NIBBLE_REVERSAL_TABLE[(in >> 20) & 0xf] << 8 |
         NIBBLE_REVERSAL_TABLE[(in >> 24) & 0xf] << 4 |
         NIBBLE_REVERSAL_TABLE[(in >> 28) & 0xf];
}
