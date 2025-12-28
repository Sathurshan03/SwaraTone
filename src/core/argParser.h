/**
 *******************************************************************************
 * @file    argParser.h
 * @brief   Argument parser header.
 *******************************************************************************
 */

#pragma once

#include <string>

/** @brief Argument parsing action status. */
enum ParseAction { Continue, ExitSuccess, ExitFailure };

/** @brief Struct holding parsed argument values. */
struct Arguments {
  /** @brief Parsing action result. */
  ParseAction action{ParseAction::Continue};

  /** @brief File path to audio file. */
  std::string filePath{"sample.mp3"};
};

/**
 * @brief Parse command line arguments.
 *
 * @param argc Number of arguments.
 * @param argv Arguments.
 * @return Arguments Parsed arguments.
 */
Arguments parseArgumnets(int argc, char* argv[]);

/** @brief Display help info for command line. */
void displayHelp();
