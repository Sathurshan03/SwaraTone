/**
 *******************************************************************************
 * @file    endian.cpp
 * @brief   Endian source code.
 *******************************************************************************
 */
#include "endian.h"

uint16_t endianSwap2B(uint16_t in) {
  return (in & 0x00ff) << 8 | (in & 0xff00) >> 8;
}

uint32_t endianSwap4B(uint32_t in) {
  return (in & 0x000000ff) << 24 | (in & 0x0000ff00) << 8 |
         (in & 0x00ff0000) >> 8 | (in & 0xff000000) >> 24;
}
