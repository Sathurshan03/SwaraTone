/**
 *******************************************************************************
 * @file    windowing_functions.cpp
 * @brief   Windowing functions source.
 *******************************************************************************
 */

#include "windowing_functions.hpp"

#include "constants.h"

void applyHanningWindow(double* x, int N) {
  for (int n = 0; n < N; n++) {
    double w = 0.5 * (1.0 - std::cos(2.0 * PI * n / (N - 1)));
    double xn = x[n] * w;
    x[n] = xn;
  }
}
