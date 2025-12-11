/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   main code.
 *******************************************************************************
 */

#include "constants.h"
#include "fft.h"
#include "frequencyDomain.h"
#include "ifft.h"
#include "logging.h"
#include "wav_encoding.h"
#include "windowing_functions.h"

int main() {
  LOG_INFO("Hello! I am Swara Tone!");
  LOG_INFO("We will need a lot of coffee for this fun project!");

  // Generate a sample input.
  const int N = 4096;
  const double freq = 55.0;
  const double Fs = N;
  double x[4096];

  // Generate a cosine wave.
  for (int n = 0; n < N; n++) {
    x[n] = std::cos(2.0 * PI * freq * n / Fs);
  }
  // applyHanningWindow(x, N);

  // Write input signal to a wav file.
  WAVFileEncoder wavEncoder{};
  std::vector<double> inputSignal(x, x + N);
  wavEncoder.writeToFile("originalSignal", inputSignal, BITS_PER_SAMPLE,
                         Channel::Mono, SAMPLE_RATE);

  // Run FFT on the input.
  frequencyDomain X;
  initFrequncyDomain(N, X);
  runFFT(x, N, X);

  // Run IFFT of the generate frequency domain.
  std::vector<std::complex<double>> outputSignal;
  runIFFT(X.frequency, N, outputSignal);

  // Convert the output time domain signal into real number.
  std::vector<double> outputRealSignal(N);
  for (int i = 0; i < N; i++) {
    outputRealSignal[i] = outputSignal[i].real();
  }

  // Write output signal to a wav file.
  wavEncoder.writeToFile("modifiedSignal", outputRealSignal, BITS_PER_SAMPLE,
                         Channel::Mono, SAMPLE_RATE);
}
