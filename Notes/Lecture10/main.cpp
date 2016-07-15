/** @file: main.cpp */

#include <iostream>
using namespace std;


struct Node
{
    int data;
    Node* next;
}; // end Node


//  Types of recursive solutions:
//  1.) Divide and Conquer
//  2.) The first and the rest
//  3.) The last and the rest


bool contains(int a[], int n, int target)
{
    if (n <= 0)
        return false;
    
    if (a[0] == target)
        return true;
    
    return contains(a+1, n-1, target);
} // end contains


bool contains(Node* p, int target)
{
    if (p == nullptr)
        return false;
    
    if (p->data == target)
        return true;
    
    return contains(p->next, target);
} // end contains


/**
bool solve(pos, end)
{
    if (pos == end)
        return true;
 
    mark the current position
    for each direction from the current position:
    {
        if I can move in that direction, and I haven't been there before:
        {
            if (solve(pos + direction, end)
                return true
        }
    }
    return false
} **/


/*************************************************************************\
                            TEMPLATE FUNCTIONS
\*************************************************************************/


int minimum(int a, int b)
{
    if (a < b)
        return a;
    
    return b;
} // end minimum

double minimum(double a, double b)
{
    if (a < b)
        return a;
    
    return b;
} // end minimum


//  Two Functions with the same text that do different things.
//  Fix:

template<typename T>    // tells the compiler that this is a template function for an arbritrary
                        // type 'T'
T minimum(T a, T b)
{
    if ( a < b)
        return a;
    
    return b;
} // end minimum

// Template argument deduction: The process by which the compiler deduce what type T represents and therefore determines which version of minimum to use
// This process is call instantiating the template.
// If a function is called with no exact match (i.e., a function who's parameter is a reference to a constant string, but you insert a string)
// Widening Conversion: convert from a smaller type to a larger type (e.g., converts characters to integers); (e.g., a float to a double); etc...
// Class base conversion (e.g., c string to string)


//  1. Math the template
//  2. The instantiated template compiles
//  3. The instantiated template must do what you want


// WONT COMPILE:
/*
 int k;
 ... minimum(k, 'c');
*/


// Both k (an int) and 'c' (a character) can not be converted into template


// Exceptions can be created by overloading the functions
// This will overload the template function for minimum
char* minimum(char* a, char* b)
{
    if (strcmp(a,b) < 0)
        return a;
    
    return b;
} // minimum


template<typename T>
T sum(T a[], int n)
{
    T total = T();
    for (int k = 0; k < n; k++)
        total += a[k];
    
    return total;
} // end sum

template<typename T>
class Stack
{
public:
    Stack();
    void push(const T& a);
private:
    T m_data[100];
    int m_size;
};

template<typename T>
Stack<T>::Stack()
{
    m_size = 0;
}

template<typename T>
void Stack<T>::push(const T& a)
{
    return;
}
// ...




