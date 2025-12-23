/**
 *******************************************************************************
 * @file    signalReconstruction.cpp
 * @brief   Signal reconstruction source code.
 *******************************************************************************
 */

#include "signalReconstruction.h"

#include "ifft.h"
#include "windowingFunctions.hpp"

void reconstructSignal(Matrix<std::complex<double>> complexSpectrum,
                       uint32_t windowSize, std::vector<double> output) {
  const size_t r = complexSpectrum.getNumRows();
  const size_t c = complexSpectrum.getNumCols();

  const size_t halfWindowSize = windowSize / 2;
  const size_t signalSize = (c - 1) * halfWindowSize + windowSize;

  std::vector<std::complex<double>> X(r);
  std::vector<std::complex<double>> x;

  std::vector<double> numerator(signalSize, 0.0);
  std::vector<double> denominator(signalSize, 0.0);
  output.resize(signalSize);

  // Temporary store window weights. Allows for faster access when
  // reconstructing signal.
  std::vector<double> weights(windowSize);
  for (size_t i = 0; i < windowSize; i++) {
    weights[i] = getHanningWindowWeight(i, windowSize);
  }

  // Reconstruct signal while considering the window weights initially applied
  // when computing the fourier transform.
  for (size_t i = 0; i < c; i++) {
    X = complexSpectrum.getCol(i);
    runIFFT(X, windowSize, x);

    for (size_t j = 0; j < signalSize; j++) {
      size_t pos = i * halfWindowSize + j;
      numerator[pos] += x[j].real() * weights[j];
      denominator[pos] += weights[j] * weights[j];
    }
  }

  for (size_t i = 0; i < signalSize; i++) {
    if (denominator[i] != 0.0) {
      output[i] = numerator[i] / denominator[i];
    } else {
      output[i] = 0.0;
    }
  }
}
