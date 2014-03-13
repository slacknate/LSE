#ifndef LSE_EXCEPTION_H
#define LSE_EXCEPTION_H

#define BUFFER_SIZE 128

/*
Exception class used to display file names and
line numbers automatically.
TODO:
    extended OS error code info
*/
class LSE_Exception {
    
    private:
        
        char output[BUFFER_SIZE];
        const char *fileName;
        int lineNumber, errCode; // error code
    
    public:
        
        LSE_Exception(const char *f, int l, int c) throw();
        
        const char* what() const throw();
        const int code() const throw();
};

#endif
