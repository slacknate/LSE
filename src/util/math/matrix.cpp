#include "util/math/matrix.h"
using namespace LSE;

/*

*/
LSE_Matrix::LSE_Matrix(unsigned int r, unsigned int c) {
    
    rows = r;
    columns = c;
    
    data = new (std::nothrow) float [rows * columns];
    if(data == NULL)
        LSE_ERROR_LOG("Failed to allocate memory for matrix data.\n");
}

/*
Create a copy of a pre-existing matrix.
*/
LSE_Matrix::LSE_Matrix(const LSE_Matrix& other) {
    
    rows = other.rows;
    columns = other.columns;
    
    data = new (std::nothrow) float [rows * columns];
    if(data != NULL) {
        
        memcpy(this->data, other.data, sizeof(float) * rows * columns);
    }
    else {
        
        LSE_ERROR_LOG("Failed to allocate memory for matrix data.\n");
    }
}

/*

*/
LSE_Matrix::~LSE_Matrix() {
    
    if(data != NULL)
        delete[] data;
}

/*
Return the array which stores our data.
*/
float* LSE_Matrix::RawMatrix() {
    
    return data;
}
 
/*
 
*/  
LSE_Matrix LSE_Matrix::Inverse() {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/  
LSE_Matrix LSE_Matrix::Transpose() {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}

/*

*/
LSE_Matrix LSE_Matrix::TopTriangular() {
    
    
}

/*

*/
LSE_Matrix LSE_Matrix::BotTriangular() {
    
    
}
    
/*
 
*/     
float LSE_Matrix::Determinant() {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/       
void LSE_Matrix::operator*(const double& scalar) {
    
    if(data != NULL) {
        
        for(int i = 0; i < rows * columns; ++i)
            data[i] *= scalar;
    }
    else {
        
        
    }
}
 
/*
 
*/  
void LSE_Matrix::operator/(const double& scalar) {
    
    if(data != NULL) {
        
        for(int i = 0; i < rows * columns; ++i)
            data[i] /= scalar;
    }
    else {
        
        
    }
}
 
/*
 
*/  
LSE_Matrix LSE_Matrix::operator+(const LSE_Matrix& other) {
    
    if(data != NULL) {
        
        if(this->rows == other.rows && this->columns == other.columns) {
            
            LSE_Matrix matrix(rows, columns);
            
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
LSE_Matrix LSE_Matrix::operator-(const LSE_Matrix& other) {
    
    if(data != NULL) {
        
        if(this->rows == other.rows && this->columns == other.columns) {
            
            LSE_Matrix matrix(rows, columns);
            
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
LSE_Matrix LSE_Matrix::operator*(const LSE_Matrix& other) {
    
    if(data != NULL) {
        
        if(this->columns == other.rows) {
            
            LSE_Matrix matrix(this->rows, other.columns);
            
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
LSE_Matrix LSE_Matrix::operator/(LSE_Matrix& other) {
    
    return ((*this) * other.Inverse());
}
 
/*
 
*/
float* LSE_Matrix::operator[](const int& rIndex) {
    
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
bool LSE_Matrix::operator==(const LSE_Matrix& other) {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
 
/*
 
*/
bool LSE_Matrix::operator!=(const LSE_Matrix& other) {
    
    if(data != NULL) {
        
        
    }
    else {
        
        
    }
}
