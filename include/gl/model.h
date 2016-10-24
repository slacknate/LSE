#ifndef LSE_GL_MOD_H
#define LSE_GL_MOD_H

#include "gl/object.h"

namespace LSE {

/*
Base class for all model objects.
*/
class GLModel : public GLObject {
    
    protected:
        
        unsigned char *modelData; // model data read in from file
        
        virtual void LoadModel() {} // format-specific model loader
        
    public:
        
        GLModel(char *fileName, float x, float y, float z);
        ~GLModel();
};

}

#endif
