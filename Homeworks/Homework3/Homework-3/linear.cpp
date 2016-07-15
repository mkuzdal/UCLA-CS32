/** @file: linear.cpp */

#include <iostream>
using namespace std;


/** Returns true if the somePredicate function returns true for at
        least one of the array elements.
    @param: a: An array of doubles.
    @param: n: The number of entries in the array a.
    @return: True if the test was successful (i.e., somePredicate was true for
        some element in a). Otherwise return false. */
bool anyTrue(const double a[], int n)
{
    // Base case:
    if (n <= 0)
        return false;
    
    // if the current object of interest is true...
    if (somePredicate(a[n-1]))
        // return true
        return true;
    // otherwise, check the rest of the array to see if it is true
    else
        return anyTrue(a, n-1);
    
} // end anyTrue



/** Returns the number of elements in the array for which the somePredicate 
        function returns true.
    @param: a: An array of doubles.
    @param: n: The number of entries in the array a.
    @return: The number of elements in the array where somePredicate is true. */
int countTrue(const double a[], int n)
{
    // Base case:
    if (n <= 0)
        return 0;
    
    // if the current object of interest is true...
    if (somePredicate(a[n-1]))
        // add 1 to the count and check the rest.
        return 1 + countTrue(a, n-1);
    // otherwise, check the rest.
    else
        return countTrue(a, n-1);
    
}// end countTrue



/** Returns the subscript of the first element in the array for which 
        the somePredicate function returns true.  
    @param: a: An array of doubles.
    @param: n: The number of entries in the array a.
    @return: The index of the first instance where somePredicate is true.
        Otherwise returns -1. */
int firstTrue(const double a[], int n)
{
    // Base case:
    if (n <= 0)
        return -1;
    
    // if the current object of interest is true...
    if (somePredicate(a[n-1]))
        // check to see what the first true is for the rest of the array.
        // if it is -1, then that would indicate that the current item is the first
        if (firstTrue(a, n-1) == -1)
            // so return it.
            return n-1;
    
    return firstTrue(a, n-1);
    
} // end firstTrue



// Return the subscript of the smallest element in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    // Base cases:
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    
    // if the last item is less than the rest of the items...
    if (a[n-1] < a[indexOfMin(a, n-1)])
        // return the current index.
        return n-1;
    // otherwise, return the index of the minimum of the rest of the items.
    else
        return indexOfMin(a, n-1);
    
} // end indexOfMin



// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    // Base cases:
    if (n2 <= 0)
        return true;
    if (n1 <= 0)
        return false;
    
    // if a2 is also in a1...
    if (a1[n1-1] == a2[n2-1])
        // check to see if the next item of a2 is also in a1.
        return includes(a1, n1-1, a2, n2-1);
    // otherwise, check the rest of a1 for the element of a2.
    else
        return includes(a1, n1-1, a2, n2);
    
} // end includes
