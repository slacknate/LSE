#ifndef LSE_MATRIX_H
#define LSE_MATRIX_H

#include "lse/defs.h"

/*
A matrix stored in column major format.
*/
class LSE_Matrix {
    
    private:
        
        unsigned int rows, columns; // matrix dimensions
        float *data; // matrix data
        
    public:
        
        LSE_Matrix(unsigned int r, unsigned int c);
        LSE_Matrix(const LSE_Matrix& other);
        ~LSE_Matrix();
        
        float* RawMatrix();
        
        LSE_Matrix Inverse();
        LSE_Matrix Transpose();
        LSE_Matrix TopTriangular();
        LSE_Matrix BotTriangular();
        
        float Determinant();
        
        void operator*(const double& scalar);
        void operator/(const double& scalar);
        LSE_Matrix operator+(const LSE_Matrix& other);
        LSE_Matrix operator-(const LSE_Matrix& other);
        LSE_Matrix operator*(const LSE_Matrix& other);
        LSE_Matrix operator/(LSE_Matrix& other);
        float* operator[](const int& rIndex);
        bool operator==(const LSE_Matrix& other);
        bool operator!=(const LSE_Matrix& other);
};

#endif
