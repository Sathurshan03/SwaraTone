/**
 ******************************************************************************
 * @file    stats_argmax_test.cpp
 * @brief   Unit tests for stats argmax function.
 ******************************************************************************
 */

#include <gtest/gtest.h>

#include "stats.h"

/** @brief Struct for parameterized testing. */
struct ArgMaxParamType {
  std::vector<int> vec;  // Input vector to function.

  size_t startIdx;  // Input starting index to function.

  size_t endIdx;  // Input ending index to funciton.

  size_t expectedIdx;  // Expected returned index.
};

/** @brief Parameterized test class for argmax. */
class ArgmaxTest : public ::testing::TestWithParam<ArgMaxParamType> {};

/** @brief Given sample vector, starting index, and ending index, the correct
 * argument maximum is determined. */
TEST_P(ArgmaxTest, ArgMax) {
  ArgMaxParamType param = GetParam();

  ASSERT_EQ(argmax(param.vec, param.startIdx, param.endIdx), param.expectedIdx);
}

/** @brief Parametized options. */
INSTANTIATE_TEST_SUITE_P(
    ArgMaxParams, ArgmaxTest,
    ::testing::Values(ArgMaxParamType{{}, 1, 3, size_t(-1)},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 4, 3, size_t(-1)},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 3, 3, 3},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 0, 1, 0},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 0, 5, 3},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 4, 5, 4},
                      ArgMaxParamType{{9, 3, 4, 10, 7}, 1, 3, 2}));
