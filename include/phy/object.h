#ifndef LSE_PHYS_OBJ_H
#define LSE_PHYS_OBJ_H

#include "lse/object.h"
#include "util/math/vector.h"
#include "util/math/quaternion.h"

/*
Physics constants.
*/
#define PHY_UPD_TIME            1
#define PHY_UPD_MULT            0.001
#define PI                      3.14159265359

/*
Class that describes an object which will have physical interaction
with other objects of the same type.
*/
class LSE_PHObject : public LSE_Object {
    
    protected:
        
        LSE_Vector linearVelocity, angularVelocity; // object linear and angular velocity
        double pX, pY, pZ; // location of this object in 3D space
        double mass; // object mass
        
    public:
        
        LSE_PHObject(double x, double y, double z);
        
        void ApplyForce(LSE_Vector& force, LSE_Vector &normal, double x, double y, double z);
        //static unsigned int Update(unsigned int delay, void *arg);
};

#endif
