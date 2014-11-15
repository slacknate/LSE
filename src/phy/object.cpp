#include "phy/object.h"
using namespace LSE;

/*
Set our objects point and create a new velocity vector
with the given veloctiy. Default velocity is zero.
*/
PHObject::PHObject(double x, double y, double z) {
    
    pX = x;
    pY = y;
    pZ = z;
    mass = 1.0;
}

/*
Apply a force, inducing an acceleration, to this object. test me
The first vector is the force that hits the object. The provided point
in 3D space is the impact point of the force.
test me
fix me -> need to know the center of mass
*/
void PHObject::ApplyForce(Vector &force, Vector &normal, double x, double y, double z) {
    
    //  get the component of force that is converted to linear velocity
    Vector inverseNormal = normal; // does this create a copy of normal even though normal is a reference? - the answer is yes, thanks hbock!
    inverseNormal = inverseNormal * -1;
    double dotProd = force * inverseNormal;
    Vector linearForce = inverseNormal;
    linearForce.normalize();
    linearForce = linearForce * dotProd;
    
    //  get the component of force that is converted to angular velocity
    double tailX = x - force.i() + linearForce.i();
    double tailY = y - force.j() + linearForce.j();
    double tailZ = z - force.k() + linearForce.k();
    Vector angularForce(x - tailX, y - tailY, z - tailZ);
    
    linearVelocity = linearVelocity + (linearForce / mass);
    angularVelocity = angularVelocity + (angularForce / mass);
}

/*
SDL compatible timer callback.
Adjust the objects position and orientation
based on current linear and angular velocity.
*//*
unsigned int PHObject::Update(unsigned int delay, void *arg) {
    
    PHObject *ph = (PHObject*)arg;
    if(ph) {
            
        if(ph->object) {
        
            // update position
            ph->object->Move(ph->linearVelocity.I()*PHY_UPD_MULT, ph->linearVelocity.J()*PHY_UPD_MULT, ph->linearVelocity.K()*PHY_UPD_MULT);
        
            // update orientation
            Quaternion q(cos(PI/180.0)/PHY_UPD_MULT, ph->angularVelocity.I(), ph->angularVelocity.J(), ph->angularVelocity.K());
            q.normalize();
            ph->object->Transform(q);
        }
    }
    
    return delay;
}*/
