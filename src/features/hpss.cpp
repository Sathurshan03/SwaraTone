/**
 *******************************************************************************
 * @file    hpss.cpp
 * @brief   Harmonic Percussice Source Separation (HPSS) source.
 *******************************************************************************
 */

#include "hpss.h"

#include "logging.h"

void runHPSS(const std::vector<double>& in, std::vector<double>& harmonics,
             std::vector<double>& percussive) {
  LOG_INFO("Running HPSS.");

  // Clean up vector sizes.

  // 1. Compute FFT on input signal.

  // Apply window.

  // 2. Apply power spectrum.

  // 3. Apply median filtering.

  // 4. Apply mask.

  // 5. Get final components.
}
