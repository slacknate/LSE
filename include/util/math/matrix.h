#ifndef LSE_MATRIX_H
#define LSE_MATRIX_H

#include <cmath>
#include "lse/defs.h"

namespace LSE {

/*
 * Object to implement smart double indexing into our matrix.
 */
class MatrixColumn {

    private:

        unsigned int rows;
        float *column;

    public:

        MatrixColumn(unsigned int _rows);

        void set_column(float *col_ptr);

        float& operator[](const int& row);
};

/*
A matrix stored in column major format.
*/
class Matrix {
    
    private:

        MatrixColumn mat_col; // object to return a reference to in in operator[]
        unsigned int columns, rows; // matrix dimensions
        float *matrix; // matrix data
        
    public:
        
        Matrix(unsigned int _columns, unsigned int _rows);
        Matrix(unsigned int _col_rows, bool identity=false);
        Matrix(const Matrix& other);
        ~Matrix();
        
        float* get_matrix();
        
        Matrix inverse();
        Matrix transpose();
        Matrix top_triangular();
        Matrix bot_triangular();
        
        float determinant();

        MatrixColumn& operator[](const int& column);

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
