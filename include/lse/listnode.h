#ifndef LSE_LIST_NODE_H
#define LSE_LIST_NODE_H

namespace LSE {

/*
Forward declaration of list class to
allow for friend class relationship
of same template type.
*/
// TODO: determine if the list node class can be refactored to avoid this
class List;

/*
List node class.
Can store any type of data.
Note that whenever data is
stored in a node, a copy is
made in its own allocated
memory space.
*/
class ListNode {

    /*
    Force the user to add/remove nodes with List methods,
    as the SetPrev() and SetNext() methods are private to
    this class.
    */   
    friend class List;
    
    private:
        
        ListNode *prev, *next; // list element pointers
        void *data; // data pointer
    
    public:
        
        ListNode();
        ListNode(const ListNode& other);
        ListNode(void *d);
        
        ~ListNode();

        void SetData(void *d);
        void* GetData() const;

        ListNode* GetPrev() const;
        ListNode* GetNext() const;
};

}

#endif
