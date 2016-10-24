#include <cstdio>
#include "prism.h"
using namespace LSE;


/*

*/
TestPrism::TestPrism(GLWindow *win, float x, float y, float z, float w, float h, float d) : GLRectPrism(x, y, z, w, h, d) {
    
    window = win;

    this->subscribe<TestPrism>(EVENT_MOUSE, &TestPrism::OnMouseMotion);
    this->subscribe<TestPrism>(EVENT_KEYBOARD, &TestPrism::OnKey);
}

/*

*/
void TestPrism::OnMouseMotion(Event *ev) {
    
    MouseEvent *event = (MouseEvent *)ev;
    if(event != NULL) {

//        if(event->button == MOUSE_LEFT && event->state == STATE_DOWN) {

            Vector v(event->dY, event->dX, 0);
            v.normalize();

            Quaternion q((float)cos(PI/180.0), v.i(), v.j(), v.k());
            q.normalize();

            rotate(q);
//        }
    }
}

/*

*/
void TestPrism::OnKey(Event *ev) {
    
    KeyEvent *event = (KeyEvent *)ev;

    if(event->key == 'W') {

        Vector v(0.0f, 0.0f, 0.5f);
        this->translate(v);
    }
    else if(event->key == 'A') {

        Vector v(-0.5f, 0.0f, 0.0f);
        this->translate(v);
    }
    else if(event->key == 'S') {

        Vector v(0.0f, 0.0f, -0.5f);
        this->translate(v);
    }
    else if(event->key == 'D') {

        Vector v(0.5f, 0.0f, 0.0f);
        this->translate(v);
    }
            
//    if(event->key == 'i') {
//
//        foc.z += 0.1;
//    }
//    else if(event->key == 'j') {
//
//        foc.x -= 0.1;
//    }
//    else if(event->key == 'k') {
//
//        foc.z -= 0.1;
//    }
//    else if(event->key == 'l') {
//
//        foc.x += 0.1;
//    }
}
