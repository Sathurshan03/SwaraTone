/**
 *******************************************************************************
 * @file    fft.cpp
 * @brief   Fast Fourier Transform (FFT) source.
 *******************************************************************************
 */

#include "fft.h"

#include "constants.h"
#include "fft_helper.hpp"
#include "logging.h"
#include "powers.hpp"

void runFFT(double* x, uint32_t N, frequencyDomain& X) {
  if (!checkPower2(N)) {
    LOG_ERROR("N is not a power of 2. N = " << N);
    return;
  }

  // Run radix sort.
  X.frequency.resize(N);
  for (int i = 0; i < N; i++) {
    X.frequency[i] = doubleComplex(x[i], 0.0);
  }

  size_t numStages = static_cast<size_t>(log2(N));
  swapInput(X.frequency.data(), N, numStages);

  // Run butterfly staging to compute fourier transform.
  std::vector<doubleComplex> weight(N / 2);
  for (size_t s = 1; s <= numStages; s++) {
    size_t stageN = 1 << s;
    size_t half = stageN >> 1;
    double angle = -2.0 * PI / static_cast<double>(stageN);

    for (size_t l = 0; l < half; l++) {
      weight[l] = std::polar(1.0, angle * l);
    }

    for (size_t k = 0; k < N; k += stageN) {
      doubleComplex* base = X.frequency.data() + k;
      for (size_t j = 0; j < half; j++) {
        doubleComplex u = base[j];
        doubleComplex t = weight[j] * base[j + half];
        base[j] = u + t;
        base[j + half] = u - t;
      }
    }
  }

  // From Nyquist thereom, we can discard the last half elements as they repeat.
  resizeFrequncyDomain(getNyquistSize(N), X);
}
