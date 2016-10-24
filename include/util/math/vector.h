#ifndef LSE_VECTOR_H
#define LSE_VECTOR_H

#include <cmath>

namespace LSE {

/*

*/
class Vector {
    
    private:
        
        float x, y, z; // Vector components
        
    public:
        
        Vector();
        Vector(float x, float y, float z);
        
        float i();
        float j();
        float k();
        float length();
        void normalize();
        void orthagonalize(Vector &v);
        
        Vector operator*(const float& scalar);
        Vector operator/(const float& scalar);
        Vector operator+(const Vector& other);
        Vector operator-(const Vector& other);
        float operator^(Vector& other);
        float operator*(const Vector& other);
        Vector operator%(const Vector& other);
        bool operator==(const Vector& other);
        bool operator!=(const Vector& other);
};

}

#endif
