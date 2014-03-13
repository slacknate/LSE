#include "phy/object.h"

/*
Set our objects point and create a new velocity vector
with the given veloctiy. Default velocity is zero.
*/
LSE_PHObject::LSE_PHObject(double x, double y, double z) {
    
    pX = x;
    pY = y;
    pZ = z;
    mass = 1.0;
}

/*
Free allocated LSE_Vectors.
*/
LSE_PHObject::~LSE_PHObject() {
    
    
}

/*
Apply a force, inducing an acceleration, to this object. test me
The first vector is the force that hits the object. The provided point
in 3D space is the impact point of the force.
test me
fix me -> need to know the center of mass
*/
void LSE_PHObject::ApplyForce(LSE_Vector &force, LSE_Vector &normal, double x, double y, double z) {
    
    //  get the component of force that is converted to linear velocity
    LSE_Vector inverseNormal = normal; // does this create a copy of normal even though normal is a reference?
    inverseNormal = inverseNormal * -1;
    double dotProd = force * inverseNormal;
    LSE_Vector linearForce = inverseNormal;
    linearForce.Normalize();
    linearForce = linearForce * dotProd;
    
    //  get the component of force that is converted to angular velocity
    double tailX = x - force.I() + linearForce.I();
    double tailY = y - force.J() + linearForce.J();
    double tailZ = z - force.K() + linearForce.K();
    LSE_Vector angularForce(x - tailX, y - tailY, z - tailZ);
    
    linearVelocity = linearVelocity + (linearForce / mass);
    angularVelocity = angularVelocity + (angularForce / mass);
}

/*
SDL compatible timer callback.
Adjust the objects position and orientation
based on current linear and angular velocity.
*//*
unsigned int LSE_PHObject::Update(unsigned int delay, void *arg) {
    
    LSE_PHObject *ph = (LSE_PHObject*)arg;
    if(ph) {
            
        if(ph->object) {
        
            // update position
            ph->object->Move(ph->linearVelocity.I()*PHY_UPD_MULT, ph->linearVelocity.J()*PHY_UPD_MULT, ph->linearVelocity.K()*PHY_UPD_MULT);
        
            // update orientation
            LSE_Quaternion q(cos(PI/180.0)/PHY_UPD_MULT, ph->angularVelocity.I(), ph->angularVelocity.J(), ph->angularVelocity.K());
            q.Normalize();
            ph->object->Transform(q);
        }
    }
    
    return delay;
}*/
