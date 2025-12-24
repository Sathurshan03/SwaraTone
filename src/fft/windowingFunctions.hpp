/**
 *******************************************************************************
 * @file    windowingFunctions.hpp
 * @brief   Windowing functions header.
 *******************************************************************************
 */

#pragma once

#include <cmath>

#include "constants.h"


/**
 * @brief Apply Hanning Windowing function to input signal.
 *
 * @param[in,out] x Input signal.
 * @param[in] N Size of input signal.
 */
void applyHanningWindow(double* x, int N);

/**
 * @brief Apply square root Hanning Windowing function to input signal.
 *
 * @param[in,out] x Input signal.
 * @param[in] N Size of input signal.
 */
void applySqrtHanningWindow(double* x, int N);

/**
 * @brief Get the Hannning window weight based on index position.
 *
 * @param n Window index position.
 * @param N Window size.
 * @return double
 */
inline double getHanningWindowWeight(int n, int N) {
  return std::sin(PI * n / (N - 1)) * std::sin(PI * n / (N - 1));
}

/**
 * @brief Get the square Hannning window weight based on index position.
 *
 * @param n Window index position.
 * @param N Window size.
 * @return double
 */
inline double getSqrtHanningWindowWeight(int n, int N) {
  return std::sin(PI * n / (N - 1));
}
