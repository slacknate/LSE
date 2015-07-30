#include <cerrno>
#include <cstring>
#include <iostream>
#include "lse/logger.h"
#include "lse/engine.h"
#include "util/time.h"
#include "util/format.h"
#include "util/memory.h"
using namespace LSE;

const unsigned int LOG_BUFFER_SIZE = 32;
const unsigned int LOG_LINE_LENGTH = 66;
const unsigned int LOG_PREFIX_LENGTH = 14;

const char *const LOG_INDENT_STR = "\n              ";

const char *const LOG_LEVEL_PREFIXS[] = {
    
    "I",
    "D",
    "E",
    "V",
    "R",
};


/*
Initialize our log buffers memory.
*/
Logger::Logger(LogLevel _level) : level(_level), buffer(LOG_BUFFER_SIZE) {}


/*
Stop the logger write-to-disk thread.
*/
bool Logger::join() {
    
    running = false;
    this->log_sem.post();
    return Thread::join();
}


/*
Thread to write log events to their respective log files.
*/
void* Logger::execute() {
    
    while(this->running) {

        this->log_sem.wait();
        
        /*
        When we stop the logger, the post to the semaphore, but the buffer is
        empty. Thusly we need to make sure to skip writing a log event if
        we are terminating the logger.
        */
        if(this->running) {
            
            LogEvent *log_event = this->buffer.pop();
            
            /*
            Explode the log event tuple, pass the elements to write_log.
            */
            this->write_log(std::get<0>(*log_event), std::get<1>(*log_event), std::get<2>(*log_event));
            
            delete log_event;
        }
    }
    
    return nullptr;
}


/*
Write a log entry to disk. We only record entries which are
greater or equal log level to the log level of the logger.

TODO: format properly, auto newline around 80 characters
*/
void Logger::write_log(LogLevel log_level, std::ostream &stream, char *fmt_log) {
    
    if(log_level <= this->level) {
        
        char *time_str = LSE::calloc<char>(TIME_STR_LENGTH);            
        LSE::get_local_time(time_str);
            
        stream << "[" << time_str << "] " << LOG_LEVEL_PREFIXS[log_level] << ": " << fmt_log << std::endl;
        
        delete[] time_str;
        delete[] fmt_log;
    }
}


/*

*/
void Logger::log_event(LogLevel log_level, std::ostream &stream, const char *fmt, va_list &args) {

    LogEvent log_event = LogEvent(log_level, stream, vformat(fmt, args));
    this->buffer.push(log_event);

    this->log_sem.post();
}


/*
Log a simple informative log message at LOG_LEVEL_INFO.
*/
void Logger::info(const char *format, ...) {
    
    va_list args;
    va_start(args, format);
    
    this->log_event(LOG_LEVEL_INFO, std::cout, format, args);
    
    va_end(args);
}


/*
Log engine debugging information at LOG_LEVEL_DEBUG.
*/
void Logger::debug(const char *format, ...) {
    
    va_list args;
    va_start(args, format);
    
    this->log_event(LOG_LEVEL_DEBUG, std::cout, format, args);
    
    va_end(args);
}


/*
Log an engine error at LOG_LEVEL_ERROR.
*/
void Logger::error(const char *format, ...) {
    
    va_list args;
    va_start(args, format);
    
    this->log_event(LOG_LEVEL_ERROR, std::cerr, format, args);
    
    va_end(args);
}


/*
Log an errno message at LOG_LEVEL_ERROR.
*/
void Logger::errn(const char *error_msg) {
    
    this->error("%s: %s", error_msg, strerror(errno));
}


/*
Log a message at LOG_LEVEL_VERBOSE.
This is used for log messages we
typically do not need to see.
*/
void Logger::verbose(const char *format, ...) {
    
    va_list args;
    va_start(args, format);
    
    this->log_event(LOG_LEVEL_VERBOSE, std::cout, format, args);
    
    va_end(args);
}


/*
Log a message at LOG_LEVEL_RAW.
This is mostly used for data dumps.
*/
void Logger::raw(const char *format, ...) {
    
    va_list args;
    va_start(args, format);
    
    this->log_event(LOG_LEVEL_RAW, std::cout, format, args);
    
    va_end(args);
}


/*char* indent_newlines(const char *format) {
    
    char prefix_buffer[LOG_PREFIX_LENGTH];
    memset(prefix_buffer, ' ', LOG_PREFIX_LENGTH);
    
    unsigned int format_len = strlen(format);
    unsigned int num_newlines = 0;
    for(unsigned int i = 0; i < format_len; ++i) {
        
        if(format[i] == '\n')
            ++num_newlines;
    }
    
    unsigned int new_format_len = (num_newlines * LOG_PREFIX_LENGTH) + format_len + 1;
    char *new_format = new (std::nothrow) char[new_format_len];
    if(new_format == NULL) {
        
         // FIXME: uhhh... do we log this? wont that be some SERIOUS RECURSION BRO?!
    }
    
    memset(new_format, 0, new_format_len);
    
    unsigned int i = 0, k = 0;
    for(; i < format_len; ++i, ++k) {
        
        new_format[k] = format[i];
        if(format[i] == '\n') {
            
            strncat(new_format, prefix_buffer, LOG_PREFIX_LENGTH);
            k += LOG_PREFIX_LENGTH;
        }
    }

    return new_format;
}*/
