#ifndef LSE_VECTOR_H
#define LSE_VECTOR_H

#include <cmath>

namespace LSE {

/*

*/
class Vector {
    
    private:
        
        double x, y, z; // Vector components
        
    public:
        
        Vector();
        Vector(double x, double y, double z);
        
        double i();
        double j();
        double k();
        double length();
        void normalize();
        void orthagonalize(Vector &v);
        
        Vector operator*(const double& scalar);
        Vector operator/(const double& scalar);
        Vector operator+(const Vector& other);
        Vector operator-(const Vector& other);
        double operator^(Vector& other);
        double operator*(const Vector& other);
        Vector operator%(const Vector& other);
        bool operator==(const Vector& other);
        bool operator!=(const Vector& other);
};

}

#endif
