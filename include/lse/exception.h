#ifndef LSE_EXCEPTION_H
#define LSE_EXCEPTION_H

#include <exception>

namespace LSE {

/*
Exception class used to display file names and
line numbers automatically.
TODO:
    extended OS error code info
*/
class Exception : public std::exception {
    
    private:

        int line_number;
        const char *file_name, *error_message;

    public:
        
        Exception(const char *file, int line, const char *fmt, ...) noexcept;
        
        const char* what() const noexcept;
};

}

/*
Macro to wrap the Exception class. This automatically inserts the file and line number.
Note that if this macro is used outside of the LSE namespace you MUST provide the LSE:: prefix
like you would directly accessing the Exception class.
*/
#define EXCEPTION(...) Exception(__FILE__, __LINE__, __VA_ARGS__)

#endif
