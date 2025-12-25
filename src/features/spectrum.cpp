/**
 *******************************************************************************
 * @file    spectrum.cpp
 * @brief   Spectrum source.
 *******************************************************************************
 */

#include "spectrum.h"

#include <algorithm>
#include <thread>
#include <vector>

#include "constants.h"
#include "fft.h"
#include "frequencyDomain.h"
#include "logging.h"
#include "windowingFunctions.hpp"

void createComplexSpectrum(std::vector<double>& in,
                           Matrix<std::complex<double>>& complexSpectrum) {
  const size_t r = complexSpectrum.getNumRows();

  // Use threads to speed up computation.
  const size_t NUM_THREADS = std::min<size_t>(BASE_NUM_THREADS, r);
  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);

  size_t base = r / NUM_THREADS;
  size_t rem = r % NUM_THREADS;

  size_t start = 0;
  size_t end = 0;

  for (size_t i = 0; i < NUM_THREADS; i++) {
    start = i * base + std::min(i, rem);
    end = start + base + (i < rem ? 1 : 0);

    threads.emplace_back(std::thread(createComplexSpectrumCols, std::ref(in),
                                     std::ref(complexSpectrum), start, end));
  }

  for (std::thread& thread : threads) {
    thread.join();
  }
}

void createComplexSpectrumCols(std::vector<double>& in,
                               Matrix<std::complex<double>>& complexSpectrum,
                               size_t rowStart, size_t rowEnd) {
  frequencyDomain X;
  initFrequncyDomain(WINDOW_SIZE, X);
  std::vector<double> x(WINDOW_SIZE);

  for (size_t i = rowStart; i < rowEnd; i++) {
    std::copy(in.begin() + i * HOP_SIZE,
              in.begin() + i * HOP_SIZE + WINDOW_SIZE, x.begin());

    applySqrtHanningWindow(x.data(), WINDOW_SIZE);
    runFFT(x.data(), WINDOW_SIZE, X);

    // Store fourier transform values into the complex spectrum.
    complexSpectrum.setRow(i, X.frequency);
  }
}

void createPowerSpectrum(const Matrix<std::complex<double>>& complexSpectrum,
                         Matrix<double>& powerSpectrum) {
  const size_t numOps = powerSpectrum.getNumRows() * powerSpectrum.getNumCols();

  for (size_t i = 0; i < numOps; i++) {
    powerSpectrum(i) = std::norm(complexSpectrum(i));
  }
}