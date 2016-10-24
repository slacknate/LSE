#include "gl/object.h"
#include "gl/shaders.h"
#include "lse/globals.h"
#include "lse/exception.h"
using namespace LSE;

/*
Initialize our object to a position.
*/
GLObject::GLObject(double x, double y, double z) : PHObject(x, y, z) {
    
    program.AddShader(GetObjShaders(SHADER_VERT), SHADER_VERT);
    program.AddShader(GetObjShaders(SHADER_FRAG), SHADER_FRAG);
        
    program.BindAttrib(VERT_POSITION, "VERT_POSITION");
    program.BindAttrib(VERT_NORMAL, "VERT_NORMAL");
    program.BindAttrib(VERT_COLOR, "VERT_COLOR");
    program.BindAttrib(VERT_TEX_COORD, "VERT_TEX_COORD");
        
    if(!program.Finalize())
        throw EXCEPTION("OpenGL shader program failed to verify");
        
    program.BindUniform(MAT4, "VIEW_MAT", 1, GL_FALSE, &VIEW_MATRIX[0]);
    program.BindUniform(MAT4, "PROJ_MAT", 1, GL_FALSE, &PROJ_MATRIX[0]);
    program.BindUniform(MAT4, "ROT_MAT", 1, GL_FALSE, quat.get_matrix());
}

/*

*/
GLProgram* GLObject::GetProgram() {
    
    return &program;
}

/*

*/
void GLObject::Move(double dX, double dY, double dZ) {

    this->pos.z += dX;
    this->pos.y += dY;
    this->pos.z += dZ;
}

/*
Change this objects orientation.
*/
void GLObject::Transform(Quaternion& q) {
    
    quat = q * quat;
    quat.normalize();
}

/*
Draw our object on an OpenGL canvas.
Make sure to only attempt to draw the
object when we have valid coordinates.
*/
void GLObject::Render() {
    
    //  isolate this object from the rest 
    //glPushMatrix();
    
    //  bind to this objects shader program
    program.Bind();
    
    //  translate to our position -> replace, this shit is deprecated (AKA we need to do some matrix schtuff!)
    glTranslated(this->pos.x, this->pos.y, this->pos.z);
    
    Quaternion q(0.0, 0.0, 0.1, 10.0*cos(PI/180.0));
    q.normalize();
    Transform(q);
    
    //  draw our object
    Draw();
    
    //  unbind the shader
    program.Unbind();
    
    //  go back to the last frame of reference 
    //glPopMatrix();
}
