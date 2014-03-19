#include "prism.h"

LSE_EVTMAP(TestPrism) PrismMap[] = {
    
    LSE_EVTFUNC(LSE_MOUSE,      TestPrism::ID_MOUSE,    TestPrism::OnMouseMotion),
    LSE_EVTFUNC(LSE_KEYBOARD,   TestPrism::ID_KEY,      TestPrism::OnKey)
};

LSE_EVTIMP(TestPrism, PrismMap);

/*

*/
TestPrism::TestPrism(LSE_GLWindow *win, double x, double y, double z, double w, double h, double d) : LSE_GLRectPrism(x, y, z, w, h, d) {
    
    window = win;
}

/*

*/
bool TestPrism::OnMouseMotion(LSE_Object *, unsigned int, unsigned int, void *) {
    
    /*SDL_MouseMotionEvent *event = (SDL_MouseMotionEvent *)ptr;
    if(event != NULL) {
        
        if(event->state == SDL_PRESSED) {
            
            LSE_Vector v(event->yrel, event->xrel, 0);
            v.Normalize();

            LSE_Quaternion q(10.0*cos(3.14159265359/180.0), v.I(), v.J(), v.K());
            q.Normalize();
        
            Transform(q);
        }
    }*/
    
    return true;
}

/*

*/
bool TestPrism::OnKey(LSE_Object *, unsigned int, unsigned int, void *ptr) {
    
    printf("Key!\n");
    LSE_KeyEvent *event = (LSE_KeyEvent *)ptr;
    
    LSE_Vertex& pos = window->GetCamPos();
    LSE_Vertex& foc = window->GetCamFocus();
            
    if(event->key == 'w') {
                
        pos.z += 0.1;
    }
    else if(event->key == 'a') {
                
        pos.x -= 0.1;
    }
    else if(event->key == 's') {
                
        pos.z -= 0.1;
    }
    else if(event->key == 'd') {
                
        pos.x += 0.1;
    }
            
    if(event->key == 'i') {
                
        foc.z += 0.1;
    }
    else if(event->key == 'j') {
                
        foc.x -= 0.1;
    }
    else if(event->key == 'k') {
                
        foc.z -= 0.1;
    }
    else if(event->key == 'l') {
                
        foc.x += 0.1;
    }
    
    return true;
}
