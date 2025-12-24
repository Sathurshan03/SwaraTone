/**
 *******************************************************************************
 * @file    signalReconstruction.h
 * @brief   Signal reconstruction header.
 *******************************************************************************
 */

#pragma once
#include <complex>
#include <cstdint>

#include "matrix.hpp"

/**
 * @brief Reconstruction signal from complex spectrum
 *
 * @param[in] complexSpectrum Complex spectrum.
 * @param[out] output reconstructed signal.
 */
void reconstructSignal(Matrix<std::complex<double>>& complexSpectrum,
                       std::vector<double>& output);
