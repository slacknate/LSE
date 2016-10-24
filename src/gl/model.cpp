#include <cstdio>
#include "gl/model.h"
using namespace LSE;

/*

*/
GLModel::GLModel(char *fileName, float x, float y, float z) : GLObject(x, y, z) {
    
    if(fileName) {
        
        FILE *model = fopen(fileName, "rb");
        if(model) {
            
            fseek(model, 0, SEEK_END);
            int fileSize = ftell(model);
            rewind(model);
        
            modelData = new (std::nothrow) unsigned char [fileSize];
            if(modelData)
                fread(modelData, sizeof(unsigned char), fileSize, model);
            else
                printf("Failed to allocate memory for model.");
            
            fclose(model);
        }
        else {
            
            printf("Failed to open model file.");
        }
    }
}

/*

*/
GLModel::~GLModel() {
    
    if(modelData)
        delete[] modelData;
}
