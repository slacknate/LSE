#include "gl/object.h"
#include "gl/shaders.h"

/*
Initialize our object to a position.
*/
LSE_GLObject::LSE_GLObject(double x, double y, double z) : LSE_PHObject(x, y, z) {
    
    program.AddShader(LSE_GetObjShaders(SHADER_VERT), SHADER_VERT);
    program.AddShader(LSE_GetObjShaders(SHADER_FRAG), SHADER_FRAG);
        
    program.BindAttrib(VERT_POSITION, "VERT_POSITION");
    program.BindAttrib(VERT_NORMAL, "VERT_NORMAL");
    program.BindAttrib(VERT_COLOR, "VERT_COLOR");
    program.BindAttrib(VERT_TEX_COORD, "VERT_TEX_COORD");
        
    if(!program.Finalize())
        LSE_THROW(LSE_GL_PROG_FAIL)
        
    program.BindUniform(LSE_MAT4, "VIEW_MAT", 1, GL_FALSE, &LSE_VIEW_MATRIX[0]);
    program.BindUniform(LSE_MAT4, "PROJ_MAT", 1, GL_FALSE, &LSE_PROJ_MATRIX[0]);
    program.BindUniform(LSE_MAT4, "ROT_MAT", 1, GL_FALSE, quat.GetMatrix());
}

/*

*/
LSE_GLProgram* LSE_GLObject::GetProgram() {
    
    return &program;
}

/*

*/
void LSE_GLObject::Move(double dX, double dY, double dZ) {
    
    pX += dX;
    pY += dY;
    pZ += dZ;
}

/*
Change this objects orientation.
*/
void LSE_GLObject::Transform(LSE_Quaternion& q) {
    
    quat = q * quat;
    quat.Normalize();
}

/*
Draw our object on an OpenGL canvas.
Make sure to only attempt to draw the
object when we have valid coordinates.
*/
void LSE_GLObject::Render() {
    
    //  isolate this object from the rest 
    //glPushMatrix();
    
    //  bind to this objects shader program
    program.Bind();
    
    //  translate to our position -> replace, this shit is deprecated (AKA we need to do some matrix schtuff!)
    glTranslated(pX, pY, pZ);
    
    LSE_Quaternion q(0.0, 0.0, 0.1, 10.0*cos(PI/180.0));
    q.Normalize();
    Transform(q);
    
    //  draw our object
    Draw();
    
    //  unbind the shader
    program.Unbind();
    
    //  go back to the last frame of reference 
    //glPopMatrix();
}
