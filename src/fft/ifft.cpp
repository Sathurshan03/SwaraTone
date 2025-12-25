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

void runIFFT(const doubleComplex* X, uint32_t N, std::vector<doubleComplex>& x,
             bool nyquistApplied) {
  // Reverse Nyquist theroem if applicable.
  if (nyquistApplied) {
    reverseNyquistTheorem(X, N, x);
    N = static_cast<uint32_t>(x.size());
  } else {
    x.assign(X, X + N);
  }

  if (!checkPower2(N)) {
    LOG_ERROR("N is not a power of 2. N = " << N);
    return;
  }

  // Run radix sort.
  size_t numStages = static_cast<size_t>(log2(N));
  swapInput(x.data(), N, numStages);

  // Run butterfly staging to compute fourier transform.
  std::vector<doubleComplex> weight(N / 2);
  for (size_t s = 1; s <= numStages; s++) {
    size_t stageN = 1 << s;
    size_t half = stageN >> 1;
    double angle = 2.0 * PI / static_cast<double>(stageN);

    for (size_t l = 0; l < half; l++) {
      weight[l] = std::polar(1.0, angle * l);
    }

    for (size_t k = 0; k < N; k += stageN) {
      doubleComplex* base = x.data() + k;
      for (size_t j = 0; j < half; j++) {
        doubleComplex u = base[j];
        doubleComplex t = weight[j] * base[j + half];
        base[j] = u + t;
        base[j + half] = u - t;
      }
    }
  }

  // Normalize the signal.
  double invN = 1.0 / static_cast<double>(N);
  for (int i = 0; i < N; i++) {
    x[i] *= invN;
  }
}

void reverseNyquistTheorem(const doubleComplex* X, uint32_t Npos,
                           std::vector<doubleComplex>& fullFrequency) {
  const size_t N = 2 * (Npos - 1);
  fullFrequency.resize(N);

  std::copy(X, X + Npos, fullFrequency.begin());

  // Mirror negative frequencies (exclude DC [0] and Nyquist [N/2])
  for (size_t i = 1; i < Npos - 1; i++) {
    fullFrequency[N - i] = std::conj(X[i]);
  }
}
