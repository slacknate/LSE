#include "cam.h"
#include "lse/defs.h"

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
bool TestCam::OnKey(LSE_Object *o, unsigned int type, unsigned int id, void *ptr) {
            
    printf("Key!\n");
}
