/**
 *******************************************************************************
 * @file    highPass.cpp
 * @brief   High pass filter source.
 *******************************************************************************
 */

#include "highPass.h"

#include <cmath>

#include "constants.h"

void digitalHighPass(const std::vector<double>& x, std::vector<double>& y,
                     double fc, double fs) {
  size_t signalSize = x.size();

  // Size verification.
  if (signalSize != y.size()) {
    y.resize(signalSize);
  }

  // Compute constants.
  const double K = std::tan(PI * fc / fs);
  const double D = 1 + sqrt(2) * K + K * K;

  const double B0 = 1 / D;
  const double B1 = -2 / D;
  const double B2 = B0;
  const double A1 = -2 * (K * K - 1) / D;
  const double A2 = -(1 - sqrt(2) * K + K * K) / D;

  // Apply high pass filter.
  if (signalSize >= 1) {
    y[0] = B0 * x[0];
  }

  if (signalSize >= 2) {
    y[1] = B0 * x[1] + B1 * x[0] + A1 * y[0];
  }

  for (size_t n = 2; n < signalSize; n++) {
    y[n] = B0 * x[n] + B1 * x[n - 1] + B2 * x[n - 2] + A1 * y[n - 1] +
           A2 * y[n - 2];
  }
}