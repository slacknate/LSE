#ifndef LSE_EXCEPTION_H
#define LSE_EXCEPTION_H

/*
TODO: move these includes to the .cpp file?
*/
#include <iostream>
#include <stdexcept>
#include <exception>

namespace LSE {

/*
Exception class used to display file names and
line numbers automatically.
TODO:
    add a flag to check the errno error code/message
    extended OS error code info
*/
class Exception {
    
    private:

        int line_number;
        const char *file_name, *error_message;

    public:
        
        Exception(const char *file, int line, const char *message) throw();
        
        const char* what() const throw();
};

}

#endif
