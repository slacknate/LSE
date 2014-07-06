#ifndef LSE_VECTOR_H
#define LSE_VECTOR_H

#include <cmath>

namespace LSE {

/*

*/
class Vector {
    
    private:
        
        double i, j, k; // Vector components
        
    public:
        
        Vector();
        Vector(double x, double y, double z);
        
        double I();
        double J();
        double K();
        double Length();
        void Normalize();
        void Orthagonalize(Vector& v);
        
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
