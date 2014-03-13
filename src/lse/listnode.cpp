#include <cstdlib>
#include "lse/defs.h"
#include "lse/listnode.h"

/*
Initialize our node as empty.
*/
LSE_ListNode::LSE_ListNode() {
    
    prev = next = NULL;
    data = NULL;
}

/*
Create a copy of an existing node.
*/
LSE_ListNode::LSE_ListNode(const LSE_ListNode& other) {
    
    prev = next = NULL;
    SetData(other.data);
}

/*
Initialize our node with data.
*/
LSE_ListNode::LSE_ListNode(void *d) {
    
    prev = next = NULL;
    SetData(d);
}

/*

*/
LSE_ListNode::~LSE_ListNode() {
    
    LSE_ERROR_LOG("LSE_ListNode::~LSE_ListNode(): MEMORY LEAK!");
    //delete data;
}

/*
Store data in this node.
*/
void LSE_ListNode::SetData(void *d) {
    
    data = d;
}

/*
Return the previous node in the list.
*/      
LSE_ListNode* LSE_ListNode::GetPrev() const {
    
    return prev;
}

/*
Return the next node in the list.
*/
LSE_ListNode* LSE_ListNode::GetNext() const {
    
    return next;
}

/*
Return this nodes data.
*/
void* LSE_ListNode::GetData() const {
    
    return data;
}
