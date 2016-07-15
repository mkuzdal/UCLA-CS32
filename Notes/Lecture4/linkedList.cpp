/** @file: linkedList.cpp */

#include "linkedList.h"

#include <iostream>
using namespace std;


void linkedList::display() const
{
    // WRONG!
    /* while (m_head != nullptr)
    {
        cout << m_head->m_data << endl;
        m_head = m_head->m_next;
    } */
    
    // BETTER
    /* node* N = m_head;
    while (N != nullptr)
    {
        cout << N->m_data << endl;
        N = N->m_next;
    } */
    
    for (node* p = m_head; p != nullptr; p = p->m_next)
        cout << p->m_data << endl;
    
    // Any time you write p->, make sure p has been previously
    // given a value and that p is not the null ptr.
    
    
} // end display

bool linkedList::addFive(int key)
{
    node* p;
    for (p = m_head; p != nullptr && p->m_data != key; p = p->m_next)
        ;
    
    if (p == nullptr)
        return false;
    
    p->m_data += 5;
    return true;
    
} // end addFive

bool linkedList::insert(int key)
{
    node* newN = new node;
    newN->m_data = key;
    newN->m_next = m_head;
    m_head = newN;
    return true;
    
    // Dont do things in the wrong order.
    // Advice: set values in new node first.
    
} // end insert

bool linkedList::remove(int key)
{
    node* current;
    node* prev = nullptr;
    for (current = m_head; current != nullptr && current->m_data != key; prev = current, current = current->m_next)
        ;
    
    if (current == nullptr)
        return false;
    
    if (prev != nullptr)
        prev->m_next = current->m_next;
    else
        m_head = m_head->m_next;
    delete current;
    return true;
    
    // Scenarios to consider:
    // 1.   General case
    // 2.   Empty list
    // 3.   Single item list that does contain the key
    // 4.   Single item list that does not contain the key
    // 5.   When the item is at the beginning of the list
    // 6.   When the item is at the very end of the list
    
} // end remove











