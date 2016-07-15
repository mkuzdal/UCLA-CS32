/** @file: main.cpp */

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


bool isNegative( int k )
{
    return (k < 0);
} // end isNegative


///////////////////////////////////////////////////////////////////////////////////////////////////


double blah(double x)
{
    return x*x;
} // end f

// writing a function that takes in a function
double integrate(const double& x, const double& y, const int& steps, double f(double))
{
    // ... do something...
    double Y = f(x);
    return Y;
} // end integrate


///////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
T* Find(T* b, T* e, const T& target)
{
    for ( ; b != e; b++)
        if(*b == target)
            break;
    return b;
} // end find


// This find will work with many different types; however,  this will not work with string
// because when passed in a string literal, the compiler recognizes that as a c-string, not a
// c++ string. To fix:

template<typename iter, typename T>
iter Find(iter b, iter e, const T& target)
{
    for ( ; b != e; b++)
        if (*b == target)
            break;
    return b;
} // end find


///////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    
    list<string> ls;
    list<string>::iterator q = Find(ls.begin(), ls.end(), "Fred");
    if (q == ls.end())
        // ... not found ...
        ;
    
    vector<int> vi;
    vector<int>::iterator r = Find(vi.begin(), vi.begin()+5, 42);
    if (r == vi.begin()+5)
        // ... not found ...
        ;
    
    double I = integrate(10.4, 15.4, 12, blah);
    
    
    vector<int>::iterator p = find_if(vi.begin(), vi.end(), isNegative);
    if ( p == vi .end())
        // ... not found ...
        ;
    
    // sort(vi.begin(), vi.end(), isGreater);
    // is greater should return true if the first is greater than the second.
    // e.g., bool isGreater(int i, int j) { return i > j; }
    // if the function passed returns true, the first object will come before the second.
} // end main


///////////////////////////////////////////////////////////////////////////////////////////////////


// A function is O(N)if the highest order term is N^1;
// Likewise O(N^2) for quadratic terms
// O(N) is also known as a linear time algorithm. (i.e., double N, double the time it takes)
// O(1) is a constant time algorithm
// O(log N) is a logarithmic time alogirthm
// O(N^2) Quadratic time algoirthm


