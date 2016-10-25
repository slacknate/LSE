#include <cstdio>
#include "util/file.h"
#include "util/memory.h"
using namespace LSE;


/*
 * Helper to open a file and read the entire contents.
 */
unsigned char* read_file(const char *const file_name) {

    unsigned char *buffer = nullptr;

    FILE *file_pointer = fopen(file_name, "rb");
    if(file_pointer) {

        // get file size
        fseek (file_pointer, 0, SEEK_END);
        size_t file_size = (size_t)ftell(file_pointer);
        rewind(file_pointer);

        // allocate our buffer and read our data into it
        try {

            buffer = LSE::MALLOC(unsigned char, file_size + 1);
        }
        catch(std::exception) {

            // we failed to allocate memory, close our file
            fclose(file_pointer);
            throw;
        }

        fread(buffer, sizeof(char), file_size, file_pointer);

        // explicitly null terminate for safety
        buffer[file_size] = '\0';

        // close our file as we are done with it
        fclose(file_pointer);
    }
    else {

        throw EXCEPTION("Unable to open file '%s'.", file_name);
    }

    return buffer;
}
