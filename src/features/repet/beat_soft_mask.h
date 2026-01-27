/**
 *******************************************************************************
 * @file    beat_soft_mask.h
 * @brief   Beat soft mask header.
 *******************************************************************************
 */

#pragma once

#include <complex>

#include "matrix.hpp"

/**
 * @brief Applies soft mask onto STFT X
 *
 * @param repeatingSegment Repeating pattern per period (S).
 * @param magnitudeSpectrogram Full magnitude spectrum. (V)
 * @param X Original complex STFT. (X)
 * @param period The determined period of the beat spectrum.
 * @return Matrix<std::complex<double>> soft mask on X.
 */
Matrix<std::complex<double>> applySoftMask(
    const Matrix<double>& repeatingSegment,
    const Matrix<double>& magnitudeSpectrogram,
    const Matrix<std::complex<double>>& X, size_t period);
