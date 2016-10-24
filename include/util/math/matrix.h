#ifndef LSE_MATRIX_H
#define LSE_MATRIX_H

#include <cmath>
#include "lse/defs.h"

namespace LSE {

/*
A matrix stored in column major format.
*/
class Matrix {
    
    private:
        
        unsigned int rows, columns; // matrix dimensions
        float *matrix; // matrix data
        
    public:
        
        Matrix(unsigned int r, unsigned int c);
        Matrix(const Matrix& other);
        ~Matrix();
        
        float* get_matrix();
        
        Matrix inverse();
        Matrix transpose();
        Matrix top_triangular();
        Matrix bot_triangular();
        
        float determinant();
        
        void operator*(const float& scalar);
        void operator/(const float& scalar);
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix operator/(Matrix& other);
        bool operator==(const Matrix& other);
        bool operator!=(const Matrix& other);
};

}

#endif
