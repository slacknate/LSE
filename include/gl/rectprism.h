#ifndef LSE_GL_RECT_PRISM_H
#define LSE_GL_RECT_PRISM_H

#include "gl/primitive.h"

namespace LSE {

/*
Pre-defined rectangular prism primitive.
*/
class GLRectPrism : public GLPrimitive {
    
    private:
        
        static const int RECTP_VERT_COUNT = 24;
        static const int RECTP_ELEM_COUNT = 12;
    
    protected:
        
        double width, height, depth; // prism attributes
        
        void CalcVertices();
        void CalcIndices();
        
    public:
        
        GLRectPrism(double x, double y, double z, double w, double h, double d);
};

}

#endif
