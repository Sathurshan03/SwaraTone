/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   main code.
 *******************************************************************************
 */

#include <QtWidgets/QApplication>

#include "argParser.h"
#include "coreLogic.h"
#include "logging.h"
#include "sampleData.h"

int main(int argc, char* argv[]) {
  LOG_INFO("Hello! I am Swara Tone!");
  LOG_INFO("We will need a lot of coffee for this fun project!");

  QApplication app(argc, argv);

  // Parse arguments.
  Arguments arguments = parseArgumnets(argc, argv);
  switch (arguments.action) {
    case ParseAction::ExitFailure:
      return 1;
      break;

    case ParseAction::ExitSuccess:
      return 0;
      break;

    case ParseAction::Continue:
    default:
      break;
  }

  // Run main code.
  runCore(arguments.filePath);

  return 0;
}
