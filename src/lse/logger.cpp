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

char* indent_newlines(unsigned int prefix_len, const char *format) {
    
    char prefix_buffer[prefix_len];
    memset(prefix_buffer, ' ', prefix_len);
    
    unsigned int format_len = strlen(format);
    unsigned int num_newlines = 0;
    for(unsigned int i = 0; i < format_len; ++i) {
        
        if(format[i] == '\n')
            ++num_newlines;
    }
    
    unsigned int new_format_len = (num_newlines * prefix_len) + format_len + 1;
    char *new_format = new (std::nothrow) char[new_format_len];
    if(new_format == NULL) {
        
         // FIXME: uhhh... do we log this? wont that be some SERIOUS RECURSION BRO?!
    }
    
    memset(new_format, 0, new_format_len);
    
    unsigned int i = 0, k = 0;
    for(; i < format_len; ++i, ++k) {
        
        new_format[k] = format[i];
        if(format[i] == '\n') {
            
            strncat(new_format, prefix_buffer, prefix_len);
            k += prefix_len;
        }
    }

    return new_format;
}

/*
TODO: use strftime, auto newline around 80 characters
*/
void write_log(LogLevel log_level, FILE *stream, va_list &arg_list) {
    
    if(log_level <= LOG_LEVEL) {
        
        char *time_str = new (std::nothrow) char [9];
        if(stream != NULL && time_str != NULL) {
        
            memset(time_str, 0, 9);
        
            time_t t;
            time(&t);
            char *static_time = ctime(&t);
    
            strncpy(time_str, &static_time[11], 8);
        
            int prefix_len = fprintf(stream, "[%s] %s: ", time_str, LOG_LEVEL_PREFIXS[log_level]);
            if(prefix_len < 0) {
                
                // FIXME: what should we do here? this is an error case...
            }
            
            const char *format = va_arg(arg_list, const char *);
            char *indented_format = indent_newlines(prefix_len, format);
            
            vfprintf(stream, indented_format, arg_list);
            fprintf(stream, "\n");
            
            fflush(stream);
            
            delete[] time_str;
            delete[] indented_format;
        }
        else {
        
            LOG(LOG_LEVEL_ERROR, "Could not create time string or NULL log stream supplied.");
        }
    }
}

void errno_helper(LogLevel log_level, FILE *stream, ...) {
    
    va_list arg_list;
    va_start(arg_list, stream);
    
    write_log(log_level, stream, arg_list);
    
    va_end(arg_list);
}

namespace LSE {

void LOG(LogLevel log_level, ...) {
    
    va_list arg_list;
    va_start(arg_list, log_level);
    
    if(log_level == LOG_LEVEL_ERROR)
        ::write_log(log_level, stderr, arg_list);
        
    else
        ::write_log(log_level, stdout, arg_list);
    
    va_end(arg_list);
}

void ERRNO(const char *const errno_msg) {
    
    ::errno_helper(LOG_LEVEL_ERROR, stderr, "%s: %s", errno_msg, strerror(errno));
}

}
