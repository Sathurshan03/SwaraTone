/**
 *******************************************************************************
 * @file    signalReconstruction.cpp
 * @brief   Signal reconstruction source code.
 *******************************************************************************
 */

#include "signalReconstruction.h"

#include <thread>

#include "constants.h"
#include "ifft.h"
#include "windowingFunctions.hpp"

void reconstructSignal(Matrix<std::complex<double>>& complexSpectrum,
                       std::vector<double>& output) {
  const size_t r = complexSpectrum.getNumRows();

  const size_t signalSize = (r - 1) * HOP_SIZE + WINDOW_SIZE;
  const size_t paddedSignalSize = signalSize + PADDING_SIZE * 2;

  std::vector<double> constructedSignal(paddedSignalSize, 0.0);
  output.resize(signalSize);

  // Temporary store window weights. Allows for faster access when
  // reconstructing signal.
  std::vector<double> sqrtWeights(WINDOW_SIZE);
  for (size_t i = 0; i < WINDOW_SIZE; i++) {
    sqrtWeights[i] = getSqrtHanningWindowWeight(i, WINDOW_SIZE);
  }

  // Use threads to speed up computation.
  runSignalReconctructionThread(complexSpectrum, sqrtWeights,
                                constructedSignal);

  // Remove intially added zero padding.
  std::copy(constructedSignal.begin() + PADDING_SIZE,
            constructedSignal.begin() + PADDING_SIZE + signalSize,
            output.begin());
}

void runSignalReconctructionThread(
    Matrix<std::complex<double>>& complexSpectrum,
    std::vector<double>& sqrtWeights, std::vector<double>& constructedSignal) {
  const size_t r = complexSpectrum.getNumRows();
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

    threads.emplace_back(std::thread(
        complexSpectrumRowToSignal, std::ref(complexSpectrum),
        std::ref(sqrtWeights), std::ref(constructedSignal), start, end));
  }

  for (std::thread& thread : threads) {
    thread.join();
  }
}

void complexSpectrumRowToSignal(Matrix<std::complex<double>>& complexSpectrum,
                                std::vector<double>& sqrtWeights,
                                std::vector<double>& constructedSignal,
                                size_t rowStart, size_t rowEnd) {
  // Reconstruct signal while considering the window weights initially applied
  // when computing the fourier transform.
  const size_t c = complexSpectrum.getNumCols();
  double denominator = HALF_WINDOW_SIZE / HOP_SIZE;

  std::vector<std::complex<double>> x;

  for (size_t i = rowStart; i < rowEnd; i++) {
    runIFFT(complexSpectrum.getRowPtr(i), c, x);
    for (size_t j = 0; j < WINDOW_SIZE; j++) {
      size_t pos = i * HOP_SIZE + j;
      constructedSignal[pos] += (x[j].real() * sqrtWeights[j]) / denominator;
    }
  }
}
