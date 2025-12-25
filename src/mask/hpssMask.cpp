/**
 *******************************************************************************
 * @file    hpssMask.cpp
 * @brief   HPSS (Harmonic Percussive Source Seperation) mask source.
 *******************************************************************************
 */

#include "hpssMask.hpp"

#include <algorithm>
#include <thread>

void applyBinaryMask(const Matrix<double>& yH, const Matrix<double>& yP,
                     Matrix<double>& mH, Matrix<double>& mP) {
  // Resize masks if needed.
  if (mH.size() != yH.size()) {
    mH.resize(yH.size());
  }

  if (mP.size() != yP.size()) {
    mP.resize(yP.size());
  }

  const size_t numOps = yH.getNumRows() * yH.getNumCols();

  // Apply binary mask.
  for (size_t i = 0; i < numOps; i++) {
    binaryMask(yH(i), yP(i), mH(i), mP(i));
  }
}

void applySoftMask(const Matrix<double>& yH, const Matrix<double>& yP,
                   Matrix<double>& mH, Matrix<double>& mP) {
  // Resize masks if needed.
  if (mH.size() != mH.size()) {
    mH.resize(yH.size());
  }

  if (mP.size() != mP.size()) {
    mP.resize(yP.size());
  }

  // Use threads to speed up computation.
  const size_t numOps = yH.getNumRows() * yH.getNumCols();
  const size_t NUM_THREADS = std::min<size_t>(BASE_NUM_THREADS, numOps);
  std::vector<std::thread> threads;
  threads.reserve(NUM_THREADS);

  size_t base = numOps / NUM_THREADS;
  size_t rem = numOps % NUM_THREADS;

  size_t start = 0;
  size_t end = 0;

  for (size_t i = 0; i < NUM_THREADS; i++) {
    start = i * base + std::min(i, rem);
    end = start + base + (i < rem ? 1 : 0);

    threads.emplace_back(std::thread(applySoftMaskSubset, std::ref(yH),
                                     std::ref(yP), std::ref(mH), std::ref(mP),
                                     start, end));
  }

  for (std::thread& thread : threads) {
    thread.join();
  }
}

void applySoftMaskSubset(const Matrix<double>& yH, const Matrix<double>& yP,
                         Matrix<double>& mH, Matrix<double>& mP, size_t start,
                         size_t end) {
  // Apply soft mask.
  for (size_t i = start; i < end; i++) {
    softMask(yH(i), yP(i), mH(i), mP(i));
  }
}
