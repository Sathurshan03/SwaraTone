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
/**
 * @brief Creates threads to do signal reconstruction.
 *
 * @param complexSpectrum Complex spectrum.
 * @param sqrtWeights Weights pre computed from square Hanning window.
 * @param constructedSignal Constructed signal where output signal will be
 * stored.
 */
void runSignalReconctructionThread(
    Matrix<std::complex<double>>& complexSpectrum,
    std::vector<double>& sqrtWeights, std::vector<double>& constructedSignal);

/**
 * @brief Convert specific rows from power spectrum to output signal.
 *
 * @param complexSpectrum Complex spectrum.
 * @param sqrtWeights Weights pre computed from square Hanning window.
 * @param constructedSignal Constructed signal where output signal will be
 * stored.
 * @param rowStart Starting row of complex spectrum to convert to output signal.
 * @param rowEnd Last row (non-inclusive) of complex spectrum to convert to
 * output signal.
 */
void complexSpectrumRowToSignal(Matrix<std::complex<double>>& complexSpectrum,
                                std::vector<double>& sqrtWeights,
                                std::vector<double>& constructedSignal,
                                size_t rowStart, size_t rowEnd);
