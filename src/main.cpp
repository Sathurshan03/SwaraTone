/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   main code.
 *******************************************************************************
 */
#include <iostream>

#include "constants.h"
#include "fft.h"
#include "frequencyDomain.h"
#include "windowing_functions.h"

int main() {
  std::cout << "Hello! I am Swara Tone!" << std::endl;
  std::cout << "We will need a lot of coffee for this fun project!"
            << std::endl;

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
