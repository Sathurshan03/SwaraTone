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
#include "stats.h"
#include "windowing_functions.h"

static const size_t MEDIAN_FILTER_SIZE = 5;
static const size_t MEDIAN_OFFSET = (MEDIAN_FILTER_SIZE - 1) / 2;

// TODO: we should throw each step into its own function.

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

  // Initialize power spectrum matrix. Subtract 1 from number windows to avoid
  // partially filled window.
  const size_t numFreqBins = getNyquistSize(WINDOW_SIZE);
  const size_t numWindows = (in.size() / HALF_WINDOW_SIZE) - 1;
  const size_t r = numFreqBins;
  const size_t c = numWindows;
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
  LOG_INFO("Applying median filtering.");
  Matrix yH{r, c};
  Matrix yP{r, c};

  // Rows: Harmonics
  for (size_t i = 0; i < r; i++) {
    std::vector<double> rowData = powerSpectrumTs.getRow(i);

    auto first = rowData.begin();
    auto last = rowData.begin() + MEDIAN_FILTER_SIZE;
    for (size_t j = MEDIAN_OFFSET; j < c - MEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yH(i, j) = median(vec);
      first++;
      last++;
    }
  }

  // Cols: Percussion
  for (size_t i = 0; i < c; i++) {
    std::vector<double> colData = powerSpectrumTs.getCol(i);

    auto first = colData.begin();
    auto last = colData.begin() + MEDIAN_FILTER_SIZE;
    for (size_t j = MEDIAN_OFFSET; j < c - MEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yH(i, j) = median(vec);
      first++;
      last++;
    }
  }

  // 3. Apply mask.

  // 4. Get final components.
}
