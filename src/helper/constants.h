/**
 *******************************************************************************
 * @file    constants.h
 * @brief   Project constants definitions.
 *******************************************************************************
 */

#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include <cstdint>

// Constants
const uint16_t BITS_PER_SAMPLE = 16U;

const uint32_t BYTE_SIZE = 8U;

const uint32_t SAMPLE_RATE = 44100U;

const uint32_t WINDOW_SIZE = 4096U;

const uint32_t HALF_WINDOW_SIZE = WINDOW_SIZE / 2;

const double PI = M_PI;

// Host device endian detection.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
constexpr bool HOST_IS_BIG_ENDIAN = true;
#elif defined(_BIG_ENDIAN) || defined(__BIG_ENDIAN__) || defined(__ARMEB__) || \
    defined(__MIPSEB__)
constexpr bool HOST_IS_BIG_ENDIAN = true;
#else
constexpr bool HOST_IS_BIG_ENDIAN = false;
#endif
