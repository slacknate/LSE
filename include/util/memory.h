#ifndef LSE_MEMORY_H
#define LSE_MEMORY_H

#include <new>
#include <cstring>
#include "lse/defs.h"
#include "lse/exception.h"

namespace LSE {


/*
Allocate a block of memory and initialize to zero.
Throw an exception in the event of allocation failure.
This should be used for basic types and structs.
*/
template <class T> T* calloc(size_t size, const char *file, int line) {
    
    T *t_ptr = new (std::nothrow) T [size];
    if(t_ptr != nullptr) {
        
        memset(t_ptr, 0, sizeof(T) * size);
    }
    else{
        
        throw Exception(file, line, "An error occurred during memory allocation");
    }
    
    return t_ptr;
}


/*
 */
#define CALLOC(t, size) calloc<t>(size, __FILE__, __LINE__)


/*
Allocate a block of memory.
Throw an exception in the event of allocation failure.
This should be used for classes. Note that this will only
call a default constructor; if a more specialized constructor
is required, use template specialization to override this function.
*/
template <class T> T* malloc(size_t size, const char *file, int line) {
    
    T *t_ptr = new (std::nothrow) T [size];
    if(t_ptr == nullptr) {

        throw Exception(file, line, "An error occurred during memory allocation");
    }
    
    return t_ptr;
}


/*
 */
#define MALLOC(t, size) malloc<t>(size, __FILE__, __LINE__)


}

#endif
