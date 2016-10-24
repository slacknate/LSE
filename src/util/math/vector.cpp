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
Vector::Vector(float x, float y, float z) {
    
    this->x = x;
    this->y = y;
    this->z = z;
}

/*
Get the X component.
*/
float Vector::i() {
    
    return this->x;
}

/*
Get the Y component.
*/
float Vector::j() {
    
    return this->y;
}

/*
Get the Z component.
*/
float Vector::k() {
    
    return this->z;
}

/*
Get the length of the vector.
*/
float Vector::length() {
    
    return (float)sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0));
}

/*
Make this vector a unit vector in its current direction.
*/
void Vector::normalize() {
    
    float size = this->length();
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
Vector Vector::operator*(const float& scalar) {
    
    return Vector(this->x * scalar, this->y * scalar, this->z * scalar);
}

/*
Vector scalar division.
*/
Vector Vector::operator/(const float& scalar) {
    
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
float Vector::operator^(Vector& other) {
    
    return acos((float)((*this * other)/(this->length() * other.length())));
}

/*
Get the dot product of two vector.
*/
float Vector::operator*(const Vector& other) {
    
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

/*
Get the cross product of two vector.
*/
Vector Vector::operator%(const Vector& other) {
    
    float x = (this->y * other.z) - (this->z * other.y);
    float y = (this->z * other.x) - (this->x * other.z);
    float z = (this->x * other.y) - (this->y * other.x);
    
    return Vector(x, y, z);
}

bool Vector::operator==(const Vector& other) {
    
    return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool Vector::operator!=(const Vector& other) {
    
    return (this->x != other.x || this->y != other.y || this->z != other.z);
}
