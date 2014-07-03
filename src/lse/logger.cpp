#include <new>
#include <ctime>
#include <cstdarg>
#include <cstring>
#include "lse/logger.h"
#include "lse/engine.h"
using namespace LSE;

const char *const LOG_LEVEL_PREFIXS[] = {
    
    "I",
    "D",
    "E",
    "V",
    "R",
};

void WriteLog(LSE_LogLevel log_level, FILE *stream, va_list &arg_list) {
    
    if(log_level <= LSE_Engine::log_level) {
        
        char *timeStr = new (std::nothrow) char [9];
        if(stream != NULL && timeStr != NULL) {
        
            memset(timeStr, 0, 9);
        
            time_t t;
            time(&t);
            char *static_time = ctime(&t);
    
            strncpy(timeStr, &static_time[11], 8);
        
            fprintf(stream, "[%s] %s: ", timeStr, LOG_LEVEL_PREFIXS[log_level]);
        
            delete[] timeStr;
            timeStr = NULL;
            
            const char *format = va_arg(arg_list, const char *);
            vfprintf(stream, format, arg_list);
        
            fprintf(stream, "\n");
        }
        else {
        
            LOG(LOG_LEVEL_ERROR, "Could not create time string or NULL log stream supplied.");
        }
    }
}

namespace LSE {

void LOG(LSE_LogLevel log_level, ...) {
    
    va_list arg_list;
    va_start(arg_list, log_level);
    
    if(log_level == LOG_LEVEL_ERROR)
        WriteLog(log_level, stderr, arg_list);
        
    else
        WriteLog(log_level, stdout, arg_list);
    
    va_end(arg_list);
}

void errno_helper(LSE_LogLevel log_level, FILE *stream, ...) {
    
    va_list arg_list;
    va_start(arg_list, stream);
    
    WriteLog(log_level, stream, arg_list);
    
    va_end(arg_list);
}

void ERRNO(const char *const errno_msg) {
    
    errno_helper(LOG_LEVEL_ERROR, stderr, "%s: %s", errno_msg, strerror(errno));
}

}
