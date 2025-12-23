/**
 *******************************************************************************
 * @file    endian.h
 * @brief   Endian header.
 *******************************************************************************
 */

#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Swaps endian for 2 bytes. Big endian -> little endian or vice versa.
 *
 * @param[in] in Input with 2 bytes.
 * @return uint16_t endian swapped value of the input.
 */
uint16_t endianSwap2B(uint16_t in);

/**
 * @brief Swaps endian for 4 bytes. Big endian -> little endian or vice versa.
 *
 * @param[in] in Input with 4 bytes.
 * @return uint32_t endian swapped value of the input.
 */
uint32_t endianSwap4B(uint32_t in);

/**
 * @brief Convert to little endian.
 *
 * @param[in] in input with 2 bytes
 * @return uint16_t Little endian representation of the input.
 */
uint16_t convertToLE2B(uint16_t in);

/**
 * @brief Convert to little endian.
 *
 * @param[in] in input with 4 bytes
 * @return uint16_t Little endian representation of the input.
 */
uint32_t convertToLE4B(uint32_t in);

#ifdef __cplusplus
}
#endif