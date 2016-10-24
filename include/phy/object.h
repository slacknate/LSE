#ifndef LSE_PHY_OBJ_H
#define LSE_PHY_OBJ_H

#include "lse/object.h"
#include "util/math/vector.h"
#include "util/math/quaternion.h"

namespace LSE {

/*
Physics constants.
*/
const int PHY_UPD_TIME   = 1;
const float PHY_UPD_MULT = 0.001f;
const double PI          = 3.14159265359;

/*
Class that describes an object which will have physical interaction
with other objects of the same type.
*/
class PHObject : public Object {
    
    protected:
        
        Vector linearVelocity, angularVelocity; // object linear and angular velocity
        Vertex pos; // location of this object in 3D space
        double mass; // object mass
        
    public:
        
        PHObject(double x, double y, double z);
        
        void ApplyForce(Vector& force, Vector &normal, double x, double y, double z);
        //static unsigned int Update(unsigned int delay, void *arg);
};

}

#endif
