#ifndef LSE_MATERIAL_H
#define LSE_MATERIAL_H

#include "lse/object.h"

/*
Class that describes material lighting properties.
*/
class LSE_GLMaterial : LSE_Object {
    
    private:
        
        float parameters[24]; // array containing all parameters
        
    public:
        
        LSE_GLMaterial();
        
        void Bind();
        void Unbind();
        
        void SetAmbient(float x, float y, float z, float w);
        void SetDiffuse(float x, float y, float z, float w);
        void SetSpecular(float x, float y, float z, float w);
        void SetEmission(float x, float y, float z, float w);
        void SetAmbAndDiff(float x, float y, float z, float w);
        void SetColorIndices(float x, float y, float z);
        void SetShininess(float x);
};

#endif
