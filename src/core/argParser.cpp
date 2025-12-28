/**
 *******************************************************************************
 * @file    argParser.h
 * @brief   Argument parser source code.
 *******************************************************************************
 */

#include "argParser.h"

#include <iostream>

#include "logging.h"

Arguments parseArgumnets(int argc, char* argv[]) {
  Arguments arguments{};

  for (int i = 1; i < argc; i++) {
    std::string_view arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      displayHelp();
      arguments.action = ParseAction::ExitSuccess;
      break;
    }

    else if (arg == "-f" && (i + 1) < argc) {
      arguments.filePath = argv[++i];
    } else {
      arguments.action = ParseAction::ExitFailure;
      LOG_ERROR("Unknown or malformed argument: "
                << std::string(arg)
                << ". Use -h or --help to view the full argument list.");
    }
  }

  return arguments;
}

void displayHelp() {
  std::cout << std::endl;
  std::cout << "SwaraTone" << std::endl;
  std::cout << "\nArguments" << std::endl;
  std::cout << "=========" << std::endl;
  std::cout << "-f <file_path>   Path to audio file to run audio decomposition."
            << std::endl;
  std::cout << std::endl;
}
