#include <cstdlib>
#include "lse/defs.h"
#include "lse/listnode.h"
using namespace LSE;

/*
Initialize our node as empty.
*/
ListNode::ListNode() {
    
    prev = next = NULL;
    data = NULL;
}

/*
Create a copy of an existing node.
*/
ListNode::ListNode(const ListNode& other) {
    
    prev = next = NULL;
    SetData(other.data);
}

/*
Initialize our node with data.
*/
ListNode::ListNode(void *d) {
    
    prev = next = NULL;
    SetData(d);
}

/*

*/
ListNode::~ListNode() {
    
    //logger.error("ListNode::~ListNode(): MEMORY LEAK!");
    //delete data;
}

/*
Store data in this node.
*/
void ListNode::SetData(void *d) {
    
    data = d;
}

/*
Return the previous node in the list.
*/      
ListNode* ListNode::GetPrev() const {
    
    return prev;
}

/*
Return the next node in the list.
*/
ListNode* ListNode::GetNext() const {
    
    return next;
}

/*
Return this nodes data.
*/
void* ListNode::GetData() const {
    
    return data;
}
