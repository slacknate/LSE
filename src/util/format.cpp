#include <cwchar>
#include <cstdio>
#include <cstdarg>
#include "util/format.h"
#include "util/memory.h"
using namespace LSE;


char* format(const char *format, ...) {

    char *formatted = nullptr;

    va_list args;
    va_start(args, format);

    int log_length = vsnprintf(NULL, 0, format, args);
    if(log_length >= 0) {

        formatted = LSE::calloc<char>(log_length);
        vsprintf(formatted, format, args);
    }

    va_end(args);

    if(!formatted)
        throw Exception(__FILE__, __LINE__, "String formatting failed.");

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
        throw Exception(__FILE__, __LINE__, "String formatting failed.");

    return formatted;
}*/
