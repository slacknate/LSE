#ifndef LSE_EXCEPTION_H
#define LSE_EXCEPTION_H

#include <iostream>
#include <stdexcept>
#include <exception>

namespace LSE {

/*
Exception class used to display file names and
line numbers automatically.
TODO:
    extended OS error code info
*/
class Exception {
    
    private:
        
        static const int ERROR_BUFFER_SIZE = 128;
        
        char output[ERROR_BUFFER_SIZE + 1];
        const char *fileName;
        int lineNumber, errCode; // error code
    
    public:
        
        Exception(const char *f, int l, int c) throw();
        
        const char* what() const throw();
        const int code() const throw();
};

}

#endif
