#include "util/math/quaternion.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize our quaternion by default to a identity orientation.
*/
Quaternion::Quaternion() {
    
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 1.0;

    update_matrix();
}

/*
Initialize our quaternion given all four components.
*/
Quaternion::Quaternion(double x, double y, double z, double w) {

    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;

    update_matrix();
}

/*
Get the X component.
*/
double Quaternion::i() {
    
    return x;
}

/*
Get the Y component.
*/
double Quaternion::j() {
    
    return y;
}

/*
Get the Z component.
*/
double Quaternion::k() {
    
    return z;
}

/*
Get the scalar component.
*/
double Quaternion::s() {
    
    return w;
}

/*
Get the length of the quaternion.
*/
double Quaternion::norm() {
    
    return sqrt(x * x + y * y + z * z + w * w);
}

/*
Return the conjugate of this quaternion.
*/
Quaternion Quaternion::conjugate() {
    
    return Quaternion(-x, -y, -z, w);
}

/*
Make this quaternion a unit quaternion in its current direction.
*/
void Quaternion::normalize() {
    
    double size = norm();
    
    if(size > 0) {
        
        x /= size;
        y /= size;
        z /= size;
        w /= size;
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
    
    double xx = x * x;
    double xy = x * y;
    double xz = x * z;
    double xw = x * w;

    double yy = y * y;
    double yz = y * z;
    double yw = y * w;

    double zz = z * z;
    double zw = z * w;

    matrix[0]  = 1 - 2 * ( yy + zz );
    matrix[1]  = 2 * ( xy - zw );
    matrix[2]  = 2 * ( xz + yw );

    matrix[4]  = 2 * ( xy + zw );
    matrix[5]  = 1 - 2 * ( xx + zz );
    matrix[6]  = 2 * ( yz - xw );

    matrix[8]  = 2 * ( xz - yw );
    matrix[9]  = 2 * ( yz + xw );
    matrix[10] = 1 - 2 * ( xx + yy );

    matrix[3]  = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0.0;
    matrix[15] = 1.0;
}

/*
Return the address of the first element of the matrix
to be passed to OpenGL or Direct3D for rotation.
*/
double* Quaternion::get_matrix() {
    
    return &matrix[0];
}

/*
Quaternion scalar multiplication.
*/
Quaternion Quaternion::operator*(const double& scalar) {
    
    return Quaternion(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}

/*
Quaternion scalar division.
*/
Quaternion Quaternion::operator/(const double& scalar) {
    
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
    
    double x, y, z, n;
    
    x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    y = (this->w * other.y) + (this->y * other.w) - (this->x * other.z) + (this->z * other.x);
    z = (this->w * other.z) + (this->z * other.w) + (this->x * other.y) - (this->y * other.x);
    n = (this->w * other.w) - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    
    return Quaternion(x, y, z, n);
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
