#include <cstring>
#include "lse/exception.h"
#include "util/memory.h"
#include "util/math/matrix.h"
using namespace LSE;


/*
 * Initialize our number of rows from our matrix
 * and set our column pointer to NULL.
 */
MatrixColumn::MatrixColumn(unsigned int _rows) : rows(_rows), column(nullptr) {}


/*
 * Set our current column pointer.
 */
void MatrixColumn::set_column(float *col_ptr) {

    this->column = col_ptr;
}

/*
 * Return a pointer to the specified row of our column pointer.
 *
 * This is our second dimension indexing into our matrix.
 *
 * If the specified row is greater than the number of rows we
 * throw an exception so we do not do nasty stuff to memory!
 */
float* MatrixColumn::operator[](const int& row) {

    if(row >= this->rows)
        throw EXCEPTION("Matrix only has %u rows, cannot index into row %u.", this->rows, row);

    return &this->column[row];
}


/*
 * Initialize our matrix in memory and zero it out.
 */
Matrix::Matrix(unsigned int _columns, unsigned int _rows) : columns(_columns), rows(_rows), mat_col(_rows) {

    this->matrix = LSE::CALLOC(float, _columns * _rows);
}

/*
 * Create a square matrix, optionally initializing
 * it to be an identity matrix.
 */
Matrix::Matrix(unsigned int _cols_rows, bool identity) : Matrix(_cols_rows, _cols_rows) {

    if(identity) {

        for(unsigned int i = 0; i < _cols_rows; ++i)
            this->matrix[i + (i * _cols_rows)] = 1.0f;
    }
}

/*
 * Create a copy of a pre-existing matrix.
 */
Matrix::Matrix(const Matrix& other) : Matrix(other.rows, other.columns) {

    memcpy(this->matrix, other.matrix, sizeof(float) * other.rows * other.columns);
}

/*
 * Free up the array created to represent this matrix.
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
 * FIXME: implement!
 */
Matrix Matrix::inverse() {


}

/*
 * FIXME: implement!
 */
Matrix Matrix::transpose() {


}

/*
 * FIXME: implement!
 */
Matrix Matrix::top_triangular() {
    
    
}

/*
 * FIXME: implement!
 */
Matrix Matrix::bot_triangular() {
    
    
}

/*
 * FIXME: implement!
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
 * Set the current column in our MatrixColumn object
 * and then return a reference to it.
 *
 * If the specified column is greater than the number of columns we
 * throw an exception so we do not do nasty stuff to memory!
 *
 * This allows us to bounds check on both the column
 * and the row index so we can throw an exception if
 * necessary.
 */
MatrixColumn& Matrix::operator[](const int& column) {

    if(column >= this->columns)
        throw EXCEPTION("Matrix only has %u rows, cannot index into row %u.", this->columns, column);

    float *col_ptr = &this->matrix[column * this->rows];
    this->mat_col.set_column(col_ptr);

    return this->mat_col;
}

/*
 * Matrix scalar multiplication.
 */
void Matrix::operator*(const float& scalar) {
    
    for(int i = 0; i < rows * columns; ++i)
        this->matrix[i] *= scalar;
}

/*
 * Matrix scalar division.
 */
void Matrix::operator/(const float& scalar) {

    for(int i = 0; i < rows * columns; ++i)
        this->matrix[i] /= scalar;
}

/*
 * Add a matrix to this matrix.
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
 * Subtract a matrix from this matrix.
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
 * FIXME: implement!
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
 * "Divide" this matrix by another. We define matrix division "A/B" as "A(B^-1)"
 */
Matrix Matrix::operator/(Matrix& other) {
    
    return ((*this) * other.inverse());
}

/*
 * Check for equality of two matrices.
 *
 * If they are unequal in size then they are
 * automatically considered not equal.
 *
 * Otherwise we compare the data in memory for equality.
 */
bool Matrix::operator==(const Matrix& other) {

    bool result = false;

    if(this->rows == other.rows && this->columns == other.columns)
        result = (memcmp(this->matrix, other.matrix, sizeof(float) * other.rows * other.columns) == 0);

    return result;
}

/*
 * Check for inequality of two matrices.
 *
 * If they are unequal in size then they are
 * automatically considered not equal.
 *
 * Otherwise we compare the data in memory for inequality.
 */
bool Matrix::operator!=(const Matrix& other) {

    bool result = true;

    if(this->rows == other.rows && this->columns == other.columns)
        result = (memcmp(this->matrix, other.matrix, sizeof(float) * other.rows * other.columns) != 0);

    return result;
}
