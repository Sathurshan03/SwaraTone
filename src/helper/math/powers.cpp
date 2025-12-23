/**
 *******************************************************************************
 * @file    powers.cpp
 * @brief   Powers source code.
 *******************************************************************************
 */

#include "powers.hpp"

void applyPowerSpectrum(const std::vector<std::complex<double>>& in,
                        std::vector<double>& powerSpectrum) {
  if (powerSpectrum.size() != in.size()) {
    powerSpectrum.resize(in.size());
  }
  for (size_t i = 0; i < in.size(); i++) {
    powerSpectrum[i] = std::norm(in[i]);
  }
}
