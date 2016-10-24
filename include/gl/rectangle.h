#ifndef LSE_GL_RECTANGLE_H
#define LSE_GL_RECTANGLE_H

#include "gl/primitive.h"

namespace LSE {

/*
Pre-defined quad primitive.
*/
class GLRectangle : public GLPrimitive {
    
    private:
        
        static const int QUAD_VERT_COUNT = 4;
        static const int QUAD_ELEM_COUNT = 2;
    
    protected:
        
        float width, height; // quad attributes
        
        void CalcVertices();
        void CalcIndices();
        void CalcTexCoords();
        
    public:
        
        GLRectangle(float x, float y, float z, float w, float h);
};

}

#endif
