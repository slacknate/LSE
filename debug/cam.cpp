#include "cam.h"
#include "lse/defs.h"
using namespace LSE;

EVTMAP(TestCam) CamMap[] = {
    
    EVTFUNC(EVENT_KEYBOARD, TestCam::ID_KEY, TestCam::OnKey)
};

EVTIMP(TestCam, CamMap);

/*

*/
TestCam::TestCam(GLWindow *w) : Object() {
    
    window = w;
}

/*

*/
bool TestCam::OnKey(Object *, unsigned int, unsigned int, void *) {
            
    printf("Key!\n");
    return true;
}
