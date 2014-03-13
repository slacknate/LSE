#ifndef LSE_VECTOR_H
#define LSE_VECTOR_H

/*

*/
class LSE_Vector {
    
    private:
        
        double i, j, k; // LSE_Vector components
        
    public:
        
        LSE_Vector();
        LSE_Vector(double x, double y, double z);
        ~LSE_Vector();
        
        double I();
        double J();
        double K();
        double Length();
        void Normalize();
        void Orthagonalize(LSE_Vector& v);
        
        LSE_Vector operator*(const double& scalar);
        LSE_Vector operator/(const double& scalar);
        LSE_Vector operator+(const LSE_Vector& other);
        LSE_Vector operator-(const LSE_Vector& other);
        double operator^(LSE_Vector& other);
        double operator*(const LSE_Vector& other);
        LSE_Vector operator%(const LSE_Vector& other);
        bool operator==(const LSE_Vector& other);
        bool operator!=(const LSE_Vector& other);
};

#endif
