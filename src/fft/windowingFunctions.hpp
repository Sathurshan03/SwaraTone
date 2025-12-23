/**
 *******************************************************************************
 * @file    windowingFunctions.hpp
 * @brief   Windowing functions header.
 *******************************************************************************
 */

#pragma once

#include "constants.h"

/**
 * @brief Apply Haning Windowing function to input signal.
 *
 * @param[in,out] x Input signal.
 * @param[in] N Size of input signal.
 */
void applyHanningWindow(double* x, int N);

/**
 * @brief Get the Handding window weight based on index position.
 *
 * @param n Window index position.
 * @param N Window size.
 * @return double
 */
inline double getHanningWindowWeight(int n, int N) {
  return 0.5 * (1.0 - std::cos(2.0 * PI * n / (N - 1)));
}
