#ifndef LSE_LIST_NODE_H
#define LSE_LIST_NODE_H

namespace LSE {

/*
Forward declaration of list class to
allow for friend class relationship
of same template type.
*/
// TODO: determine if the list node class can be refactored to avoid this
class LSE_List;

/*
List node class.
Can store any type of data.
Note that whenever data is
stored in a node, a copy is
made in its own allocated
memory space.
*/
class LSE_ListNode {

    /*
    Force the user to add/remove nodes with LSE_List methods,
    as the SetPrev() and SetNext() methods are private to
    this class.
    */   
    friend class LSE_List;
    
    private:
        
        LSE_ListNode *prev, *next; // list element pointers
        void *data; // data pointer
    
    public:
        
        LSE_ListNode();
        LSE_ListNode(const LSE_ListNode& other);
        LSE_ListNode(void *d);
        
        ~LSE_ListNode();

        void SetData(void *d);
        void* GetData() const;

        LSE_ListNode* GetPrev() const;
        LSE_ListNode* GetNext() const;
};

}

#endif
