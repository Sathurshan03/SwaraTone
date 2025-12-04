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

void swapInput(double* x, uint16_t N, int numStages) {
  for (uint16_t i = 0; i < N; i++) {
    uint16_t reversedBits = bitReversal16(i) >> (16 - numStages);

    if (reversedBits > i) {
      std::swap(x[i], x[reversedBits]);
    }
  }
}

bool inline checkPower2(uint16_t num) { return check1BitSet(num); }

void runFFT16(double* x, uint16_t N, frequencyDomain& X) {
  if (!checkPower2(N)) {
    // TODO: add some logging or some error enum to return instead?
    return;
  }

  int numStages = static_cast<int>(log2(N));
  swapInput(x, N, numStages);

  X.frequency.resize(N);
  for (int i = 0; i < N; i++) {
    X.frequency[i] = doubleComplex(x[i], 0.0);
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
        doubleComplex u = X.frequency[idx];
        doubleComplex t = w * X.frequency[idxHalf];
        X.frequency[idx] = u + t;
        X.frequency[idxHalf] = u - t;
        w *= w_m;
      }
    }
  }

  // From Nyquist thereom, we can discard the last half elements as they repeat.
  X.frequency.resize(X.numBins);
}
