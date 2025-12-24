/**
 *******************************************************************************
 * @file    signalReconstruction.cpp
 * @brief   Signal reconstruction source code.
 *******************************************************************************
 */

#include "signalReconstruction.h"

#include "constants.h"
#include "ifft.h"
#include "windowingFunctions.hpp"

void reconstructSignal(Matrix<std::complex<double>>& complexSpectrum,
                       std::vector<double>& output) {
  const size_t r = complexSpectrum.getNumRows();
  const size_t c = complexSpectrum.getNumCols();

  const size_t signalSize = (c - 1) * HOP_SIZE + WINDOW_SIZE;
  const size_t paddedSignalSize = signalSize + PADDING_SIZE * 2;

  std::vector<std::complex<double>> X(r);
  std::vector<std::complex<double>> x;

  std::vector<double> constructedSignal(paddedSignalSize, 0.0);
  output.resize(signalSize);

  double denominator = HALF_WINDOW_SIZE / HOP_SIZE;

  // Temporary store window weights. Allows for faster access when
  // reconstructing signal.
  std::vector<double> sqrtWeights(WINDOW_SIZE);
  std::vector<double> weights(WINDOW_SIZE);
  for (size_t i = 0; i < WINDOW_SIZE; i++) {
    weights[i] = getHanningWindowWeight(i, WINDOW_SIZE);
    sqrtWeights[i] = getSqrtHanningWindowWeight(i, WINDOW_SIZE);
  }

  // Reconstruct signal while considering the window weights initially applied
  // when computing the fourier transform.
  for (size_t i = 0; i < c; i++) {
    X = complexSpectrum.getCol(i);
    runIFFT(X, WINDOW_SIZE, x);

    for (size_t j = 0; j < WINDOW_SIZE; j++) {
      size_t pos = i * HOP_SIZE + j;
      constructedSignal[pos] += x[j].real() * sqrtWeights[j] / denominator;
    }
  }

  // Remove intially added zero padding.
  std::copy(constructedSignal.begin() + PADDING_SIZE,
            constructedSignal.begin() + PADDING_SIZE + signalSize,
            output.begin());
}
