#include <cstdio>
#include "prism.h"
using namespace LSE;


/*

*/
TestPrism::TestPrism(GLWindow *win, double x, double y, double z, double w, double h, double d) : GLRectPrism(x, y, z, w, h, d) {
    
    window = win;

    this->subscribe<TestPrism>(EVENT_MOUSE, &TestPrism::OnMouseMotion);
    this->subscribe<TestPrism>(EVENT_KEYBOARD, &TestPrism::OnKey);
}

/*

*/
void TestPrism::OnMouseMotion(Event *) {
    
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
}

/*

*/
void TestPrism::OnKey(Event *ev) {
    
    printf("Key!\n");
    KeyEvent *event = (KeyEvent *)ev;
    
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
}
