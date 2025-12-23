/**
 *******************************************************************************
 * @file    hpssMask.cpp
 * @brief   HPSS (Harmonic Percussive Source Seperation) mask source.
 *******************************************************************************
 */

#include <gtest/gtest.h>

#include "hpssMask.hpp"
#include "test_helper.h"

/** @brief Tests HPSS binary mask exclusively selects harmonic component. */
TEST(HPSSBinaryMask, HarmonicSelected) {
  // Run binary mask on values such that harmonic is selected one.
  double yH = 10.0;
  double yP = 9.0;
  double mH;
  double mP;

  binaryMask(yH, yP, mH, mP);

  // Assert that harmonic is selected.
  ASSERT_NEAR(mH, 1.0, PRECISION_ERROR);
  ASSERT_NEAR(mP, 0.0, PRECISION_ERROR);
}

/** @brief Tests HPSS binary mask exclusively selects percussive component. */
TEST(HPSSBinaryMask, PercussiveSelected) {
  // Run binary mask on values such that percussive is selected one.
  double yH = 7.0;
  double yP = 9.0;
  double mH;
  double mP;

  binaryMask(yH, yP, mH, mP);

  // Assert that percussive is selected.
  ASSERT_NEAR(mH, 0.0, PRECISION_ERROR);
  ASSERT_NEAR(mP, 1.0, PRECISION_ERROR);
}

/** @brief Tests HPSS soft mask puts more bias on harmonic when there is more
 * harmonic components than the percussive. */
TEST(HPSSSoftMask, HarmonicBias) {
  // Run soft mask on values such that harmonic has more bias.
  double yH = 10.0;
  double yP = 9.0;
  double mH;
  double mP;

  softMask(yH, yP, mH, mP);

  // Assert that harmonic has more bias.
  ASSERT_GT(mH, mP);
  ASSERT_LE(mH, 1.0);
  ASSERT_GE(mH, 0.0);
}

/** @brief Tests HPSS soft mask puts more bias on percussive when there is more
 * percussive components than the harmonic. */
TEST(HPSSSoftMask, PercussiveBias) {
  // Run soft mask on values such that percussive has more bias.
  double yH = 7.0;
  double yP = 9.0;
  double mH;
  double mP;

  softMask(yH, yP, mH, mP);

  // Assert that percussive has more bias.
  ASSERT_GT(mP, mH);
  ASSERT_LE(mP, 1.0);
  ASSERT_GE(mP, 0.0);
}
