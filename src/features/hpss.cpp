/**
 *******************************************************************************
 * @file    hpss.cpp
 * @brief   Harmonic Percussice Source Separation (HPSS) source.
 *******************************************************************************
 */

#include "hpss.h"

#include "constants.h"
#include "fft.h"
#include "fft_helper.hpp"
#include "frequencyDomain.h"
#include "logging.h"
#include "matrix.hpp"
#include "powers.hpp"
#include "windowing_functions.h"

void runHPSS(std::vector<double>& in, std::vector<double>& harmonics,
             std::vector<double>& percussive) {
  LOG_INFO("Running HPSS.");

  // Clean up vector sizes.
  if (harmonics.size() != in.size()) {
    harmonics.resize(in.size());
  }

  if (percussive.size() != in.size()) {
    percussive.resize(in.size());
  }

  // Initialize power spectrum matrix. Subtract 1 from column size to avoid
  // partially filled window.
  size_t r = getNyquistSize(WINDOW_SIZE);
  size_t c = (in.size() / HALF_WINDOW_SIZE) - 1;
  Matrix powerSpectrumTs{r, c};

  // 1. Compute FFT on input signal.
  LOG_INFO("Computing FFT on input signal");
  frequencyDomain X;
  initFrequncyDomain(WINDOW_SIZE, X);
  std::vector<double> powerSpectrum(WINDOW_SIZE);

  for (size_t i = 0; i < c; i++) {
    double* x = in.data() + i * HALF_WINDOW_SIZE;

    applyHanningWindow(x, WINDOW_SIZE);
    runFFT(x, WINDOW_SIZE, X);

    // Create power spectrum.
    for (size_t j = 0; j < r; j++) {
      powerSpectrumTs(j, i) = std::norm(X.frequency[j]);
    }
  }

  // 2. Apply median filtering.

  // 3. Apply mask.

  // 4. Get final components.
}
