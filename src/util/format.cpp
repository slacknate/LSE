#include <cstdio>
#include <cwchar>
#include <cstdarg>
#include "util/format.h"
#include "util/memory.h"
using namespace LSE;


/*
 * Format a string with the given parameters.
 * This is more or less a wrapper around vformat.
 */
char* format(const char *fmt, ...) {

    char *formatted = nullptr;

    va_list args;
    va_start(args, fmt);

    try {

        formatted = vformat(fmt, args);
    }
    catch(std::exception &err) {

        va_end(args);
        throw;
    }

    va_end(args);

    return formatted;
}


/*
 * Format a string with the given va_list arguments.
 * We first attempt to get the length of the formatted
 * string. If this succeeds we allocate a buffer
 * and fill it with the formatted string, otherwise we
 * raise an exception indicating that we were unable
 * to calculate the formatted string length.
 */
char* vformat(const char *fmt, va_list &args) {

    char *formatted = nullptr;

    int num_written = vsnprintf(NULL, 0, fmt, args);
    if(num_written > 0) {

        size_t fmt_length = (size_t)num_written;

        // Allocate an extra character to accommodate for null termination.
        formatted = LSE::calloc<char>(fmt_length + 1);
        vsnprintf(formatted, fmt_length, fmt, args);
    }
    else if(num_written < 0) {

        throw EXCEPTION("Failed to get formatted string length.");
    }

    return formatted;
}


/*
 * Format a unicode string with the given parameters.
 * This is more or less a wrapper around vwformat.
 */
wchar_t* wformat(const wchar_t *fmt, ...) {

    wchar_t *formatted = nullptr;

    va_list args;
    va_start(args, fmt);

    try {

        formatted = vwformat(fmt, args);
    }
    catch(std::exception &err) {

        va_end(args);
        throw;
    }

    va_end(args);

    return formatted;
}


/*
 * Format a unicode string with the given va_list arguments.
 * We first attempt to get the length of the formatted
 * string. If this succeeds we allocate a buffer
 * and fill it with the formatted string, otherwise we
 * raise an exception indicating that we were unable
 * to calculate the formatted string length.
 */
wchar_t* vwformat(const wchar_t *fmt, va_list &args) {

    wchar_t *formatted = nullptr;

    int num_written = vswprintf(NULL, 0, fmt, args);
    if(num_written > 0) {

        size_t fmt_length = (size_t)num_written;

        // Allocate an extra character to accommodate for null termination.
        formatted = LSE::calloc<wchar_t>(fmt_length + 1);
        vswprintf(formatted, fmt_length, fmt, args);
    }
    else if(num_written < 0) {

        throw EXCEPTION("Failed to get formatted string length.");
    }

    return formatted;
}