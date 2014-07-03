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
class LSE_Quaternion {
    
    private:
        
        double i, j, k, s; // Quaternion components
        double matrix[16]; // Quaternion represented as a rotation matrix
        
    public:
        
        LSE_Quaternion();
        LSE_Quaternion(double x, double y, double z, double n);
        
        double I();
        double J();
        double K();
        double S();
        double Norm();
        LSE_Quaternion Conjugate();
        void Normalize();
        void UpdateMatrix();
        double* GetMatrix();
        
        LSE_Quaternion operator*(const double& scalar);
        LSE_Quaternion operator/(const double& scalar);
        LSE_Vertex operator*(LSE_Vertex& v);
        LSE_Vector operator*(LSE_Vector& v);
        LSE_Quaternion operator+(const LSE_Quaternion& other);
        LSE_Quaternion operator-(const LSE_Quaternion& other);
        LSE_Quaternion operator*(const LSE_Quaternion& other);
        LSE_Quaternion operator/(const LSE_Quaternion& other);
        bool operator==(const LSE_Quaternion& other);
        bool operator!=(const LSE_Quaternion& other);
};

}

#endif
