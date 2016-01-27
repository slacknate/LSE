#include <cstdio>
#include "cam.h"
#include "lse/defs.h"
using namespace LSE;


/*

*/
TestCam::TestCam(GLWindow *w) : Object() {
    
    window = w;
}


/*

*/
int TestCam::OnKey(Event *) {
            
    printf("Key!\n");
    return 1;
}
