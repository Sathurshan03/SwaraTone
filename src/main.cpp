/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   main code.
 *******************************************************************************
 */

#include "coreLogic.h"
#include "logging.h"
#include "sampleData.h"

int main() {
  LOG_INFO("Hello! I am Swara Tone!");
  LOG_INFO("We will need a lot of coffee for this fun project!");

  // runSampleDataCore();
  runCore("sample.mp3");  // TODO: #20 implement arguments.
}
