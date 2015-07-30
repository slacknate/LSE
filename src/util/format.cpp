#include <cwchar>
#include <cstdio>
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

    int fmt_length = vsnprintf(NULL, 0, fmt, args);
    if(fmt_length >= 0) {

        formatted = LSE::calloc<char>((size_t)fmt_length);
        vsprintf(formatted, fmt, args);
    }
    else {

        throw EXCEPTION("Failed to get formatted string length.");
    }

    return formatted;
}


/*wchar_t* wformat(const wchar_t *format, ...) {

    wchar_t *formatted = nullptr;

    va_list args;
    va_start(args, format);

    int log_length = vsnprintf(NULL, 0, format, args);
    if(log_length >= 0) {

        formatted = LSE::calloc<wchar_t>(log_length);
        vswprintf(formatted, format, args);
    }

    va_end(args);

    if(!formatted)
        throw EXCEPTION("String formatting failed.");

    return formatted;
}*/
