/**
 *******************************************************************************
 * @file    ifft.h
 * @brief   Inverse Fast Fourier Transform (IFFT) header.
 *******************************************************************************
 */

#include "ifft.h"

#include "constants.h"
#include "fft_helper.hpp"
#include "logging.h"
#include "powers.hpp"

void runIFFT(std::vector<doubleComplex>& X, uint32_t N,
             std::vector<doubleComplex>& x, bool nyquistApplied) {
  // Reverse Nyquist theroem if applicable.
  std::vector<doubleComplex> fullX{};
  if (nyquistApplied) {
    reverseNyquistTheorem(X, fullX);
    N = static_cast<uint32_t>(fullX.size());
  } else {
    fullX = X;
  }

  if (!checkPower2(N)) {
    LOG_ERROR("N is not a power of 2. N = " << N);
    return;
  }

  // Run radix sort.
  x.assign(std::begin(fullX), std::end(fullX));
  int numStages = static_cast<int>(log2(N));
  swapInput(x.data(), N, numStages);

  // Run butterfly staging to compute fourier transform.
  for (int s = 1; s <= numStages; s++) {
    int stageN = 1 << s;
    int half = stageN >> 1;
    double angle = 2.0 * PI / static_cast<double>(stageN);

    doubleComplex w_m = std::polar(1.0, angle);

    for (int k = 0; k < N; k += stageN) {
      doubleComplex w = 1.0;
      for (int j = 0; j < half; j++) {
        int idx = k + j;
        int idxHalf = idx + half;
        doubleComplex u = x[idx];
        doubleComplex t = w * x[idxHalf];
        x[idx] = u + t;
        x[idxHalf] = u - t;
        w *= w_m;
      }
    }
  }

  // Normalize the signal.
  for (int i = 0; i < N; i++) {
    x[i] /= static_cast<double>(N);
  }
}

void reverseNyquistTheorem(std::vector<doubleComplex>& X,
                           std::vector<doubleComplex>& fullFrequency) {
  const size_t Npos = X.size();
  const size_t N = 2 * (Npos - 1);
  fullFrequency.resize(N);

  std::copy(X.begin(), X.end(), fullFrequency.begin());

  // Mirror negative frequencies (exclude DC [0] and Nyquist [N/2])
  for (size_t i = 1; i < Npos - 1; i++) {
    fullFrequency[N - i] = std::conj(X[i]);
  }
}
