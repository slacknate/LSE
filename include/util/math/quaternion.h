#ifndef LSE_QUATERNION_H
#define LSE_QUATERNION_H

#include <cmath>
#include "util/math/vector.h"
#include "gl/vertex.h"

namespace LSE {

/*
Quaternion class used to represent gimbal-lock free
rotation in 3D space.
*/
class Quaternion {
    
    private:
        
        float x, y, z, w; // Quaternion components
        float matrix[16]; // Quaternion represented as a rotation matrix
        
    public:
        
        Quaternion();
        Quaternion(float x, float y, float z, float w);
        
        float i();
        float j();
        float k();
        float s();
        float norm();
        Quaternion conjugate();
        void normalize();
        void update_matrix();
        float* get_matrix();
        
        Quaternion operator*(const float& scalar);
        Quaternion operator/(const float& scalar);
        Vertex operator*(Vertex& v);
        Vector operator*(Vector& v);
        Quaternion operator+(const Quaternion& other);
        Quaternion operator-(const Quaternion& other);
        Quaternion operator*(const Quaternion& other);
        Quaternion operator/(const Quaternion& other);
        bool operator==(const Quaternion& other);
        bool operator!=(const Quaternion& other);
};

}

#endif
