#ifndef LSE_EXCEPTION_H
#define LSE_EXCEPTION_H

#include <iostream>
#include <stdexcept>
#include <exception>
#include "lse/defs.h"

/*
Exception function macros.
*/
#define LSE_TRY()               try { try {
#define LSE_THROW(X)            throw LSE_Exception(__FILE__, __LINE__, X)
#define LSE_CATCH()             } catch(const std::bad_alloc& ba) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_ALLOC); } \
                                catch(const std::bad_cast& bc) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_CAST); } \
                                catch(const std::bad_typeid& bt) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_TYPE_ID); } \
                                catch(const std::bad_exception& be) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_EXCEPTION); } \
                                catch(const std::ios_base::failure& iof) { throw LSE_Exception(__FILE__, __LINE__, LSE_IOS_FAIL); } \
                                catch(const std::runtime_error& re) { throw LSE_Exception(__FILE__, __LINE__, LSE_RUNTIME_ERR); } \
                                catch(const std::logic_error& le) { throw LSE_Exception(__FILE__, __LINE__, LSE_LOGIC_ERR); } \
                                } catch(const LSE_Exception& e) { LSE_WriteLog(LOG_LEVEL_ERROR, stderr, "%s", e.what()); LSE_ErrorStatus(e.code()); }

#define ERROR_BUFFER_SIZE 128

/*
Exception class used to display file names and
line numbers automatically.
TODO:
    extended OS error code info
*/
class LSE_Exception {
    
    private:
        
        char output[ERROR_BUFFER_SIZE + 1];
        const char *fileName;
        int lineNumber, errCode; // error code
    
    public:
        
        LSE_Exception(const char *f, int l, int c) throw();
        
        const char* what() const throw();
        const int code() const throw();
};

#endif
