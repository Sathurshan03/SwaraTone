/**
 *******************************************************************************
 * @file    windowingFunctions.cpp
 * @brief   Windowing functions source.
 *******************************************************************************
 */

#include "windowingFunctions.hpp"

#include "constants.h"

void applyHanningWindow(double* x, int N) {
  for (int n = 0; n < N; n++) {
    double w = std::sin(PI * n / (N - 1)) * std::sin(PI * n / (N - 1));
    double xn = x[n] * w;
    x[n] = xn;
  }
}

void applySqrtHanningWindow(double* x, int N) {
  for (int n = 0; n < N; n++) {
    double w = std::sin(PI * n / (N - 1));
    double xn = x[n] * w;
    x[n] = xn;
  }
}