#include <cstdio>
#include "gl/object.h"
#include "gl/shaders.h"
#include "lse/globals.h"
#include "lse/exception.h"
#include "util/file.h"
using namespace LSE;

/*
Initialize our object to a position.
*/
GLObject::GLObject(float x, float y, float z) : PHObject(x, y, z) {

    this->init_translation_matrix();

    /*
     * FIXME: LOL hard-coded paths!
     */
    unsigned char *vert_shader = read_file("H:\\CLion\\LSE\\shaders\\ObjShaders.vert");
    unsigned char *frag_shader = read_file("H:\\CLion\\LSE\\shaders\\ObjShaders.frag");

    program.add_shader((const char *)vert_shader, SHADER_VERT);
    program.add_shader((const char *)frag_shader, SHADER_FRAG);

    delete[] vert_shader;
    delete[] frag_shader;

    program.bind_attrib(VERT_POSITION, "VERT_POSITION");
    program.bind_attrib(VERT_NORMAL, "VERT_NORMAL");
    program.bind_attrib(VERT_COLOR, "VERT_COLOR");
    program.bind_attrib(VERT_TEX_COORD, "VERT_TEX_COORD");

    if(!program.finalize())
        throw EXCEPTION("OpenGL shader program failed to verify");

    /*
     * FIXME: these need to be updated sometimes...
     */
    program.uniform(MAT4, "VIEW_MAT", 1, GL_FALSE, &VIEW_MATRIX[0]);
    program.uniform(MAT4, "PROJ_MAT", 1, GL_FALSE, &PROJ_MATRIX[0]);
}

/*

*/
GLProgram* GLObject::GetProgram() {
    
    return &program;
}

void GLObject::init_translation_matrix() {

    this->translation[0] = 1.0;
    this->translation[1] = 0.0;
    this->translation[2] = 0.0;
    this->translation[3] = 0.0;
    this->translation[4] = 0.0;
    this->translation[5] = 1.0;
    this->translation[6] = 0.0;
    this->translation[7] = 0.0;
    this->translation[8] = 0.0;
    this->translation[9] = 0.0;
    this->translation[10] = 1.0;
    this->translation[11] = 0.0;
    this->translation[12] = this->pos.x;
    this->translation[13] = this->pos.y;
    this->translation[14] = this->pos.z;
    this->translation[15] = 1.0;
}

/*

*/
void GLObject::translate(Vector& v) {

    this->pos.x += v.i();
    this->pos.y += v.j();
    this->pos.z += v.k();

    this->translation[12] += v.i();
    this->translation[13] += v.j();
    this->translation[14] += v.k();
}

/*
Change this objects orientation.
*/
void GLObject::rotate(Quaternion& q) {

    this->rotation = this->rotation * q;
    this->rotation.normalize();
}

/*
Draw our object on an OpenGL canvas.
Make sure to only attempt to draw the
object when we have valid coordinates.
*/
void GLObject::Render() {
    
    //  isolate this object from the rest 
    glPushMatrix();
    
    //  bind to this objects shader program
    program.bind();

    //  update our transformation matrices
    program.uniform(MAT4, "TRANS_MAT", 1, GL_FALSE, this->translation);
    program.uniform(MAT4, "ROT_MAT", 1, GL_FALSE, this->rotation.get_matrix());

    //  draw our object
    Draw();
    
    //  unbind the shader
    program.unbind();
    
    //  go back to the last frame of reference 
    glPopMatrix();
}
