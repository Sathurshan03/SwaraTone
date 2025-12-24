/**
 *******************************************************************************
 * @file    hpss.cpp
 * @brief   Harmonic Percussice Source Separation (HPSS) source.
 *******************************************************************************
 */

#include "hpss.h"

#include "constants.h"
#include "hpssMask.hpp"
#include "logging.h"
#include "stats.h"

static const size_t HMEDIAN_FILTER_SIZE = 9;
static const size_t PMEDIAN_FILTER_SIZE = 5;
static const size_t HMEDIAN_OFFSET = (HMEDIAN_FILTER_SIZE - 1) / 2;
static const size_t PMEDIAN_OFFSET = (PMEDIAN_FILTER_SIZE - 1) / 2;

void runHPSS(ComplexMatrix& complexSpectrum, Matrix<double>& powerSpectrum,
             ComplexMatrix& hComplexSpectrum, ComplexMatrix& pComplexSpectrum,
             bool softMask) {
  LOG_INFO("Running HPSS.");

  // 1. Apply median filtering.
  LOG_INFO("Applying median filtering.");
  const size_t r = powerSpectrum.getNumRows();
  const size_t c = powerSpectrum.getNumCols();

  Matrix<double> yH{r, c};
  Matrix<double> yP{r, c};
  runMedianFiltering(powerSpectrum, yH, yP);

  // 2. Create mask.
  LOG_INFO("Applying filter mask.");
  Matrix<double> mH{r, c};
  Matrix<double> mP{r, c};

  if (softMask) {
    applySoftMask(yH, yP, mH, mP);
  } else {
    applyBinaryMask(yH, yP, mH, mP);
  }

  // 3. Apply mask to complex spectrum.
  hComplexSpectrum = complexSpectrum * mH;
  pComplexSpectrum = complexSpectrum * mP;

  LOG_INFO("Finished running HPSS.");
}

void runMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yH,
                        Matrix<double>& yP) {
  const size_t r = powerSpectrum.getNumRows();
  const size_t c = powerSpectrum.getNumCols();

  // Rows: Harmonics
  for (size_t i = 0; i < r; i++) {
    std::vector<double> rowData = powerSpectrum.getRow(i);
    auto first = rowData.begin();
    auto last = rowData.begin() + HMEDIAN_FILTER_SIZE;
    for (size_t j = HMEDIAN_OFFSET; j < c - HMEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yH(i, j) = median(vec);
      first++;
      last++;
    }
  }

  // Cols: Percussion
  for (size_t i = 0; i < c; i++) {
    std::vector<double> colData = powerSpectrum.getCol(i);
    auto first = colData.begin();
    auto last = colData.begin() + PMEDIAN_FILTER_SIZE;
    for (size_t j = PMEDIAN_OFFSET; j < r - PMEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yP(j, i) = median(vec);
      first++;
      last++;
    }
  }
}
