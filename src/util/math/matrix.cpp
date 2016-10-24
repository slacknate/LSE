#include <cstring>
#include "lse/exception.h"
#include "util/math/matrix.h"
using namespace LSE;

/*
 * Initialize our matrix in memory and zero it out.
 */
Matrix::Matrix(unsigned int _rows, unsigned int _columns) :
        rows(_rows), columns(_columns), matrix(new float [_rows * _columns]) {

    memset(this->matrix, 0, _rows * _columns);
}

/*
 * Create a copy of a pre-existing matrix.
 */
Matrix::Matrix(const Matrix& other) : Matrix(other.rows, other.columns) {}

/*
 */
Matrix::~Matrix() {
    
    delete[] this->matrix;
}

/*
 * Return the address of the first element of the matrix
 * to be passed to OpenGL or Direct3D for transformation.
 */
float* Matrix::get_matrix() {
    
    return &this->matrix[0];
}
 
/*
 */
Matrix Matrix::inverse() {


}

/*
 */
Matrix Matrix::transpose() {


}

/*
 */
Matrix Matrix::top_triangular() {
    
    
}

/*
 */
Matrix Matrix::bot_triangular() {
    
    
}

/*
 */
float Matrix::determinant() {
    
    float result = 1.0f;

    /*
     * Only square matrices have a determinant.
     */
    if(this->rows == this->columns) {
        
        
    }

    return result;
}

/*
 */
void Matrix::operator*(const float& scalar) {
    
    for(int i = 0; i < rows * columns; ++i)
        this->matrix[i] *= scalar;
}

/*
 */
void Matrix::operator/(const float& scalar) {

    for(int i = 0; i < rows * columns; ++i)
        this->matrix[i] /= scalar;
}

/*
 */
Matrix Matrix::operator+(const Matrix& other) {
    
    if(this->rows == other.rows && this->columns == other.columns) {

        Matrix matrix(rows, columns);

        for(int i = 0; i < rows * columns; ++i)
            matrix.matrix[i] = this->matrix[i] + other.matrix[i];

        return matrix;
    }
    else {

        throw EXCEPTION("Cannot add matrices of unequal dimensions.");
    }
}

/*
 */
Matrix Matrix::operator-(const Matrix& other) {

    if(this->rows == other.rows && this->columns == other.columns) {

        Matrix matrix(rows, columns);

        for(int i = 0; i < rows * columns; ++i)
            matrix.matrix[i] = this->matrix[i] + other.matrix[i];

        return matrix;
    }
    else {

        throw EXCEPTION("Cannot subtract matrices of unequal dimensions.");
    }
}

/*
 */
Matrix Matrix::operator*(const Matrix& other) {
    
//    if(this->columns == other.rows) {
//
//        Matrix matrix(this->rows, other.columns);
//
//        for(int i = 0; i < other.columns; ++i) {
//
//            for(int j = 0; j < this->rows; ++j) {
//
//                matrix[j][i] = this->data[rIndex + (cIndex * rows)];
//            }
//        }
//
//        return matrix;
//    }
//    else {
//
//
//    }
}
 
/*
 * "Divide" this matrix by another. We define matrix divison "A/B" as "A(B^-1)"
 */
Matrix Matrix::operator/(Matrix& other) {
    
    return ((*this) * other.inverse());
}

/*
 
*/
bool Matrix::operator==(const Matrix& other) {
    

}

/*
 */
bool Matrix::operator!=(const Matrix& other) {


}
