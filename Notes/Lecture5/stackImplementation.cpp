/** @file: stackImplementation.cpp */

#include <cassert>
#include <iostream>

const int MAX_SIZE = 100;

class intStack
{
private:
    int m_stack[MAX_SIZE];
    int m_size;
public:
    intStack():m_size(0) {}
    int size() const { return m_size; } // end size
    bool isEmpty() const { return (m_size == 0); } // end isEmpty
    int peek() const;
    void push(int n);
    int pop();
    
}; // end intStack

int intStack::peek() const
{
    assert(!this->isEmpty());
    return m_stack[m_size];
    
} // end peek

void intStack::push(int n)
{
    m_stack[m_size] = n;
    m_size++;
    
} // end push

int intStack::pop()
{
    assert(!this->isEmpty());
    m_size--;
    return m_stack[m_size+1];
} // end pop


