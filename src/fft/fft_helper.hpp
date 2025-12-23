/**
 *******************************************************************************
 * @file    fft_helper.h
 * @brief   Fast Fourier Transform (FFT) helper header file.
 *******************************************************************************
 */

#pragma once

#include <cstdint>

#include "bit_reversal.h"

/**
 * @brief Swaps the ordering of input for radix-2 algo.
 *
 * @param[in,out] x Input signal.
 * @param[in] N Size of input signal.
 * @param[in] numStages The number of stages in radix-2 algo. This is equivalent
 * to log2(N).
 */
template <typename T>
void swapInput(T* x, uint32_t N, int numStages) {
  for (uint32_t i = 0; i < N; i++) {
    uint32_t reversedBits = bitReversal32(i) >> (32 - numStages);

    if (reversedBits > i) {
      std::swap(x[i], x[reversedBits]);
    }
  }
}

/**
 * @brief Get the size of array when using Nyquist theory
 *
 * @param[in] N Size of original array.
 * @return uint32_t New array size.
 */
inline uint32_t getNyquistSize(uint32_t N) { return (N / 2) + 1; }
