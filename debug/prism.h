#ifndef TEST_PRISM_H
#define TEST_PRISM_H

#include "gl/rectprism.h"
#include "gui/window/window.h"

namespace LSE {

// test lse_globject class
class TestPrism : public GLRectPrism {
    
    private:
        
        static const EventTable<TestPrism> table;
        
        GLWindow *window; // system provided opengl context
    
    public:
        
        TestPrism(GLWindow *win, double x, double y, double z, double w, double h, double d);
        
        enum {
            
            ID_MOUSE = 1,
            ID_KEY
        };
        
        int OnMouseMotion(Object *sender, unsigned int type, unsigned int id, void *ptr);
        int OnKey(Object *o, unsigned int type, unsigned int id, void *ptr);
};

typedef EventTable<TestPrism> PrismEventTable;
typedef EventTableEntry<TestPrism> PrismTableEntry;

}

#endif
