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
        
        double i, j, k, s; // Quaternion components
        double matrix[16]; // Quaternion represented as a rotation matrix
        
    public:
        
        Quaternion();
        Quaternion(double x, double y, double z, double n);
        
        double I();
        double J();
        double K();
        double S();
        double Norm();
        Quaternion Conjugate();
        void Normalize();
        void UpdateMatrix();
        double* GetMatrix();
        
        Quaternion operator*(const double& scalar);
        Quaternion operator/(const double& scalar);
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
