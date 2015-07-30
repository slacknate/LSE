#ifndef LSE_FORMAT_H
#define LSE_FORMAT_H

namespace LSE {

char* format(const char *fmt, ...);
char* vformat(const char *fmt, va_list &args);

//wchar_t* wformat(const wchar_t *format, ...);

}

#endif //LSE_FORMAT_H
