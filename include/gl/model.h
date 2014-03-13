#ifndef LSE_GL_MOD_H
#define LSE_GL_MOD_H

#include "gl/object.h"

/*
Base class for all model objects.
*/
class LSE_GLModel : public LSE_GLObject {
    
    protected:
        
        unsigned char *modelData; // model data read in from file
        
        virtual void LoadModel() {} // format-specific model loader
        
    public:
        
        LSE_GLModel(char *fileName, double x, double y, double z);
        ~LSE_GLModel();
};

#endif
