#ifndef LSE_GL_RECTANGLE_H
#define LSE_GL_RECTANGLE_H

#include "gl/primitive.h"

namespace LSE {

/*
Pre-defined quad primitive.
*/
class LSE_GLRectangle : public LSE_GLPrimitive {
    
    private:
        
        static const int QUAD_VERT_COUNT = 4;
        static const int QUAD_ELEM_COUNT = 2;
    
    protected:
        
        double width, height; // quad attributes
        
        void CalcVertices();
        void CalcIndices();
        void CalcTexCoords();
        
    public:
        
        LSE_GLRectangle(double x, double y, double z, double w, double h);
};

}

#endif
