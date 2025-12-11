/**
 *******************************************************************************
 * @file    powers.h
 * @brief   Powers header file.
 *******************************************************************************
 */

#pragma once

#include <cstdint>

#include "bit_property.h"

/**
 * @brief Check whether input is a power of 2. Input must be unsinged int.
 *
 * @param num Input
 * @return true Input is a power of 2. False otherwise.
 */
bool inline checkPower2(uint32_t num) { return check1BitSet(num); };
