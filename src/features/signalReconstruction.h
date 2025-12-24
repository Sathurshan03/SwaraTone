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
 * @param[in] windowSize Size of window.
 * @param[out] output reconstructed signal.
 */
void reconstructSignal(Matrix<std::complex<double>> complexSpectrum,
                       uint32_t windowSize, std::vector<double>& output);
