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
 * @param[in] magnitudeSpectrogram Full magnitude spectrum. (V)
 * @param[in] X Original complex STFT. (X)
 * @param[in] period The determined period of the beat spectrum.
 * @param[out] maskedX soft mask on X.
 */
void applySoftMask(const Matrix<double>& magnitudeSpectrogram,
                   const Matrix<std::complex<double>>& X, size_t period,
                   Matrix<std::complex<double>>& maskedX);
