#include "util/math/matrix.h"
using namespace LSE;

/*

*/
Matrix::Matrix(unsigned int r, unsigned int c) {
    
    rows = r;
    columns = c;
    
    data = new (std::nothrow) float [rows * columns];
    if(data == NULL)
        ERROR_LOG("Failed to allocate memory for matrix data.\n");
}

/*
Create a copy of a pre-existing matrix.
*/
Matrix::Matrix(const Matrix& other) {
    
    rows = other.rows;
    columns = other.columns;
    
    data = new (std::nothrow) float [rows * columns];
    if(data != NULL) {
        
        memcpy(this->data, other.data, sizeof(float) * rows * columns);
    }
    else {
        
        ERROR_LOG("Failed to allocate memory for matrix data.\n");
    }
}

/*

*/
Matrix::~Matrix() {
    
    if(data != NULL)
        delete[] data;
}

/*
Return the array which stores our data.
*/
float* Matrix::raw_matrix() {
    
    return data;
}
 
/*
 
*/  
Matrix Matrix::inverse() {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/  
Matrix Matrix::transpose() {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
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
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/       
void Matrix::operator*(const double& scalar) {
    
    if(data != NULL) {
        
        for(int i = 0; i < rows * columns; ++i)
            data[i] *= scalar;
    }
    else {
        
        
    }
}
 
/*
 
*/  
void Matrix::operator/(const double& scalar) {
    
    if(data != NULL) {
        
        for(int i = 0; i < rows * columns; ++i)
            data[i] /= scalar;
    }
    else {
        
        
    }
}
 
/*
 
*/  
Matrix Matrix::operator+(const Matrix& other) {
    
    if(data != NULL) {
        
        if(this->rows == other.rows && this->columns == other.columns) {
            
            Matrix matrix(rows, columns);
            
            for(int i = 0; i < rows * columns; ++i)
                matrix.data[i] = this->data[i] + other.data[i];
                
            return matrix;
        }
        else {
            
            
        }
    }
    else {
        
        
    }
}
 
/*
 
*/
Matrix Matrix::operator-(const Matrix& other) {
    
    if(data != NULL) {
        
        if(this->rows == other.rows && this->columns == other.columns) {
            
            Matrix matrix(rows, columns);
            
            for(int i = 0; i < rows * columns; ++i)
                matrix.data[i] = this->data[i] - other.data[i];
                
            return matrix;
        }
        else {
            
            
        }
    }
    else {
        
        
    }
}
 
/*
 
*/
Matrix Matrix::operator*(const Matrix& other) {
    
    if(data != NULL) {
        
        if(this->columns == other.rows) {
            
            Matrix matrix(this->rows, other.columns);
            
            for(int i = 0; i < other.columns; ++i) {
                
                for(int j = 0; j < this->rows; ++j) {
                    
                    matrix[j][i] = this->data[rIndex + (cIndex * rows)];
                }
            }
            
            return matrix;
        }
        else {
            
            
        }
    }
    else {
        
        
    }
}
 
/*
"Divide" this matrix by another. We define matrix divison "A/B" as "A(B^-1)"
*/
Matrix Matrix::operator/(Matrix& other) {
    
    return ((*this) * other.Inverse());
}
 
/*
 
*/
float* Matrix::operator[](const int& rIndex) {
    
    if(data != NULL) {
        
        if(rIndex < rows) {
            
            return &data[rIndex];
        }
        else {
            
            
        }
    }
    else {
        
        
    }
}
 
/*
 
*/
bool Matrix::operator==(const Matrix& other) {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/
bool Matrix::operator!=(const Matrix& other) {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
