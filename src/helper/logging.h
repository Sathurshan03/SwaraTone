/**
 *******************************************************************************
 * @file    logging.h
 * @brief   Logging header file.
 *******************************************************************************
 */

#pragma once
#include <string.h>

#include <sstream>
#include <string>

namespace LogInternal {
/**
 * @brief Generic log function to io stream.
 *
 * @param[in] level Logging level.
 * @param[in] file File that is sending the log message.
 * @param[in] line Line of the file that is sending the log message.
 * @param[in] msg The message to log.
 */
void log(const char* level, const char* file, int line, const std::string& msg);

}  // namespace LogInternal

// Helper macro to extract the filename from full path
#ifdef _WIN32
#define __FILENAME__ \
  (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

// ----- ERROR LOGGING -----
#ifdef ENABLE_LOGGING
#define LOG_ERROR(msg)                                             \
  do {                                                             \
    std::stringstream ss__;                                        \
    ss__ << msg;                                                   \
    LogInternal::log("ERROR", __FILENAME__, __LINE__, ss__.str()); \
  } while (0)
#else
#define LOG_ERROR(msg) \
  do {                 \
  } while (0)
#endif

// ----- WARNING LOGGING -----
#ifdef ENABLE_LOGGING
#define LOG_WARNING(msg)                                             \
  do {                                                               \
    std::stringstream ss__;                                          \
    ss__ << msg;                                                     \
    LogInternal::log("WARNING", __FILENAME__, __LINE__, ss__.str()); \
  } while (0)
#else
#define LOG_WARNING(msg) \
  do {                   \
  } while (0)
#endif

// ----- INFO LOGGING -----
#ifdef ENABLE_LOGGING
#define LOG_INFO(msg)                                             \
  do {                                                            \
    std::stringstream ss__;                                       \
    ss__ << msg;                                                  \
    LogInternal::log("INFO", __FILENAME__, __LINE__, ss__.str()); \
  } while (0)
#else
#define LOG_INFO(msg) \
  do {                \
  } while (0)
#endif
