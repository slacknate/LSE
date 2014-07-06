#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include "lse/defs.h"
#include "lse/event.h"

// TODO: do these defines need to exist? can we refactor the object class to do all this for us without defines?
namespace LSE {

/*
Class event map type declaration.
*/
#define \
DECLARE(classname) \
public: \
typedef struct { unsigned int type; unsigned int id; bool (classname::*func)(Object *, unsigned int, unsigned int, void *); } MapKey; \
virtual int Dispatch(Object *sender, unsigned int type, unsigned int id, void *ptr); \
private: \
static const int mapSize;

/*
Event map declaration.
*/
#define EVTMAP(classname) static const classname::MapKey 

/*
Event map entry.
*/
#define EVTFUNC(type, id, handler) {type, id, &handler}

/*
Event handler implementation.
*/
#define EVTIMP(classname, map) \
const int classname::mapSize = (sizeof(map)/sizeof(map[0])); \
int classname::Dispatch(Object *sender, unsigned int type, unsigned int id, void *ptr) { \
for(int i = 0; i < mapSize; ++i) { if((map[i].type == type && map[i].id == id) || (map[i].type == ANY && map[i].id == ANY)) \
{ int result = (this->*(map[i].func))(sender, type, id, ptr); if(result != 0) { return result; } continue; } } return false; }

/*
Base class for all Lucent Shards Engine objects.
*/
class Object {
    
    public:
        
        virtual ~Object() {}
        
        virtual int Dispatch(Object *, unsigned int, unsigned int, void *) { return 0; }
};

}

#endif
