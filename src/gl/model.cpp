#include "gl/model.h"

/*

*/
LSE_GLModel::LSE_GLModel(char *fileName, double x, double y, double z) : LSE_GLObject(x, y, z) {
    
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
LSE_GLModel::~LSE_GLModel() {
    
    if(modelData)
        delete[] modelData;
}
