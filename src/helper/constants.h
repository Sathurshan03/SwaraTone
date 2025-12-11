/**
 *******************************************************************************
 * @file    constants.h
 * @brief   Project constants definitions.
 *******************************************************************************
 */

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdint>

const double PI = M_PI;

const uint32_t BYTE_SIZE = 8;

// Host device endian detection.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
constexpr bool HOST_IS_BIG_ENDIAN = true;
#elif defined(_BIG_ENDIAN) || defined(__BIG_ENDIAN__) || defined(__ARMEB__) || \
    defined(__MIPSEB__)
constexpr bool HOST_IS_BIG_ENDIAN = true;
#else
constexpr bool HOST_IS_BIG_ENDIAN = false;
#endif
