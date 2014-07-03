#ifndef LSE_GL_LIGHT_H
#define LSE_GL_LIGHT_H

#include "lse/object.h"

namespace LSE {

class LSE_GLLight : LSE_Object {
    
    private:
        
        float parameters[24]; // array containing all parameters
        
    public:
        
        LSE_GLLight();
        
        void Render();
        
        void SetPosition(float x, float y, float z, float w);
        void SetAmbient(float x, float y, float z, float w);
        void SetDiffuse(float x, float y, float z, float w);
        void SetSpecular(float x, float y, float z, float w);
        void SetSpotDirection(float x, float y, float z);
        void SetSpotExponent(float x);
        void SetSpotCutoff(float x);
        void SetConstAtten(float x);
        void SetLinearAtten(float x);
        void SetQuadAtten(float x);
};

}

#endif
