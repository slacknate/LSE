#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include <sstream>
#include "lse/exception.h"
#include "util/format.h"
#include "lse/globals.h"
using namespace LSE;

/*
 * Have a hard length limit for exception messages
 * so we do not have to have a wack, slow, format method
 * that can detect message length.
 */
const unsigned int EXC_MESSAGE_MAX_LENGTH = 80;

/*
 * Create an exception, with a corresponding error message.
 * The error message is built from a format string and variadic
 * parameters. If a problem occurs during string formatting,
 * the error message is the original format string with no
 * parameters formatted in.
 */
Exception::Exception(const char *file, int line, const char *fmt, ...) noexcept {

    this->file_name = file;
    this->line_number = line;

    va_list args;
    va_start(args, fmt);

    try{

        this->error_message = vformat(fmt, EXC_MESSAGE_MAX_LENGTH, args);
    }
    catch(std::exception) {

        this->error_message = fmt;  // Sorry, your string formatting done goofed. Too bad for you!
    }

    va_end(args);
}

/*
 * Return the error message.
 */
const char* Exception::what() const noexcept {

    std::stringstream ss;

    ss << "An exception was thrown in \"" << this->file_name << "\" at line " << this->line_number << ": " << this->error_message;
    if(errno != 0) {

        ss << ": Errno (" << errno <<  "): " << strerror(errno);
    }

    return ss.str().c_str();
}