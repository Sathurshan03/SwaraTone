/**
 *******************************************************************************
 * @file    fft.cpp
 * @brief   Fast Fourier Transform (FFT) source.
 *******************************************************************************
 */

#include "fft.h"

#include <math.h>

#include "bit_property.h"
#include "bit_reversal.h"
#include "constants.h"

void swapInput(double* x, uint32_t N, int numStages) {
  for (uint32_t i = 0; i < N; i++) {
    uint32_t reversedBits = bitReversal32(i) >> (32 - numStages);

    if (reversedBits > i) {
      std::swap(x[i], x[reversedBits]);
    }
  }
}

bool inline checkPower2(uint32_t num) { return check1BitSet(num); }

void runFFT(double* x, uint32_t N, frequencyDomain& X) {
  if (!checkPower2(N)) {
    // TODO: add some logging or some error enum to return instead?
    return;
  }

  int numStages = static_cast<int>(log2(N));
  swapInput(x, N, numStages);

  std::vector<std::complex<double>> tempFreq(N);
  for (int i = 0; i < N; i++) {
    tempFreq[i] = doubleComplex(x[i], 0.0);
  }

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
  if (N / 2 != X.numBins) {
    resizeFrequncyDomain(N / 2, X);
  }

  std::copy(tempFreq.begin(), tempFreq.begin() + X.numBins,
            X.frequency.begin());
}
