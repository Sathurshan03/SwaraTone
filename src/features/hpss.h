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
 * @param[out] hComplexSpectrum harmonics components complex spectrum.
 * @param[out] pComplexSpectrum percussive components complex spectrum.
 * @param[in] softMask True to use soft mask. False to use binary mask.
 */
void runHPSS(ComplexMatrix& complexSpectrum, Matrix<double>& powerSpectrum,
             ComplexMatrix& hComplexSpectrum, ComplexMatrix& pComplexSpectrum,
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

/**
 * @brief Run median filtering on for harmonics.
 *
 * @param powerSpectrum Power spectrum.
 * @param yH Median filter for harmonics.
 * @param colStart The first column of the power spectrum to analyze.
 * @param colEnd The last column (non-inclusive) of the power spectrum to
 * analyze.
 */
void runHMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yH,
                         size_t colStart, size_t colEnd);

/**
 * @brief Run median filtering on for percussions.
 *
 * @param powerSpectrum Power spectrum.
 * @param yH Median filter for percussives.
 * @param rowStart The first row of the power spectrum to analyze.
 * @param rowEnd The last row (non-inclusive) of the power spectrum to analyze.
 */
void runPMedianFiltering(Matrix<double>& powerSpectrum, Matrix<double>& yP,
                         size_t rowStart, size_t rowEnd);
