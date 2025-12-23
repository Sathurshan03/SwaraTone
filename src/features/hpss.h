/**
 *******************************************************************************
 * @file    hpss.h
 * @brief   Harmonic Percussice Source Separation (HPSS) header.
 *******************************************************************************
 */

#pragma once

#include <complex>
#include <vector>

#include "matrix.hpp"

typedef Matrix<std::complex<double>> ComplexMatrix;

/**
 * @brief Run HPSS algo.
 *
 * @param[in] complexSpectrum Complex Spectrum.
 * @param[in] powerSpectrum Power spectrum.
 * @param[in] softMask True to use soft mask. False to use binary mask.
 * @return std::pair<ComplexMatrix, ComplexMatrix> First item is the harmonic
 * components from the complex spectrum and second is the percussive component.
 */
std::pair<ComplexMatrix, ComplexMatrix> runHPSS(ComplexMatrix& complexSpectrum,
                                                Matrix<double>& powerSpectrum,
                                                bool softMask = true);

/**
 * @brief Run median filtering on power spectrum.
 *
 * @param[in] powerSpectrum Power spectrum.
 * @param[out] yH Median filter for harmonics.
 * @param[out] yP Median filter for percussives.
 */
void runMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yH,
                        Matrix<double>& yP);
