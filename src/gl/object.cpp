#include <cstdio>
#include "gl/object.h"
/*
 * The following two headers are
 * auto-generated at build time.
 */
#include "gl/shaders/objfrag.h"
#include "gl/shaders/objvert.h"
#include "lse/globals.h"
#include "lse/exception.h"
#include "util/file.h"
using namespace LSE;

/*
 * Initialize our object to a position.
 * Also initialize our translation matrix
 * to match this position.
 * Note that the translation starts as an
 * identity matrix and then we insert our
 * translation data into it from there,
 */
GLObject::GLObject(float x, float y, float z) : PHObject(x, y, z), translation(4, true) {

    *this->translation[3][0] = this->pos.x;
    *this->translation[3][1] = this->pos.y;
    *this->translation[3][2] = this->pos.z;

    program.add_shader(OBJ_VERT_SHADER, SHADER_VERT);
    program.add_shader(OBJ_FRAG_SHADER, SHADER_FRAG);

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

/*

*/
void GLObject::translate(Vector& v) {

    this->pos.x += v.i();
    this->pos.y += v.j();
    this->pos.z += v.k();

    *this->translation[3][0] += v.i();
    *this->translation[3][1] += v.j();
    *this->translation[3][2] += v.k();
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
    program.uniform(MAT4, "TRANS_MAT", 1, GL_FALSE, this->translation.get_matrix());
    program.uniform(MAT4, "ROT_MAT", 1, GL_FALSE, this->rotation.get_matrix());

    //  draw our object
    Draw();
    
    //  unbind the shader
    program.unbind();
    
    //  go back to the last frame of reference 
    glPopMatrix();
}
