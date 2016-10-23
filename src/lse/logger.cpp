#include <cerrno>
#include <cstring>
#include <iostream>
#include "lse/logger.h"
#include "lse/engine.h"
#include "util/time.h"
#include "util/format.h"
#include "util/memory.h"
using namespace LSE;

/*
 * Have a hard length limit for log messages
 * so we do not have to have a wack, slow, format method
 * that can detect message length.
 */
const unsigned int LOG_MAX_LENGTH = 120 - TIME_STR_LENGTH - 6;

const unsigned int LOG_BUFFER_SIZE = 32;
const unsigned int LOG_LINE_DELIM_LENGTH = 2;

const char *const LOG_NEW_LINE = "\n              ";
const char *const LOG_LINE_DELIM = "\\n";

const char *const LOG_LEVEL_PREFIXS[] = {
    
    "E",
    "I",
    "D",
    "V",
    "R",
};


/*
 *
 */
LogMessage::LogMessage(LogLevel _level, std::ostream& _stream, char* _message) :
        level(_level), stream(_stream), message(_message) {}


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

            LogMessage *container = this->buffer.pop();

            /*
            Explode the log event tuple, pass the elements to write_log.
            */
            this->write_log(container->level, container->stream, container->message);
            
            delete container;
        }
    }
    
    return nullptr;
}


/*
Write a log entry to disk. We only record entries which are
greater or equal log level to the log level of the logger.
*/
void Logger::write_log(LogLevel level, std::ostream &stream, char *message) {
    
    char *time_str = LSE::calloc<char>(TIME_STR_LENGTH);
    LSE::get_local_time(time_str);

    stream << "[" << time_str << "] " << LOG_LEVEL_PREFIXS[level] << ": " << message << std::endl;

    delete[] time_str;
    delete[] message;
}


/*

*/
void Logger::log_event(LogLevel level, std::ostream &stream, const char *fmt, va_list &args) {

    if(level <= this->level) {

        LogMessage *container = new LogMessage(level, stream, vformat(fmt, LOG_MAX_LENGTH, args));

        this->buffer.push(container);

        this->log_sem.post();
    }
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
