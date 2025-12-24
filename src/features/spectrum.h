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
 * @brief Create a power spectrum from the complex spectrum.
 *
 * @param[in] complexSpectrum Complex spectrum.
 * @param[out] powerSpectrum Power spectrum
 */
void createPowerSpectrum(const Matrix<std::complex<double>>& complexSpectrum,
                         Matrix<double>& powerSpectrum);