#include <cstdio>
#include "prism.h"
using namespace LSE;

const PrismEventTable TestPrism::table = PrismEventTable({
    
    PrismTableEntry(EVENT_MOUSE,      TestPrism::ID_MOUSE,    &TestPrism::OnMouseMotion),
    PrismTableEntry(EVENT_KEYBOARD,   TestPrism::ID_KEY,      &TestPrism::OnKey)
});

/*

*/
TestPrism::TestPrism(GLWindow *win, double x, double y, double z, double w, double h, double d) : GLRectPrism(x, y, z, w, h, d) {
    
    window = win;
    
    this->register_table(&TestPrism::table);
}

/*

*/
int TestPrism::OnMouseMotion(Object *, unsigned int, unsigned int, void *) {
    
    /*SDL_MouseMotionEvent *event = (SDL_MouseMotionEvent *)ptr;
    if(event != NULL) {
        
        if(event->state == SDL_PRESSED) {
            
            Vector v(event->yrel, event->xrel, 0);
            v.normalize();

            Quaternion q(10.0*cos(3.14159265359/180.0), v.I(), v.J(), v.K());
            q.normalize();
        
            Transform(q);
        }
    }*/
    
    return 1;
}

/*

*/
int TestPrism::OnKey(Object *, unsigned int, unsigned int, void *ptr) {
    
    printf("Key!\n");
    KeyEvent *event = (KeyEvent *)ptr;
    
    Vertex& pos = window->cam_pos();
    Vertex& foc = window->cam_focus();
            
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
    
    return 1;
}
