/**
 *******************************************************************************
 * @file    spectrum.h
 * @brief   Spectrum header.
 *******************************************************************************
 */

#pragma once

#include <complex>
#include <cstdint>

#include "matrix.hpp"

/**
 * @brief Create a complex spectrum of input signal.
 *
 * @param[in] in Input signal.
 * @param[out] complexSpectrum Complex spectrum of the input.
 */
void createComplexSpectrum(std::vector<double>& in,
                           Matrix<std::complex<double>>& complexSpectrum);

/**
 * @brief Create a complex spectrum of input singal from specific rows.
 *
 * @param in Input signal.
 * @param complexSpectrum Complex spectrum of the input.
 * @param rowStart First row to convert to complex spectrum.
 * @param rowEnd Last row (non-inclusive) to convert to complex spectrum.
 */
void createComplexSpectrumCols(std::vector<double>& in,
                               Matrix<std::complex<double>>& complexSpectrum,
                               size_t rowStart, size_t rowEnd);

/**
 * @brief Create a power spectrum from the complex spectrum.
 *
 * @param[in] complexSpectrum Complex spectrum.
 * @param[out] powerSpectrum Power spectrum
 */
void createPowerSpectrum(const Matrix<std::complex<double>>& complexSpectrum,
                         Matrix<double>& powerSpectrum);