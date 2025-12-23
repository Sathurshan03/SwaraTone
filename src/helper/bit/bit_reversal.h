/**
 *******************************************************************************
 * @file    bit_reversal.h
 * @brief   Bit reversal header.
 *******************************************************************************
 */

#pragma once

#include <cstdint>
#include <map>

/** @brief Look up table for bit reversal in a nibble. */
extern std::map<uint8_t, uint8_t> NIBBLE_REVERSAL_TABLE;

/**
 * @brief Reverses the bits of a 16 bit type.
 *
 * @param[in] in 16 bit input.
 * @return uint16_t reversed bits of @ref in.
 */
uint16_t bitReversal16(uint16_t in);

/**
 * @brief Reverses the bits of a 32 bit type.
 *
 * @param[in] in 32 bit input.
 * @return uint32_t reversed bits of @ref in.
 */
uint32_t bitReversal32(uint32_t in);
