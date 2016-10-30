#ifndef LSE_GL_RECT_PRISM_H
#define LSE_GL_RECT_PRISM_H

#include "gl/primitive.h"

namespace LSE {

/*
Pre-defined rectangular prism primitive.
*/
class GLRectPrism : public GLPrimitive {
    
    private:
        
        static const int RECTP_VERT_COUNT = 8;
        static const int RECTP_NORM_COUNT = 4;
        static const int RECTP_ELEM_COUNT = 12;

        Vector get_normal();
    
    protected:
        
        float width, height, depth; // prism attributes
        
        void calc_vertices();
        void calc_normals();
        // FIXME
        void calc_tex_coords() {}

    public:
        
        GLRectPrism(float x, float y, float z, float w, float h, float d);
};

}

#endif
