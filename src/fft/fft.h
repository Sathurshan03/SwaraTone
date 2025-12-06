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
 * @brief Swaps the ordering of input for FFT radix-2 algo.
 *
 * @param x Input signal.
 * @param N Size of input signal.
 * @param numStages The number of stages in radix-2 algo. This is equivalent to
 * log2(N).
 */
void swapInput(double* x, uint32_t N, int numStages);

/**
 * @brief Check whether input is a power of 2. Input must be unsinged int.
 *
 * @param num Input
 * @return true Input is a power of 2. False otherwise.
 */
bool inline checkPower2(uint32_t num);

/**
 * @brief Run FFT on input signal usiong radix-2 algo.
 *
 * @param x Input signal.
 * @param N Size of input signal.
 * @param X Frequency domain structure initialized.
 */
void runFFT(double* x, uint32_t N, frequencyDomain& X);
