#include <cstdlib>
#include "lse/defs.h"
#include "lse/list.h"
using namespace LSE;

/*
Initialize our list to empty/
*/
List::List() {
    
    this->size = 0;
    this->front = this->back = NULL;
}

/*
Create a copy of an existing list.
*/
List::List(const List& other) {
    
    this->size = other.size;
    this->front = this->back = NULL;
    
    for(ListNode *curr = other.GetFront(); curr != NULL; curr = curr->GetNext())
        this->PushBack(curr->GetData());
}

/*
Free all resources allocated by the list.
*/
List::~List() {
    
    this->Clear();
}

/*
Add new data onto the front of the list.
*/
void List::PushFront(void *data) {
    
    ListNode *node = new (std::nothrow) ListNode(data);
    if(node != NULL)
        this->PushFront(node);
    else
        LOG(LOG_LEVEL_ERROR, "Failed to allocate memory for new list node.\n");
}

/*
Add a pre-existing node to the front of the list.
*/
void List::PushFront(ListNode *node) {
    
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

        LOG(LOG_LEVEL_ERROR, "Cannot add NULL node to list.\n");
    }
}

/*
Insert new data somewhere between the list front and back.
*/
void List::Insert(void *data, int index) {
    
    if(index >= 0 && index < size) {
    
        ListNode *node = new (std::nothrow) ListNode(data);
        if(node != NULL)
            Insert(node, index);
        else
            LOG(LOG_LEVEL_ERROR, "Failed to allocate memory for new list node.\n");
    }
    else {

        LOG(LOG_LEVEL_ERROR, "List node insertion index out of range.\n");
    }
}

/*
Insert a pre-existing node somewhere between the list front and back.
*/
void List::Insert(ListNode *node, int index) {
    
    if(index >= 0 && index < size) {
    
        if(node != NULL) {

            ListNode *curr = front;
            for(int i = 0; i < index + 1; ++i, curr = curr->GetNext()) {
    
                if(i == index) {

                    ListNode *prev = curr->GetPrev();
                    ListNode *next = curr;
    
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

            LOG(LOG_LEVEL_ERROR, "Cannot add NULL node to list.\n");
        }
    }
    else {

        LOG(LOG_LEVEL_ERROR, "List node insertion index out of range.\n");
    }
}

/*
Add new data to the back of the list.
*/
void List::PushBack(void *data) {
    
    ListNode *node = new (std::nothrow) ListNode(data);
    if(node != NULL)
        PushBack(node);
    else
        LOG(LOG_LEVEL_ERROR, "Failed to allocate memory for new list node.\n");
}

/*
Add a pre-existing node to the back of the list.
*/
void List::PushBack(ListNode *node) {
    
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

        LOG(LOG_LEVEL_ERROR, "Cannot add NULL node to list.\n");
    }
}

/*
Return the first node of the list.
*/
ListNode* List::GetFront()const { 
    
    return front;
}

/*
Get the node at the given index.
*/
ListNode* List::GetNode(const int& index) const {
    
    ListNode *node = NULL;
    
    if(index >= 0 && index < size) {

        ListNode *curr = front;
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
ListNode* List::operator[](const int& index) const {
    
    return this->GetNode(index);
}

/*
Return the last node of the list.
*/
ListNode* List::GetBack() const {
    
    return back;
}
 
/*
Pop the first item off the list.
*/       
ListNode* List::PopFront() {

    ListNode *node = front;
    
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
ListNode* List::PopNode(int index) {
    
    ListNode *node = NULL;
    
    if(index >= 0 && index < size) {

        ListNode *curr = front;
        for(int i = 0; i < size && node == NULL; ++i, curr = curr->GetNext()) {
    
            if(i == index) {

                node = curr;
    
                ListNode *prev = node->GetPrev();
                ListNode *next = node->GetNext();

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
void List::PopNode(ListNode *node) {
    
    if(node != NULL) {

        ListNode *prev = node->GetPrev();
        ListNode *next = node->GetNext();

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
ListNode* List::PopBack() {
    
    ListNode *node = back;
    
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
int List::Size() {
    
    return size;
}

/*
Empty the list.
*/
void List::Clear() {
    
    while(size > 0)
        delete PopBack();
}
