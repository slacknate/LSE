#ifndef LSE_LIST_H
#define LSE_LIST_H

#include "lse/listnode.h"

namespace LSE {

/*

*/
class List {
    
    private:
        
        int size; // size of the list
        ListNode *front, *back; // list pointers
        
    public:
        
        List();
        List(const List& other);
        
        ~List();
        
        void PushFront(void *data);
        void PushFront(ListNode *node);
        
        void Insert(void *data, int index);
        void Insert(ListNode *node, int index);
        
        void PushBack(void *data);
        void PushBack(ListNode *node);
        
        ListNode* GetFront() const;
        ListNode* GetNode(const int& index) const;
        ListNode* operator[](const int& index) const;
        ListNode* GetBack() const;
        
        ListNode* PopFront();
        ListNode* PopNode(int index);
        void PopNode(ListNode *node);
        ListNode* PopBack();
        
        int Size();
        void Clear();
};

}

#endif
