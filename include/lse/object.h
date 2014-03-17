#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include "lse/defs.h"
#include "lse/event.h"

/*
Class event map type declaration.
*/
#define \
LSE_DECLARE(classname) \
public: \
typedef struct { unsigned int type; unsigned int id; bool (classname::*func)(LSE_Object *, unsigned int, unsigned int, void *); } LSE_MapKey; \
virtual bool Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr); \
private: \
static const int mapSize;

/*
Event map declaration.
*/
#define LSE_EVTMAP(classname) static const classname::LSE_MapKey 

/*
Event map entry.
*/
#define LSE_EVTFUNC(type, id, handler) {type, id, &handler}

/*
Event handler implementation.
*/
#define LSE_EVTIMP(classname, map) \
const int classname::mapSize = (sizeof(map)/sizeof(map[0])); \
bool classname::Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr) { \
for(int i = 0; i < mapSize; ++i) { if((map[i].type == type && map[i].id == id) || (map[i].type == LSE_ANY && map[i].id == LSE_ANY)) \
{ int result = (this->*(map[i].func))(sender, type, id, ptr); if(result != 0) { return result; } continue; } } return false; }

/*
Base class for all Lucent Shards Engine objects.
TODO: refactor Dispatch to return an int instead of a bool.
      returning real result codes would probably be a nice feature
      for an event handler.
*/
class LSE_Object {
    
    public:
        
        virtual bool Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
