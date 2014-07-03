#include "util/math/vector.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize a "zero" vector.
*/
LSE_Vector::LSE_Vector() {
    
    this->i = 0.0;
    this->j = 0.0;
    this->k = 0.0;
}

/*
Initialize our vector.
*/
LSE_Vector::LSE_Vector(double x, double y, double z) {
    
    this->i = x;
    this->j = y;
    this->k = z;
}

/*
Get the X component.
*/
double LSE_Vector::I() {
    
    return this->i;
}

/*
Get the Y component.
*/
double LSE_Vector::J() {
    
    return this->j;
}

/*
Get the Z component.
*/
double LSE_Vector::K() {
    
    return this->k;
}

/*
Get the length of the vector.
*/
double LSE_Vector::Length() {
    
    return sqrt(pow(this->i, 2.0) + pow(this->j, 2.0) + pow(this->k, 2.0));
}

/*
Make this vector a unit vector in its current direction.
*/
void LSE_Vector::Normalize() {
    
    double size = this->Length();
    if(size > 0) {
        
        this->i /= size;
        this->j /= size;
        this->k /= size;
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
    
    double x = (this->j * other.k) - (this->k * other.j);
    double y = (this->k * other.i) - (this->i * other.k);
    double z = (this->i * other.j) - (this->j * other.i);
    
    return LSE_Vector(x, y, z);
}

bool LSE_Vector::operator==(const LSE_Vector& other) {
    
    return (this->i == other.i && this->j == other.j && this->k == other.k);
}

bool LSE_Vector::operator!=(const LSE_Vector& other) {
    
    return (this->i != other.i || this->j != other.j || this->k != other.k);
}
