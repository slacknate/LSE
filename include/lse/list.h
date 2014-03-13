#ifndef LSE_LIST_H
#define LSE_LIST_H

#include "lse/listnode.h"

/*

*/
class LSE_List {
    
    private:
        
        int size; // size of the list
        LSE_ListNode *front, *back; // list pointers
        
    public:
        
        LSE_List();
        LSE_List(const LSE_List& other);
        
        ~LSE_List();
        
        void PushFront(void *data);
        void PushFront(LSE_ListNode *node);
        
        void Insert(void *data, int index);
        void Insert(LSE_ListNode *node, int index);
        
        void PushBack(void *data);
        void PushBack(LSE_ListNode *node);
        
        LSE_ListNode* GetFront() const;
        LSE_ListNode* GetNode(const int& index) const;
        LSE_ListNode* operator[](const int& index) const;
        LSE_ListNode* GetBack() const;
        
        LSE_ListNode* PopFront();
        LSE_ListNode* PopNode(int index);
        void PopNode(LSE_ListNode *node);
        LSE_ListNode* PopBack();
        
        int Size();
        void Clear();
};

#endif
