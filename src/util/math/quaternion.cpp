#include "util/math/quaternion.h"
#include "lse/defs.h"

/*
Initialize our quaternion by default to a identity orientation.
*/
LSE_Quaternion::LSE_Quaternion() {
    
    i = 0.0;
    j = 0.0;
    k = 0.0;
    s = 1.0;
    
    UpdateMatrix();
}

/*
Initialize our quaternion given all four components.
*/
LSE_Quaternion::LSE_Quaternion(double x, double y, double z, double n) {
    
    i = x;
    j = y;
    k = z;
    s = n;
    
    UpdateMatrix();
}

/*
Get the X component.
*/
double LSE_Quaternion::I() {
    
    return i;
}

/*
Get the Y component.
*/
double LSE_Quaternion::J() {
    
    return j;
}

/*
Get the Z component.
*/
double LSE_Quaternion::K() {
    
    return k;
}

/*
Get the scalar component.
*/
double LSE_Quaternion::S() {
    
    return s;
}

/*
Get the length of the quaternion.
*/
double LSE_Quaternion::Norm() {
    
    return sqrt(i*i + j*j + k*k + s*s);
}

/*
Return the conjugate of this quaternion.
*/
LSE_Quaternion LSE_Quaternion::Conjugate() {
    
    return LSE_Quaternion(-i, -j, -k, s);
}

/*
Make this quaternion a unit quaternion in its current direction.
*/
void LSE_Quaternion::Normalize() {
    
    double size = Norm();
    
    if(size > 0) {
        
        i /= size;
        j /= size;
        k /= size;
        s /= size;
    }
}

/*
Generates a rotation matrix from this quaternion.
This matrix can be used natively with OpenGL,
but must be transposed to be used with Direct3D.

Reference:
    www.cprogramming.com/tutorial/3d/LSE_Quaternions.html
    http://www.flipcode.com/documents/matrfaq.html#Q54

0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15
*/
void LSE_Quaternion::UpdateMatrix() {
    
    double xx = i * i;
    double xy = i * j;
    double xz = i * k;
    double xw = i * s;

    double yy = j * j;
    double yz = j * k;
    double yw = j * s;

    double zz = k * k;
    double zw = k * s;

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
double* LSE_Quaternion::GetMatrix() {
    
    return &matrix[0];
}

/*
LSE_Quaternion scalar multiplication.
*/
LSE_Quaternion LSE_Quaternion::operator*(const double& scalar) {
    
    return LSE_Quaternion(this->i * scalar, this->j * scalar, this->k * scalar, this->s * scalar);
}

/*
Quaternion scalar division.
*/
LSE_Quaternion LSE_Quaternion::operator/(const double& scalar) {
    
    return LSE_Quaternion(this->i / scalar, this->j / scalar, this->k / scalar, this->s / scalar);
}

/*
Multiply a 3D point by this quaternion.
*/
LSE_Vertex LSE_Quaternion::operator*(LSE_Vertex& v) {
    
    LSE_Quaternion qv(v.x, v.y, v.z, 0.0);
    LSE_Quaternion q = this->Conjugate() * qv;
    q = q * *this;
    return LSE_Vertex(q.I(), q.J(), q.K());
}

/*
Multiply a vector by this quaternion.
*/
LSE_Vector LSE_Quaternion::operator*(LSE_Vector& v) {
    
    LSE_Quaternion qv(v.I(), v.J(), v.K(), 0.0);
    LSE_Quaternion q = this->Conjugate() * qv;
    q = q * *this;
    return LSE_Vector(q.I(), q.J(), q.K());
}

/*
Quaternion addition.
*/
LSE_Quaternion LSE_Quaternion::operator+(const LSE_Quaternion& other) {
    
    return LSE_Quaternion(this->i + other.i, this->j + other.j, this->k + other.k, this->s + other.s);
}

/*
Quaternion subtraction.
*/
LSE_Quaternion LSE_Quaternion::operator-(const LSE_Quaternion& other) {
    
    return LSE_Quaternion(this->i - other.i, this->j - other.j, this->k - other.k, this->s - other.s);
}

/*
Multiply two quaternion.
*/
LSE_Quaternion LSE_Quaternion::operator*(const LSE_Quaternion& other) {
    
    double x, y, z, n;
    
    x = (this->s * other.i) + (this->i * other.s) + (this->j * other.k) - (this->k * other.j);
    y = (this->s * other.j) + (this->j * other.s) - (this->i * other.k) + (this->k * other.i);
    z = (this->s * other.k) + (this->k * other.s) + (this->i * other.j) - (this->j * other.i);
    n = (this->s * other.s) - (this->i * other.i) - (this->j * other.j) - (this->k * other.k);
    
    return LSE_Quaternion(x, y, z, n);
}

/*
Divide a quaternion by another quaternion. fix me
http://www.mathworks.com/help/aeroblks/quaterniondivision.html
*/
LSE_Quaternion LSE_Quaternion::operator/(const LSE_Quaternion& other) {
    
    return other;
}

/*

*/
bool LSE_Quaternion::operator==(const LSE_Quaternion& other) {
    
    return (this->i == other.i && this->j == other.j && this->k == other.k && this->s == other.s);
}

/*

*/
bool LSE_Quaternion::operator!=(const LSE_Quaternion& other) {
    
    return (this->i != other.i || this->j != other.j || this->k != other.k || this->s != other.s);
}
