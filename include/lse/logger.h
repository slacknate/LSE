#ifndef LSE_LOGGER_H
#define LSE_LOGGER_H

#include <cstdio>

/*
Logging function macros.
*/
#define LSE_MESSG_LOG(level, ...)   LSE_WriteLog(level, stdout, __VA_ARGS__)
#define LSE_ERROR_LOG(...)          LSE_WriteLog(LOG_LEVEL_ERROR, stderr, __VA_ARGS__)
#define LSE_ERRNO_LOG(X)            LSE_WriteLog(LOG_LEVEL_ERROR, stderr, "%s: %s", X, strerror(errno))

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

void LSE_WriteLog(LSE_LogLevel level, FILE *stream, ...);

#endif
