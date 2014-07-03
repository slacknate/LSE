#include <new>
#include <cstdio>
#include "gl/primitive.h"
using namespace LSE;

/*
Initialize a primitive. We have a positon, but no
vertices by default.
*/
LSE_GLPrimitive::LSE_GLPrimitive(double x, double y, double z) : LSE_GLObject(x, y, z) {
    
    vertices = NULL;
    normals = NULL;
    colors = NULL;
    texCoords = NULL;
    indices = NULL;
}

/*
Allocate all memory needed by this primitive.
*/
void LSE_GLPrimitive::MemAllocate(int nv, int ne) {
    
    numVertices = nv;
    numElements = ne;
    
    vertices = new (std::nothrow) double [3*numVertices];
    normals = new (std::nothrow) double [3*numVertices];
    colors = new (std::nothrow) double [4*numVertices];
    texCoords = new (std::nothrow) int [2*numVertices];
    indices = new (std::nothrow) int [3*numElements];
    
    if(vertices && normals && colors && texCoords && indices) {
        
        initialized = true;
        
        CalcColors();
        CalcVertices();
        CalcIndices();
        //CalcNormals(); // fix me -> causing problems
        CalcTexCoords();
    }
    else {
        
        LOG(LOG_LEVEL_ERROR, "Failed to allocate memory for vertex, normal, color, texture, or index arrays.");
        initialized = false;
    }
}

/*
Free all allocated memory.
*/
LSE_GLPrimitive::~LSE_GLPrimitive() {
    
    if(vertices)
        delete[] vertices;
    
    if(normals)
        delete[] normals;
    
    if(colors)
        delete[] colors;
    
    if(texCoords)
        delete[] texCoords;
        
    if(indices)
        delete[] indices;
}

/*
Test if two points are on the same side of a line.

Reference:
    http://www.blackpawn.com/texts/pointinpoly/default.html
*/
bool LSE_GLPrimitive::SameSide(LSE_Vertex &lp1, LSE_Vertex &lp2, LSE_Vertex &ref, LSE_Vertex &test) {
    
    LSE_Vector cp1 = LSE_Vector(lp1.x - lp2.x, lp1.y - lp2.y, lp1.z - lp2.z) % LSE_Vector(lp1.x - ref.x, lp1.y - ref.y, lp1.z - ref.z);
    LSE_Vector cp2 = LSE_Vector(lp1.x - lp2.x, lp1.y - lp2.y, lp1.z - lp2.z) % LSE_Vector(lp1.x - test.x, lp1.y - test.y, lp1.z - test.z);
    
    if((cp1 ^ cp2) == 0)
        return true;
    else
        return false;
}
        

/*
fix me -> doesnt work if on the exact edge of the triangle

Reference:
    http://www.blackpawn.com/texts/pointinpoly/default.html    
*/
bool LSE_GLPrimitive::InTriangle(LSE_Vertex &vertA, LSE_Vertex &vertB, LSE_Vertex &vertC, LSE_Vertex &ref, double x, double y, double z) {
    
    LSE_Vertex v(x, y, z);
    if(SameSide(vertA, vertB, ref, v) && SameSide(vertA, vertC, ref, v) && SameSide(vertB, vertC, ref, v))
        return true;
    else
        return false;
}

/*
Calculate the normal to every surface
of this primitive.
fix me -> this is causing some serious errors....
*/
void LSE_GLPrimitive::CalcNormals() {
    
    if(initialized) {
        
        // loop through each strip
        for(int i = 0; i < numElements; ++i) {
            
            // calculate vertex array indices
            int vertOne = indices[(3*i)];
            int vertTwo = indices[(3*i)+1];
            int vertThree = indices[(3*i)+2];
        
            // get each vertex for this triangle
            LSE_Vertex vert1(vertices[(3*vertOne)], vertices[(3*vertOne)+1], vertices[(3*vertOne)+2]);
            LSE_Vertex vert2(vertices[(3*vertTwo)], vertices[(3*vertTwo)+1], vertices[(3*vertTwo)+2]);
            LSE_Vertex vert3(vertices[(3*vertThree)], vertices[(3*vertThree)+1], vertices[(3*vertThree)+2]);
                    
            // create two vectors using the vertex coordinates
            LSE_Vector vec1(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
            LSE_Vector vec2(vert2.x - vert3.x, vert2.y - vert3.y, vert2.z - vert3.z);
                                
            // calculate the cross product, and normalize it
            LSE_Vector normal = vec1 % vec2;
            normal.Normalize();
            
            // store our result in the normal array (note: need a normal per vertex)
            normals[(3*vertOne)] = normal.I();
            normals[(3*vertOne)+1] = normal.J();
            normals[(3*vertOne)+2] = normal.K();
            
            normals[(3*vertTwo)+3] = normal.I();
            normals[(3*vertTwo)+4] = normal.J();
            normals[(3*vertTwo)+5] = normal.K();
            
            normals[(3*vertThree)+6] = normal.I();
            normals[(3*vertThree)+7] = normal.J();
            normals[(3*vertThree)+8] = normal.K();
        }
    }
}

/*
Initialize colors of all vertices to white.
*/
void LSE_GLPrimitive::CalcColors() {
    
    if(initialized) {
        
        for(int i = 0; i < 4*numVertices; ++i)
            colors[i] = 1.0;
    }
}

/*
Change the orientation of our object,
by an offset represented by the Quaternion q.
fix me -> offload this to the graphics card?
*/
/*void LSE_GLPrimitive::Transform(LSE_Quaternion& q) {
    
    if(initialized) {
        
        // loop through each strip
        for(int i = 0; i < numVertices; ++i) {
            
            // get the current vertex
            LSE_Vertex vert(vertices[(3*i)], vertices[(3*i)+1], vertices[(3*i)+2]);
            
            // transform the vertex
            vert = q * vert;
            
            // store the vertex back to memory
            vertices[(3*i)] = vert.x;
            vertices[(3*i)+1] = vert.y;
            vertices[(3*i)+2] = vert.z;
        }
        
        // loop through each strip
        for(int i = 0; i < numVertices; ++i) {
            
            // calculate vertex array indices
            // get the current normal 
            LSE_Vector normal(normals[(3*i)], normals[(3*i)+1], normals[(3*i)+2]);
            
            // transform the normal
            normal = q * normal;
            
            // store the normal back to memory
            normals[(3*i)]   = normal.I();
            normals[(3*i)+1] = normal.J();
            normals[(3*i)+2] = normal.K();
        }
    }
}*/

/*
Draw our primitive as a triangle strip.
fix me -> add textures
use shaders... lighting/color/textures wont work without it
gldrawelements documentation doesnt specify where the vertex data is stored. this may cause hardware incompatibility
*/
void LSE_GLPrimitive::Draw() {
    
    if(initialized) {
        
        glEnableVertexAttribArray(VERT_POSITION);
        glEnableVertexAttribArray(VERT_NORMAL);
        glEnableVertexAttribArray(VERT_COLOR);
        glEnableVertexAttribArray(VERT_TEX_COORD);
        
        glVertexAttribPointer(VERT_POSITION, 3, GL_DOUBLE, GL_FALSE, 0, vertices);
        glVertexAttribPointer(VERT_NORMAL, 3, GL_DOUBLE, GL_FALSE, 0, normals);
        glVertexAttribPointer(VERT_COLOR, 4, GL_DOUBLE, GL_FALSE, 0, colors);
        glVertexAttribPointer(VERT_TEX_COORD, 2, GL_INT, GL_FALSE, 0, texCoords);
        
        glDrawElements(GL_TRIANGLES, 3*numElements, GL_UNSIGNED_INT, indices);
        
        glDisableVertexAttribArray(VERT_TEX_COORD);
        glDisableVertexAttribArray(VERT_COLOR);
        glDisableVertexAttribArray(VERT_NORMAL);
        glDisableVertexAttribArray(VERT_POSITION);
    }
}

/*
Draw the normals to all surfaces of this object
fix me -> normals blink when rotating surface (problem is in InTriangle())
*/
void LSE_GLPrimitive::RenderNormals() {
    
    if(initialized) {
        
        // loop through each strip
        for(int i = 0; i < numElements; ++i) {
            
            // calculate vertex array indices
            int vertOne = indices[(3*i)];
            int vertTwo = indices[(3*i)+1];
            int vertThree = indices[(3*i)+2];
        
            // get each vertex for this triangle
            LSE_Vertex vert1(vertices[(3*vertOne)], vertices[(3*vertOne)+1], vertices[(3*vertOne)+2]);
            LSE_Vertex vert2(vertices[(3*vertTwo)], vertices[(3*vertTwo)+1], vertices[(3*vertTwo)+2]);
            LSE_Vertex vert3(vertices[(3*vertThree)], vertices[(3*vertThree)+1], vertices[(3*vertThree)+2]);
            
            // get the midpoint between vertex 1 and 2
            LSE_Vertex mid12((vert1.x + vert2.x)/2, (vert1.y + vert2.y)/2, (vert1.z + vert2.z)/2);
            
            // create a vector from the calculated midpoint to vertex 3
            LSE_Vector v(vert3.x - mid12.x, vert3.y - mid12.y, vert3.z - mid12.z);
            // the produced vector scaled down by three gives us the barycenter from the midpoint
            v = v / 3;
                    
            // calculate the barycenter of the triangle
            LSE_Vertex barycenter(mid12.x + v.I(), mid12.y + v.J(), mid12.z + v.K());
            
            // get normal of the current surface
            LSE_Vector normal = GetNormalAt(barycenter.x, barycenter.y, barycenter.z);
            
            // isolate each normal from the others
            glPushMatrix();
            
            // translate the normal to the barycenter of the triagle
            glTranslatef(barycenter.x, barycenter.y, barycenter.z);
            
            // draw the normal, starting from our object position
            glColor4f(1.0, 0.0, 0.0, 0.0);
            glBegin(GL_LINES);
                glVertex3f(pX, pY, pZ);
                glVertex3f(pX + normal.I(), pY + normal.J(), pZ + normal.K());
            glEnd();
            glColor4f(1.0, 1.0, 1.0, 1.0);
            
            // go to the previous frame of reference
            glPopMatrix();
        }
    }  
}    

/*
Test if the given point is a collision point of this object.
*/
bool LSE_GLPrimitive::Hit(double x, double y, double z) {
    
    return (GetNormalAt(x, y, z) != LSE_Vector());
}

/*
If the given point falls on a surface of this object,
return the normal of that surface, otherwise return a
zero vector.
*/
LSE_Vector LSE_GLPrimitive::GetNormalAt(double x, double y, double z) {
    
    if(initialized) {
        
        // loop through each strip
        for(int i = 0; i < numElements; ++i) {
            
            // calculate vertex array indices
            int vertOne = indices[(3*i)];
            int vertTwo = indices[(3*i)+1];
            int vertThree = indices[(3*i)+2];
            
            // get each vertex for this triangle
            LSE_Vertex vert1(vertices[(3*vertOne)], vertices[(3*vertOne)+1], vertices[(3*vertOne)+2]);
            LSE_Vertex vert2(vertices[(3*vertTwo)], vertices[(3*vertTwo)+1], vertices[(3*vertTwo)+2]);
            LSE_Vertex vert3(vertices[(3*vertThree)], vertices[(3*vertThree)+1], vertices[(3*vertThree)+2]);
            
            // get the midpoint between vertex 1 and 2
            LSE_Vertex mid12((vert1.x + vert2.x)/2, (vert1.y + vert2.y)/2, (vert1.z + vert2.z)/2);
            
            // create a vector from the calculated midpoint to vertex 3
            LSE_Vector v(vert3.x - mid12.x, vert3.y - mid12.y, vert3.z - mid12.z);
            // the produced vector scaled down by three gives us the barycenter from the midpoint
            v = v / 3;
            
            // calculate the barycenter of the triangle
            LSE_Vertex barycenter(mid12.x + v.I(), mid12.y + v.J(), mid12.z + v.K());
            
            // test if the given point falls in this triangle
            if(InTriangle(vert1, vert2, vert3, barycenter, x, y, z))
                return LSE_Vector(normals[(3*vertOne)], normals[(3*vertOne)+1], normals[(3*vertOne)+2]);
        }
    }
    
    // given point was not on any surface of this primitive
    return LSE_Vector();
}
