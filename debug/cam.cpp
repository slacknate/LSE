#include "cam.h"
#include "lse/defs.h"
using namespace LSE;

const CamEventTable TestCam::table = CamEventTable({
    
    CamTableEntry(EVENT_KEYBOARD, TestCam::ID_KEY, &TestCam::OnKey)
});


/*

*/
TestCam::TestCam(GLWindow *w) : Object() {
    
    window = w;
    
    this->register_table(&TestCam::table);
}

/*

*/
int TestCam::OnKey(Object *, unsigned int, unsigned int, void *) {
            
    printf("Key!\n");
    return 1;
}
