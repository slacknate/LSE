#include "util/math/vector.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize a "zero" vector.
*/
Vector::Vector() {
    
    this->i = 0.0;
    this->j = 0.0;
    this->k = 0.0;
}

/*
Initialize our vector.
*/
Vector::Vector(double x, double y, double z) {
    
    this->i = x;
    this->j = y;
    this->k = z;
}

/*
Get the X component.
*/
double Vector::I() {
    
    return this->i;
}

/*
Get the Y component.
*/
double Vector::J() {
    
    return this->j;
}

/*
Get the Z component.
*/
double Vector::K() {
    
    return this->k;
}

/*
Get the length of the vector.
*/
double Vector::Length() {
    
    return sqrt(pow(this->i, 2.0) + pow(this->j, 2.0) + pow(this->k, 2.0));
}

/*
Make this vector a unit vector in its current direction.
*/
void Vector::Normalize() {
    
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
void Vector::Orthagonalize(Vector& v) {
    
    
}

/*
Vector scalar multiplication.
*/
Vector Vector::operator*(const double& scalar) {
    
    return Vector(this->i * scalar, this->j * scalar, this->k * scalar);
}

/*
Vector scalar division.
*/
Vector Vector::operator/(const double& scalar) {
    
    return Vector(this->i / scalar, this->j / scalar, this->k / scalar);
}

/*
Vector addition.
*/
Vector Vector::operator+(const Vector& other) {
    
    return Vector(this->i + other.i, this->j + other.j, this->k + other.k);
}

/*
Vector subtraction.
*/
Vector Vector::operator-(const Vector& other) {
    
    return Vector(this->i - other.i, this->j - other.j, this->k - other.k);
}

/*
Get the angle between two vector, in radians.
*/
double Vector::operator^(Vector& other) {
    
    return acos((float)((*this * other)/(this->Length() * other.Length())));
}

/*
Get the dot product of two vector.
*/
double Vector::operator*(const Vector& other) {
    
    return (this->i * other.i) + (this->j * other.j) + (this->k * other.k);
}

/*
Get the cross product of two vector.
*/
Vector Vector::operator%(const Vector& other) {
    
    double x = (this->j * other.k) - (this->k * other.j);
    double y = (this->k * other.i) - (this->i * other.k);
    double z = (this->i * other.j) - (this->j * other.i);
    
    return Vector(x, y, z);
}

bool Vector::operator==(const Vector& other) {
    
    return (this->i == other.i && this->j == other.j && this->k == other.k);
}

bool Vector::operator!=(const Vector& other) {
    
    return (this->i != other.i || this->j != other.j || this->k != other.k);
}
