/**
 *******************************************************************************
 * @file    ifft.h
 * @brief   Inverse Fast Fourier Transform (IFFT) header.
 *******************************************************************************
 */

#pragma once

#include <cstdint>

#include "frequencyDomain.h"

typedef std::complex<double> doubleComplex;

/**
 * @brief Run IFFT on input signal usiong radix-2 algo.
 *
 * @param X Frequency domain.
 * @param N Size of frequency domain.
 * @param[in,out] x Output time domain signal already intiialized.
 * @param nyquistApplied True if Nyquist Theorem was applied on @ref X. False
 * otherwise.
 */
void runIFFT(std::vector<doubleComplex>& X, uint32_t N,
             std::vector<doubleComplex>& x, bool nyquistApplied = true);

/**
 * @brief Reverses Nyquist theorem by putting back frequencies that were removed
 * according to this theorem.
 *
 * @param X Frequency domain where Nyquist theorem was applied.
 * @param[in,out] fullFrequency Frequency domain where Nyquist theorem was
 * reversed.
 */
void reverseNyquistTheorem(std::vector<doubleComplex>& X,
                           std::vector<doubleComplex>& fullFrequency);
