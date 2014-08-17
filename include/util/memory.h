#ifndef LSE_MEMORY_H
#define LSE_MEMORY_H

namespace LSE {

template <class T> T* calloc(unsigned int size);
template <class T> T* malloc(unsigned int size, ...);

}

#endif
