/** @file: linkedList.h */

#ifndef LINKED_LIST_INCLUDED
#define LINKED_LIST_INCLUDED

class linkedList
{
private:
    
    struct node
    {
        int m_data;
        node* m_next;
    }; // end node
    
    node* m_head;
    int m_size;
    
public:
    
    void display() const;
    bool addFive(int key);
    bool insert(int key);
    bool remove(int key);
    
};




#endif /* LINKED_LIST_INCLUDED */
