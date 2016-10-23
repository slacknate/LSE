#ifndef LSE_LOGGER_H
#define LSE_LOGGER_H

#include <queue>
#include <cstdarg>
#include <ostream>
#include "lse/thread.h"
#include "lse/semaphore.h"

namespace LSE {

/*
Log level constants.
*/
enum LogLevel : unsigned int {
    
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_INFO ,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_RAW
};


class LogMessage {

    public:

        LogLevel level;
        std::ostream& stream;
        char* message;

        LogMessage(LogLevel _level, std::ostream& _stream, char* _message);
};


typedef std::queue<LogMessage*> LogQueue;

/*
Logger class used as the global logger.

Reference:
    http://mortoray.com/2014/05/29/wait-free-queueing-and-ultra-low-latency-logging/
    
Note:
    This class probably does not quite implement what the link implies it does, as
    I do not believe I have the same locking (or lack thereof) the article speaks of.
*/
class Logger : public Thread {
    
    private:
        
        LogLevel level;
        LogQueue queue;
        Semaphore log_sem;

        void* execute();

        void write_log(LogLevel level, std::ostream &stream, char *message);
        void log_event(LogLevel level, std::ostream &stream, const char *fmt, va_list &args);
        
    public:
        
        Logger(LogLevel _level);
        
        bool join();
        
        void info(const char *format, ...);
        void debug(const char *format, ...);
        void error(const char *format, ...);
        void errn(const char *errno_msg);
        void verbose(const char *format, ...);
        void raw(const char *format, ...);
};

}

#endif
