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
#include "powers.h"

void runFFT(double* x, uint32_t N, frequencyDomain& X) {
  if (!checkPower2(N)) {
    LOG_ERROR("N is not a power of 2. N = " << N);
    return;
  }

  // Run radix sort.
  std::vector<doubleComplex> tempFreq(N);
  for (int i = 0; i < N; i++) {
    tempFreq[i] = doubleComplex(x[i], 0.0);
  }

  int numStages = static_cast<int>(log2(N));
  swapInput(tempFreq.data(), N, numStages);

  // Run butterfly staging to compute fourier transform.
  for (int s = 1; s <= numStages; s++) {
    int stageN = 1 << s;
    int half = stageN >> 1;
    double angle = -2.0 * PI / static_cast<double>(stageN);

    doubleComplex w_m = std::polar(1.0, angle);

    for (int k = 0; k < N; k += stageN) {
      doubleComplex w = 1.0;
      for (int j = 0; j < half; j++) {
        int idx = k + j;
        int idxHalf = idx + half;
        doubleComplex u = tempFreq[idx];
        doubleComplex t = w * tempFreq[idxHalf];
        tempFreq[idx] = u + t;
        tempFreq[idxHalf] = u - t;
        w *= w_m;
      }
    }
  }

  // From Nyquist thereom, we can discard the last half elements as they repeat.
  if (getNyquistSize(N) != X.numBins) {
    resizeFrequncyDomain(getNyquistSize(N), X);
  }

  std::copy(tempFreq.begin(), tempFreq.begin() + X.numBins,
            X.frequency.begin());
}
