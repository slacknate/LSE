#include <cstdlib>
#include "lse/defs.h"
#include "lse/list.h"

/*
Initialize our list to empty/
*/
LSE_List::LSE_List() {
    
    this->size = 0;
    this->front = this->back = NULL;
}

/*
Create a copy of an existing list.
*/
LSE_List::LSE_List(const LSE_List& other) {
    
    this->size = other.size;
    this->front = this->back = NULL;
    
    for(LSE_ListNode *curr = other.GetFront(); curr != NULL; curr = curr->GetNext())
        this->PushBack(curr->GetData());
}

/*
Free all resources allocated by the list.
*/
LSE_List::~LSE_List() {
    
    this->Clear();
}

/*
Add new data onto the front of the list.
*/
void LSE_List::PushFront(void *data) {
    
    LSE_ListNode *node = new (std::nothrow) LSE_ListNode(data);
    if(node != NULL)
        this->PushFront(node);
    else
        LSE_ERROR_LOG("Failed to allocate memory for new list node.\n");
}

/*
Add a pre-existing node to the front of the list.
*/
void LSE_List::PushFront(LSE_ListNode *node) {
    
    if(node != NULL) {

        if(front == NULL) {
    
            node->prev = NULL;
            node->next = NULL;
            front = back = node;
        }
        else {
    
            front->prev = node;
            node->prev = NULL;
            node->next = front;
            front = node;
        }

        ++size;
    }
    else {

        LSE_ERROR_LOG("Cannot add NULL node to list.\n");
    }
}

/*
Insert new data somewhere between the list front and back.
*/
void LSE_List::Insert(void *data, int index) {
    
    if(index >= 0 && index < size) {
    
        LSE_ListNode *node = new (std::nothrow) LSE_ListNode(data);
        if(node != NULL)
            Insert(node, index);
        else
            LSE_ERROR_LOG("Failed to allocate memory for new list node.\n");
    }
    else {

        LSE_ERROR_LOG("List node insertion index out of range.\n");
    }
}

/*
Insert a pre-existing node somewhere between the list front and back.
*/
void LSE_List::Insert(LSE_ListNode *node, int index) {
    
    if(index >= 0 && index < size) {
    
        if(node != NULL) {

            LSE_ListNode *curr = front;
            for(int i = 0; i < index + 1; ++i, curr = curr->GetNext()) {
    
                if(i == index) {

                    LSE_ListNode *prev = curr->GetPrev();
                    LSE_ListNode *next = curr;
    
                    if(prev)
                        prev->next = node;
    
                    node->prev = prev;
                    node->next = next;
    
                    if(next)
                        next->prev = node;
                }
            }

            ++size;
        }
        else {

            LSE_ERROR_LOG("Cannot add NULL node to list.\n");
        }
    }
    else {

        LSE_ERROR_LOG("List node insertion index out of range.\n");
    }
}

/*
Add new data to the back of the list.
*/
void LSE_List::PushBack(void *data) {
    
    LSE_ListNode *node = new (std::nothrow) LSE_ListNode(data);
    if(node != NULL)
        PushBack(node);
    else
        LSE_ERROR_LOG("Failed to allocate memory for new list node.\n");
}

/*
Add a pre-existing node to the back of the list.
*/
void LSE_List::PushBack(LSE_ListNode *node) {
    
    if(node != NULL) {
    
        if(back == NULL) {
    
            node->prev = NULL;
            node->next = NULL;
            back = front = node;
        }
        else {
    
            node->prev = back;
            node->next = NULL;
            back->next = node;
            back = node;
        }

        ++size;
    }
    else {

        LSE_ERROR_LOG("Cannot add NULL node to list.\n");
    }
}

/*
Return the first node of the list.
*/
LSE_ListNode* LSE_List::GetFront()const { 
    
    return front;
}

/*
Get the node at the given index.
*/
LSE_ListNode* LSE_List::GetNode(const int& index) const {
    
    LSE_ListNode *node = NULL;
    
    if(index >= 0 && index < size) {

        LSE_ListNode *curr = front;
        for(int i = 0; i < size && node == NULL; ++i, curr = curr->GetNext()) {
    
            if(i == index)
                node = curr;
        }
    }
    
    return node;
}

/*
Get the node at the given index.
*/
LSE_ListNode* LSE_List::operator[](const int& index) const {
    
    return this->GetNode(index);
}

/*
Return the last node of the list.
*/
LSE_ListNode* LSE_List::GetBack() const {
    
    return back;
}
 
/*
Pop the first item off the list.
*/       
LSE_ListNode* LSE_List::PopFront() {

    LSE_ListNode *node = front;
    
    if(front != NULL) {

        --size;
        front = front->GetNext();
        front->prev = NULL;
        
        if(node == back)
            back = front;
    }
    
    return node;
}

/*
Pop the item with the given index off the list.
*/
LSE_ListNode* LSE_List::PopNode(int index) {
    
    LSE_ListNode *node = NULL;
    
    if(index >= 0 && index < size) {

        LSE_ListNode *curr = front;
        for(int i = 0; i < size && node == NULL; ++i, curr = curr->GetNext()) {
    
            if(i == index) {

                node = curr;
    
                LSE_ListNode *prev = node->GetPrev();
                LSE_ListNode *next = node->GetNext();

                if(prev)
                    prev->next = next;
                if(next)
                    next->prev = prev;
            }
        }

        --size;

        if(node == front) {
    
            front = front->GetNext();
            front->prev = NULL;
        }
        if(node == back) {
    
            back = back->GetPrev();
            back->next = NULL;
        }
    }
    
    return node;
}

/*
Pop the given item off the list.
*/
void LSE_List::PopNode(LSE_ListNode *node) {
    
    if(node != NULL) {

        LSE_ListNode *prev = node->GetPrev();
        LSE_ListNode *next = node->GetNext();

        if(prev)
            prev->next = next;
        if(next)
            next->prev = prev;

        if(node == front) {
    
            front = front->GetNext();
            front->prev = NULL;
        }
        if(node == back) {
    
            back = back->GetPrev();
            back->next = NULL;
        }

        --size;
    }
}

/*
Pop the last item off the list.
*/
LSE_ListNode* LSE_List::PopBack() {
    
    LSE_ListNode *node = back;
    
    if(back != NULL) {

        --size;
        back = back->GetPrev();

        if(back != NULL)
            back->next = NULL;
            
        if(node == front)
            front = back;
    }
    
    return node;
}

/*
Return the size of the list.
*/
int LSE_List::Size() {
    
    return size;
}

/*
Empty the list.
*/
void LSE_List::Clear() {
    
    while(size > 0)
        delete PopBack();
}
