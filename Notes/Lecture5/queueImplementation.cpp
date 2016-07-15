/** @file: queueImplementation.cpp */

#include <cassert>
#include <iostream>

const int MAX_SIZE = 100;

class intQueue
{
private:
    int m_stack[MAX_SIZE];
    int m_size;
    int m_frontI;
    int m_backI;
    
public:
    intQueue();
    int size() const { return m_size; }
    bool isEmpty() const { return (m_size == 0); }
    int top() const { return m_stack[m_frontI]; }
    
    void enqueue(const int& n);
    int dequeue();
}; // end intQueue

intQueue::intQueue()
:m_size(0), m_frontI(0), m_backI(0)
{
} // end default constructor

void intQueue::enqueue(const int& n)
{
    m_stack[m_backI] = n;
    m_size++;
    m_backI = (m_backI+1) % MAX_SIZE;
} // end enqueue

int intQueue::dequeue()
{
    int toReturn = m_stack[m_frontI];
    m_size--;
    m_frontI = (m_frontI+1) % MAX_SIZE;
    return toReturn;
    
} // end dequeue