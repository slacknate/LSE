#ifndef LSE_LOGGER_H
#define LSE_LOGGER_H

#include <cstdio>

namespace LSE {

/*
Log level constants.
*/
typedef enum {
    
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_RAW
} LSE_LogLevel;

void LOG(LSE_LogLevel, ...);
void ERRNO(const char *const);

}

#endif
