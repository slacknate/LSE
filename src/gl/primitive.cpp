#include <new>
#include <cstdio>
#include "lse/globals.h"
#include "util/memory.h"
#include "gl/primitive.h"
using namespace LSE;

/*
Initialize a primitive. We have a positon, but no
vertices by default.
*/
GLPrimitive::GLPrimitive(unsigned int nv, unsigned int ne, float x, float y, float z) :
        GLObject(x, y, z), numVertices(nv), numElements(ne) {

    vertices = LSE::MALLOC(float, 3u*numVertices);
    normals = LSE::MALLOC(float, 3u*numVertices);
    colors = LSE::MALLOC(float, 4u*numVertices);
    tex_coords = LSE::MALLOC(int, 2u*numVertices);
    indices = LSE::MALLOC(int, 3u*numElements);
}

/*
Free all allocated memory.
*/
GLPrimitive::~GLPrimitive() {

    delete[] vertices;
    delete[] normals;
    delete[] colors;
    delete[] tex_coords;
    delete[] indices;
}

/*
 */
void GLPrimitive::create() {

    this->calc_colors();
    this->calc_vertices();
    this->calc_indices();
    this->calc_normals();
    this->calc_tex_coords();
}

/*
Test if two points are on the same side of a line.

Reference:
    http://www.blackpawn.com/texts/pointinpoly/default.html
*/
bool GLPrimitive::SameSide(Vertex &lp1, Vertex &lp2, Vertex &ref, Vertex &test) {
    
    Vector cp1 = Vector(lp1.x - lp2.x, lp1.y - lp2.y, lp1.z - lp2.z) % Vector(lp1.x - ref.x, lp1.y - ref.y, lp1.z - ref.z);
    Vector cp2 = Vector(lp1.x - lp2.x, lp1.y - lp2.y, lp1.z - lp2.z) % Vector(lp1.x - test.x, lp1.y - test.y, lp1.z - test.z);
    
    return (cp1 ^ cp2) == 0;
}
        

/*
fix me -> doesnt work if on the exact edge of the triangle

Reference:
    http://www.blackpawn.com/texts/pointinpoly/default.html    
*/
bool GLPrimitive::InTriangle(Vertex &vertA, Vertex &vertB, Vertex &vertC, Vertex &ref, float x, float y, float z) {
    
    Vertex v(x, y, z);

    return SameSide(vertA, vertB, ref, v) && SameSide(vertA, vertC, ref, v) && SameSide(vertB, vertC, ref, v);
}

/*
Draw our primitive as a triangle strip.
fix me -> add textures
use shaders... lighting/color/textures wont work without it
gldrawelements documentation doesnt specify where the vertex data is stored. this may cause hardware incompatibility
*/
void GLPrimitive::Draw() {

    glEnableVertexAttribArray(VERT_POSITION);
    glEnableVertexAttribArray(VERT_NORMAL);
    glEnableVertexAttribArray(VERT_COLOR);
    glEnableVertexAttribArray(VERT_TEX_COORD);

    glVertexAttribPointer(VERT_POSITION, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(VERT_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glVertexAttribPointer(VERT_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glVertexAttribPointer(VERT_TEX_COORD, 2, GL_INT, GL_FALSE, 0, tex_coords);

    glDrawElements(GL_TRIANGLES, 3*numElements, GL_UNSIGNED_INT, indices);

    glDisableVertexAttribArray(VERT_TEX_COORD);
    glDisableVertexAttribArray(VERT_COLOR);
    glDisableVertexAttribArray(VERT_NORMAL);
    glDisableVertexAttribArray(VERT_POSITION);
}

/*
Draw the normals to all surfaces of this object
fix me -> normals blink when rotating surface (problem is in InTriangle())
*/
void GLPrimitive::RenderNormals() {

    // loop through each strip
    for(int i = 0; i < numElements; ++i) {

        // calculate vertex array indices
        int vertOne = indices[(3*i)];
        int vertTwo = indices[(3*i)+1];
        int vertThree = indices[(3*i)+2];

        // get each vertex for this triangle
        Vertex vert1(vertices[(3*vertOne)], vertices[(3*vertOne)+1], vertices[(3*vertOne)+2]);
        Vertex vert2(vertices[(3*vertTwo)], vertices[(3*vertTwo)+1], vertices[(3*vertTwo)+2]);
        Vertex vert3(vertices[(3*vertThree)], vertices[(3*vertThree)+1], vertices[(3*vertThree)+2]);

        // get the midpoint between vertex 1 and 2
        Vertex mid12((vert1.x + vert2.x)/2, (vert1.y + vert2.y)/2, (vert1.z + vert2.z)/2);

        // create a vector from the calculated midpoint to vertex 3
        Vector v(vert3.x - mid12.x, vert3.y - mid12.y, vert3.z - mid12.z);
        // the produced vector scaled down by three gives us the barycenter from the midpoint
        v = v / 3;

        // calculate the barycenter of the triangle
        Vertex barycenter(mid12.x + v.i(), mid12.y + v.j(), mid12.z + v.k());

        // get normal of the current surface
        Vector normal = GetNormalAt(barycenter.x, barycenter.y, barycenter.z);

        // isolate each normal from the others
        glPushMatrix();

        // translate the normal to the barycenter of the triangle
        glTranslatef(barycenter.x, barycenter.y, barycenter.z);

        // draw the normal, starting from our object position
        glColor4f(1.0, 0.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3f(this->pos.x, this->pos.y, this->pos.x);
            glVertex3f(this->pos.x + normal.i(), this->pos.y + normal.j(), this->pos.z + normal.k());
        glEnd();
        glColor4f(1.0, 1.0, 1.0, 1.0);

        // go to the previous frame of reference
        glPopMatrix();
    }
}

/*
Test if the given point is a collision point of this object.
*/
bool GLPrimitive::Hit(float x, float y, float z) {

    return (GetNormalAt(x, y, z) != Vector());
}

/*
If the given point falls on a surface of this object,
return the normal of that surface, otherwise return a
zero vector.
*/
Vector GLPrimitive::GetNormalAt(float x, float y, float z) {

    // loop through each strip
    for(int i = 0; i < numElements; ++i) {

        // calculate vertex array indices
        int vertOne = indices[(3*i)];
        int vertTwo = indices[(3*i)+1];
        int vertThree = indices[(3*i)+2];

        // get each vertex for this triangle
        Vertex vert1(vertices[(3*vertOne)], vertices[(3*vertOne)+1], vertices[(3*vertOne)+2]);
        Vertex vert2(vertices[(3*vertTwo)], vertices[(3*vertTwo)+1], vertices[(3*vertTwo)+2]);
        Vertex vert3(vertices[(3*vertThree)], vertices[(3*vertThree)+1], vertices[(3*vertThree)+2]);

        // get the midpoint between vertex 1 and 2
        Vertex mid12((vert1.x + vert2.x)/2, (vert1.y + vert2.y)/2, (vert1.z + vert2.z)/2);

        // create a vector from the calculated midpoint to vertex 3
        Vector v(vert3.x - mid12.x, vert3.y - mid12.y, vert3.z - mid12.z);
        // the produced vector scaled down by three gives us the barycenter from the midpoint
        v = v / 3;

        // calculate the barycenter of the triangle
        Vertex barycenter(mid12.x + v.i(), mid12.y + v.j(), mid12.z + v.k());

        // test if the given point falls in this triangle
        if(InTriangle(vert1, vert2, vert3, barycenter, x, y, z))
            return Vector(normals[(3*vertOne)], normals[(3*vertOne)+1], normals[(3*vertOne)+2]);
    }

    // given point was not on any surface of this primitive
    return Vector();
}
