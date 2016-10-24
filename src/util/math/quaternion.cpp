#include "util/math/quaternion.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize our quaternion by default to a identity orientation.
*/
Quaternion::Quaternion() {

    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1.0;

    this->update_matrix();
}

/*
Initialize our quaternion given all four components.
*/
Quaternion::Quaternion(float x, float y, float z, float w) {

    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;

    this->update_matrix();
}

/*
Get the X component.
*/
float Quaternion::i() {
    
    return this->x;
}

/*
Get the Y component.
*/
float Quaternion::j() {
    
    return this->y;
}

/*
Get the Z component.
*/
float Quaternion::k() {
    
    return this->z;
}

/*
Get the scalar component.
*/
float Quaternion::s() {
    
    return this->w;
}

/*
Get the length of the quaternion.
*/
float Quaternion::norm() {
    
    return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0) + pow(this->w, 2.0));
}

/*
Return the conjugate of this quaternion.
*/
Quaternion Quaternion::conjugate() {
    
    return Quaternion(-this->x, -this->y, -this->z, this->w);
}

/*
Make this quaternion a unit quaternion in its current direction.
*/
void Quaternion::normalize() {
    
    float size = this->norm();
    
    if(size > 0) {

        this->x /= size;
        this->y /= size;
        this->z /= size;
        this->w /= size;
    }
}

/*
Generates a rotation matrix from this quaternion.
This matrix can be used natively with OpenGL,
but must be transposed to be used with Direct3D.

Reference:
    www.cprogramming.com/tutorial/3d/Quaternions.html
    http://www.flipcode.com/documents/matrfaq.html#Q54

0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15
*/
void Quaternion::update_matrix() {
    
    float xx = this->x * this->x;
    float xy = this->x * this->y;
    float xz = this->x * this->z;
    float xw = this->x * this->w;

    float yy = this->y * this->y;
    float yz = this->y * this->z;
    float yw = this->y * this->w;

    float zz = this->z * this->z;
    float zw = this->z * this->w;

    this->matrix[0]  = 1 - 2 * ( yy + zz );
    this->matrix[1]  = 2 * ( xy - zw );
    this->matrix[2]  = 2 * ( xz + yw );

    this->matrix[4]  = 2 * ( xy + zw );
    this->matrix[5]  = 1 - 2 * ( xx + zz );
    this->matrix[6]  = 2 * ( yz - xw );

    this->matrix[8]  = 2 * ( xz - yw );
    this->matrix[9]  = 2 * ( yz + xw );
    this->matrix[10] = 1 - 2 * ( xx + yy );

    this->matrix[3]  = 0.0;
    this->matrix[7]  = 0.0;
    this->matrix[11] = 0.0;
    this->matrix[12] = 0.0;
    this->matrix[13] = 0.0;
    this->matrix[14] = 0.0;
    this->matrix[15] = 1.0;
}

/*
Return the address of the first element of the matrix
to be passed to OpenGL or Direct3D for rotation.
*/
float* Quaternion::get_matrix() {
    
    return &this->matrix[0];
}

/*
Quaternion scalar multiplication.
*/
Quaternion Quaternion::operator*(const float& scalar) {
    
    return Quaternion(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}

/*
Quaternion scalar division.
*/
Quaternion Quaternion::operator/(const float& scalar) {
    
    return Quaternion(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
}

/*
Multiply a 3D point by this quaternion.
*/
Vertex Quaternion::operator*(Vertex& v) {
    
    Quaternion qv(v.x, v.y, v.z, 0.0);
    Quaternion q = this->conjugate() * qv;
    q = q * *this;
    return Vertex(q.i(), q.j(), q.k());
}

/*
Multiply a vector by this quaternion.
*/
Vector Quaternion::operator*(Vector& v) {
    
    Quaternion qv(v.i(), v.j(), v.k(), 0.0);
    Quaternion q = this->conjugate() * qv;
    q = q * *this;
    return Vector(q.i(), q.j(), q.k());
}

/*
Quaternion addition.
*/
Quaternion Quaternion::operator+(const Quaternion& other) {
    
    return Quaternion(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

/*
Quaternion subtraction.
*/
Quaternion Quaternion::operator-(const Quaternion& other) {
    
    return Quaternion(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

/*
Multiply two quaternion.
*/
Quaternion Quaternion::operator*(const Quaternion& other) {
    
    float new_x, new_y, new_z, new_w;

    new_x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    new_y = (this->w * other.y) + (this->y * other.w) - (this->x * other.z) + (this->z * other.x);
    new_z = (this->w * other.z) + (this->z * other.w) + (this->x * other.y) - (this->y * other.x);
    new_w = (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    
    return Quaternion(new_x, new_y, new_z, new_w);
}

/*
FIXME: Divide a quaternion by another quaternion
http://www.mathworks.com/help/aeroblks/quaterniondivision.html
*/
Quaternion Quaternion::operator/(const Quaternion& other) {
    
    return other;
}

/*

*/
bool Quaternion::operator==(const Quaternion& other) {
    
    return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
}

/*

*/
bool Quaternion::operator!=(const Quaternion& other) {
    
    return (this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w);
}
