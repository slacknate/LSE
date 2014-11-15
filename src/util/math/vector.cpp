#include "util/math/vector.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize a "zero" vector.
*/
Vector::Vector() {
    
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

/*
Initialize our vector.
*/
Vector::Vector(double x, double y, double z) {
    
    this->x = x;
    this->y = y;
    this->z = z;
}

/*
Get the X component.
*/
double Vector::i() {
    
    return this->x;
}

/*
Get the Y component.
*/
double Vector::j() {
    
    return this->y;
}

/*
Get the Z component.
*/
double Vector::k() {
    
    return this->z;
}

/*
Get the length of the vector.
*/
double Vector::length() {
    
    return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0));
}

/*
Make this vector a unit vector in its current direction.
*/
void Vector::normalize() {
    
    double size = this->length();
    if(size > 0) {
        
        this->x /= size;
        this->y /= size;
        this->z /= size;
    }
}

/*
FIXME: Words. Fancy words. That describe orthagonalization.
*/
void Vector::orthagonalize(Vector &v) {
    
    
}

/*
Vector scalar multiplication.
*/
Vector Vector::operator*(const double& scalar) {
    
    return Vector(this->x * scalar, this->y * scalar, this->z * scalar);
}

/*
Vector scalar division.
*/
Vector Vector::operator/(const double& scalar) {
    
    return Vector(this->x / scalar, this->y / scalar, this->z / scalar);
}

/*
Vector addition.
*/
Vector Vector::operator+(const Vector& other) {
    
    return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
}

/*
Vector subtraction.
*/
Vector Vector::operator-(const Vector& other) {
    
    return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
}

/*
Get the angle between two vector, in radians.
*/
double Vector::operator^(Vector& other) {
    
    return acos((float)((*this * other)/(this->length() * other.length())));
}

/*
Get the dot product of two vector.
*/
double Vector::operator*(const Vector& other) {
    
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

/*
Get the cross product of two vector.
*/
Vector Vector::operator%(const Vector& other) {
    
    double x = (this->y * other.z) - (this->z * other.y);
    double y = (this->z * other.x) - (this->x * other.z);
    double z = (this->x * other.y) - (this->y * other.x);
    
    return Vector(x, y, z);
}

bool Vector::operator==(const Vector& other) {
    
    return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool Vector::operator!=(const Vector& other) {
    
    return (this->x != other.x || this->y != other.y || this->z != other.z);
}
