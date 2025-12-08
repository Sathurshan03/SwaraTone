/**
 *******************************************************************************
 * @file    logging.cpp
 * @brief   Logging source code.
 *******************************************************************************
 */

#include "logging.h"

#include <iostream>

namespace LogInternal {

void log(const char* level, const char* file, int line,
         const std::string& msg) {
  std::cerr << "[" << level << "] (" << file << ":" << line << ") " << msg
            << std::endl;
}

}  // namespace LogInternal
