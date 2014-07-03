#include "cam.h"
#include "lse/defs.h"
using namespace LSE;

LSE_EVTMAP(TestCam) CamMap[] = {
    
    LSE_EVTFUNC(LSE_KEYBOARD, TestCam::ID_KEY, TestCam::OnKey)
};

LSE_EVTIMP(TestCam, CamMap);

/*

*/
TestCam::TestCam(LSE_GLWindow *w) : LSE_Object() {
    
    window = w;
}

/*

*/
bool TestCam::OnKey(LSE_Object *, unsigned int, unsigned int, void *) {
            
    printf("Key!\n");
    return true;
}
