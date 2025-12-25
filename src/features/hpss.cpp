/**
 *******************************************************************************
 * @file    hpss.cpp
 * @brief   Harmonic Percussice Source Separation (HPSS) source.
 *******************************************************************************
 */

#include "hpss.h"

#include <algorithm>
#include <thread>

#include "constants.h"
#include "hpssMask.hpp"
#include "logging.h"
#include "stats.h"

static const size_t HMEDIAN_FILTER_SIZE = 11;
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
  LOG_INFO("Applying mask to complex spectrum.");
  hComplexSpectrum = complexSpectrum * mH;
  pComplexSpectrum = complexSpectrum * mP;

  LOG_INFO("Finished running HPSS.");
}

void runMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yH,
                        Matrix<double>& yP) {
  // Create threads to run median filtering.
  const size_t c = powerSpectrum.getNumCols();
  const size_t r = powerSpectrum.getNumRows();

  const size_t NUM_H_THREADS = std::min<size_t>(4, c);  // Should be power of 2.
  const size_t NUM_P_THREADS = std::min<size_t>(BASE_NUM_THREADS, r);
  std::vector<std::thread> threads;
  threads.reserve(NUM_H_THREADS + NUM_P_THREADS);

  size_t start = 0;
  size_t end = 0;

  // Percussive median filtering threads.
  size_t base = r / NUM_P_THREADS;
  size_t rem = r % NUM_P_THREADS;
  for (size_t i = 0; i < NUM_P_THREADS; i++) {
    start = i * base + std::min(i, rem);
    end = start + base + (i < rem ? 1 : 0);

    threads.emplace_back(std::thread(runPMedianFiltering,
                                     std::ref(powerSpectrum), std::ref(yP),
                                     start, end));
  }

  // Harmonic median filtering threads.
  base = c / NUM_H_THREADS;
  rem = c % NUM_H_THREADS;
  for (size_t i = 0; i < NUM_H_THREADS; i++) {
    start = i * base + std::min(i, rem);
    end = start + base + (i < rem ? 1 : 0);

    threads.emplace_back(std::thread(runHMedianFiltering,
                                     std::ref(powerSpectrum), std::ref(yH),
                                     start, end));
  }

  // Join threads.
  for (std::thread& thread : threads) {
    thread.join();
  }
}

void runHMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yH,
                         size_t colStart, size_t colEnd) {
  const size_t r = powerSpectrum.getNumRows();
  const size_t c = powerSpectrum.getNumCols();

  // Columns: Harmonics
  for (size_t i = colStart; i < colEnd; i++) {
    std::vector<double> colData = powerSpectrum.getCol(i);
    auto first = colData.begin();
    auto last = colData.begin() + HMEDIAN_FILTER_SIZE;
    for (size_t j = HMEDIAN_OFFSET; j < r - HMEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yH(j, i) = median(vec);
      ++first;
      ++last;
    }
  }
}

void runPMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yP,
                         size_t rowStart, size_t rowEnd) {
  const size_t r = powerSpectrum.getNumRows();
  const size_t c = powerSpectrum.getNumCols();

  // Rows: Percussion
  for (size_t i = rowStart; i < rowEnd; i++) {
    std::vector<double> rowData = powerSpectrum.getRow(i);
    auto first = rowData.begin();
    auto last = rowData.begin() + PMEDIAN_FILTER_SIZE;
    for (size_t j = PMEDIAN_OFFSET; j < c - PMEDIAN_OFFSET; j++) {
      std::vector<double> vec(first, last);
      yP(i, j) = median(vec);
      ++first;
      ++last;
    }
  }
}
