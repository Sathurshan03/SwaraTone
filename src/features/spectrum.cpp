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
#include "windowingFunctions.hpp"

void createComplexSpectrum(std::vector<double>& in,
                           Matrix<std::complex<double>>& complexSpectrum,
                           uint32_t windowSize) {
  const size_t r = complexSpectrum.getNumRows();
  const size_t c = complexSpectrum.getNumCols();

  frequencyDomain X;
  initFrequncyDomain(windowSize, X);
  const uint32_t halfWindowSize = windowSize / 2;

  std::vector<double> x(windowSize);
  for (size_t i = 0; i < c; i++) {
    std::copy(in.begin() + i * halfWindowSize,
              in.begin() + i * halfWindowSize + windowSize, x.begin());

    applySqrtHanningWindow(x.data(), windowSize);
    runFFT(x.data(), windowSize, X);

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