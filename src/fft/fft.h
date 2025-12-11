/**
 *******************************************************************************
 * @file    fft.h
 * @brief   Fast Fourier Transform (FFT) header.
 *******************************************************************************
 */

#pragma once

#include <cstdint>

#include "frequencyDomain.h"

typedef std::complex<double> doubleComplex;

/**
 * @brief Run FFT on input signal usiong radix-2 algo.
 *
 * @param x Input signal.
 * @param N Size of input signal.
 * @param[in,out] X Frequency domain structure.
 */
void runFFT(double* x, uint32_t N, frequencyDomain& X);
