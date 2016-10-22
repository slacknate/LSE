#ifndef LSE_FORMAT_H
#define LSE_FORMAT_H

namespace LSE {

char* format(const char *fmt, size_t max_chars, ...);
char* vformat(const char *fmt, size_t max_chars, va_list &args);

wchar_t* wformat(const wchar_t *fmt, size_t max_chars, ...);
wchar_t* vwformat(const wchar_t *fmt, size_t max_chars, va_list &args);

}

#endif //LSE_FORMAT_H
