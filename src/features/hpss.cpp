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
#include "hpssMask.hpp"
#include "logging.h"
#include "powers.hpp"
#include "stats.h"
#include "windowing_functions.hpp"

static const size_t MEDIAN_FILTER_SIZE = 5;
static const size_t MEDIAN_OFFSET = (MEDIAN_FILTER_SIZE - 1) / 2;

void runHPSS(std::vector<double>& in, Matrix<double>& mH, Matrix<double>& mP) {
  LOG_INFO("Running HPSS.");

  // Initialize power spectrum matrix. Subtract 1 from number windows to avoid
  // partially filled window.
  const size_t numFreqBins = getNyquistSize(WINDOW_SIZE);
  const size_t numWindows = (in.size() / HALF_WINDOW_SIZE) - 1;
  const size_t r = numFreqBins;
  const size_t c = numWindows;

  Matrix<std::complex<double>> stftX{r, c};
  Matrix<double> powerSpectrumTs{r, c};

  // 1. Compute FFT on input signal to create a power spectrum.
  LOG_INFO("Computing FFT on input signal");
  createPowerSpectrumTs(in, stftX, powerSpectrumTs);

  // 2. Apply median filtering.
  LOG_INFO("Applying median filtering.");
  Matrix<double> yH{r, c};
  Matrix<double> yP{r, c};
  runMedianFiltering(powerSpectrumTs, yH, yP);

  // 3. Create mask.
  LOG_INFO("Applying filter mask.");
  std::pair<double, double> maskSize = std::make_pair(r, c);
  mH.resize(maskSize);
  mP.resize(maskSize);
  applySoftMask(yH, yP, mH, mP);

  // 4. Apply mask.

  LOG_INFO("Finished running HPSS.");
}

void createPowerSpectrumTs(std::vector<double>& in,
                           Matrix<std::complex<double>>& stftX,
                           Matrix<double>& powerSpectrumTs) {
  const size_t r = powerSpectrumTs.getNumRows();
  const size_t c = powerSpectrumTs.getNumCols();

  frequencyDomain X;
  initFrequncyDomain(WINDOW_SIZE, X);

  for (size_t i = 0; i < c; i++) {
    double* x = in.data() + i * HALF_WINDOW_SIZE;

    applyHanningWindow(x, WINDOW_SIZE);
    runFFT(x, WINDOW_SIZE, X);

    // Create power spectrum.
    for (size_t j = 0; j < r; j++) {
      stftX(j, i) = X.frequency[j];
      powerSpectrumTs(j, i) = std::norm(X.frequency[j]);
    }
  }
}

void runMedianFiltering(Matrix<double>& powerSpectrumTs, Matrix<double>& yH,
                        Matrix<double>& yP) {
  const size_t r = powerSpectrumTs.getNumRows();
  const size_t c = powerSpectrumTs.getNumCols();

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
}
