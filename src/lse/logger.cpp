#include <new>
#include <ctime>
#include <cstdarg>
#include <cstring>
#include "lse/logger.h"

void LSE_WriteLog(LSE_LogLevel level, FILE *stream, ...) {
    
    char *timeStr = new (std::nothrow) char [9];
    if(stream != NULL && timeStr != NULL) {
        
        memset(timeStr, 0, 9);
        
        time_t t;
        time(&t);
        char *static_time = ctime(&t);
    
        strncpy(timeStr, &static_time[11], 8);
        
        fprintf(stream, "[%s]: ", timeStr);
        
        delete[] timeStr;
        timeStr = NULL;
        
        va_list argList;
        va_start(argList, stream);
        
        const char *format = va_arg(argList, const char *);
        vfprintf(stream, format, argList);
    
        va_end(argList);
        
        fprintf(stream, "\n");
    }
    else {
        
        LSE_ERROR_LOG("Could not create time string or NULL log stream supplied.");
    }
}
