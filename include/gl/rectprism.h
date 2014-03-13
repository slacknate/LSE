#ifndef LSE_GL_RECT_PRISM_H
#define LSE_GL_RECT_PRISM_H

#include "gl/primitive.h"

#define RECTP_VERT_COUNT 24
#define RECTP_ELEM_COUNT 12

/*
Pre-defined rectangular prism primitive.
*/
class LSE_GLRectPrism : public LSE_GLPrimitive {
    
    protected:
        
        double width, height, depth; // prism attributes
        
        void CalcVertices();
        void CalcIndices();
        
    public:
        
        LSE_GLRectPrism(double x, double y, double z, double w, double h, double d);
};

#endif
