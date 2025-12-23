/**
 *******************************************************************************
 * @file    powers.hpp
 * @brief   Powers header file.
 *******************************************************************************
 */

#pragma once

#include <complex>
#include <cstdint>
#include <vector>

#include "bit_property.h"

/**
 * @brief Check whether input is a power of 2. Input must be unsinged int.
 *
 * @param num Input
 * @return true Input is a power of 2. False otherwise.
 */
inline bool checkPower2(uint32_t num) { return check1BitSet(num); };
