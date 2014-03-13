#include "util/math/vector.h"
#include "lse/defs.h"

/*
Initialize a "zero" vector.
*/
LSE_Vector::LSE_Vector() {
    
    i = 0.0;
    j = 0.0;
    k = 0.0;
}

/*
Initialize our vector.
*/
LSE_Vector::LSE_Vector(double x, double y, double z) {
    
    i = x;
    j = y;
    k = z;
}

/*
Define the destructor for potential future use.
As for now there is no memory in need of
deallocation.
*/
LSE_Vector::~LSE_Vector() {
    
    
}

/*
Get the X component.
*/
double LSE_Vector::I() {
    
    return i;
}

/*
Get the Y component.
*/
double LSE_Vector::J() {
    
    return j;
}

/*
Get the Z component.
*/
double LSE_Vector::K() {
    
    return k;
}

/*
Get the length of the vector.
*/
double LSE_Vector::Length() {
    
    return sqrt(pow(i, 2.0) + pow(j, 2.0) + pow(k, 2.0));
}

/*
Make this vector a unit vector in its current direction.
*/
void LSE_Vector::Normalize() {
    
    double size = Length();
    if(size > 0) {
        
        i /= size;
        j /= size;
        k /= size;
    }
}

/*
Words. Fancy words. That describe orthagonalization. fix me
*/
void LSE_Vector::Orthagonalize(LSE_Vector& v) {
    
    
}

/*
Vector scalar multiplication.
*/
LSE_Vector LSE_Vector::operator*(const double& scalar) {
    
    return LSE_Vector(this->i * scalar, this->j * scalar, this->k * scalar);
}

/*
Vector scalar division.
*/
LSE_Vector LSE_Vector::operator/(const double& scalar) {
    
    return LSE_Vector(this->i / scalar, this->j / scalar, this->k / scalar);
}

/*
Vector addition.
*/
LSE_Vector LSE_Vector::operator+(const LSE_Vector& other) {
    
    return LSE_Vector(this->i + other.i, this->j + other.j, this->k + other.k);
}

/*
Vector subtraction.
*/
LSE_Vector LSE_Vector::operator-(const LSE_Vector& other) {
    
    return LSE_Vector(this->i - other.i, this->j - other.j, this->k - other.k);
}

/*
Get the angle between two vector, in radians.
*/
double LSE_Vector::operator^(LSE_Vector& other) {
    
    return acos((float)((*this * other)/(this->Length() * other.Length())));
}

/*
Get the dot product of two vector.
*/
double LSE_Vector::operator*(const LSE_Vector& other) {
    
    return (this->i * other.i) + (this->j * other.j) + (this->k * other.k);
}

/*
Get the cross product of two vector.
*/
LSE_Vector LSE_Vector::operator%(const LSE_Vector& other) {
    
    double x, y, z;
    
    x = (this->j * other.k) - (this->k * other.j);
    y = (this->k * other.i) - (this->i * other.k);
    z = (this->i * other.j) - (this->j * other.i);
    
    return LSE_Vector(x, y, z);
}

bool LSE_Vector::operator==(const LSE_Vector& other) {
    
    return (this->i == other.i && this->j == other.j && this->k == other.k);
}

bool LSE_Vector::operator!=(const LSE_Vector& other) {
    
    return (this->i != other.i || this->j != other.j || this->k != other.k);
}
