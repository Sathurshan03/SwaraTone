/**
 *******************************************************************************
 * @file    spectrum.cpp
 * @brief   Spectrum source.
 *******************************************************************************
 */

#include "spectrum.h"

#include "constants.h"
#include "fft.h"
#include "frequencyDomain.h"
#include "logging.h"
#include "windowingFunctions.hpp"

void createComplexSpectrum(std::vector<double>& in,
                           Matrix<std::complex<double>>& complexSpectrum) {
  const size_t r = complexSpectrum.getNumRows();
  const size_t c = complexSpectrum.getNumCols();

  frequencyDomain X;
  initFrequncyDomain(WINDOW_SIZE, X);

  std::vector<double> x(WINDOW_SIZE);
  for (size_t i = 0; i < c; i++) {
    std::copy(in.begin() + i * HOP_SIZE,
              in.begin() + i * HOP_SIZE + WINDOW_SIZE, x.begin());

    applySqrtHanningWindow(x.data(), WINDOW_SIZE);
    runFFT(x.data(), WINDOW_SIZE, X);

    // Store fourier transform values into the complex spectrum.
    for (size_t j = 0; j < r; j++) {
      complexSpectrum(j, i) = X.frequency[j];
    }
  }
}

void createPowerSpectrum(const Matrix<std::complex<double>>& complexSpectrum,
                         Matrix<double>& powerSpectrum) {
  const size_t r = complexSpectrum.getNumRows();
  const size_t c = complexSpectrum.getNumCols();

  for (size_t i = 0; i < c; i++) {
    for (size_t j = 0; j < r; j++) {
      powerSpectrum(j, i) = std::norm(complexSpectrum(j, i));
    }
  }
}