/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   main code.
 *******************************************************************************
 */

#include "constants.h"
#include "fft.h"
#include "frequencyDomain.h"
#include "logging.h"
#include "windowing_functions.h"

int main() {
  LOG_INFO("Hello! I am Swara Tone!");
  LOG_INFO("We will need a lot of coffee for this fun project!");

  // Generate a sample input.
  const int N = 4096;
  const double freq = 55.0;
  const double Fs = N;
  double x[N];

  // Generate a cosine wave.
  for (int n = 0; n < N; n++) {
    x[n] = std::cos(2.0 * PI * freq * n / Fs);
  }
  applyHanningWindow(x, N);

  // Run FFt on the input.
  frequencyDomain X;
  initFrequncyDomain(N, X);
  runFFT(x, N, X);
}
