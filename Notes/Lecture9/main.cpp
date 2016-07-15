/** @file: main.cpp */

/**
 
Recursion:
Algorithms: Sorting using Recursion:
 
 Proposal:
 1. Split an unsorted pile into two smaller unsorted piles (only if # of items in the pile >= 2)
 2. Sort each small half of the stack
 3. Then merge the two stacks
 4. Each sort will perform steps 1-3.
 
 Technique:
 -  Recursion.
 
 The problem:
 -  The algorithm doesn't stop
 
 if the number of items in the pile > 1 <--- this is used to make sure the algorithm stops (i.e., the base case)
 {
    split the pile into two smaller unsorted piles
    sort (the left side)
    sort (the right side)
    merge the two sorted piles into one sorted pile
 }
 
**/

void merge(double a[], int first, int split, int last)
{
    
} // end merge

void sort(double a[], int b, int e)
{
    if (e - b >= 2)
    {
        int m = (e + b) / 2;
        sort(a, b, m);
        sort(a, m, e);
        merge(a, b, m, e);
        
    } // end if
    
} // end sort

int main()
{
    double arr[5];
    for (int i = 0; i < 5; i ++)
        arr[i] = 5-i;
    
    sort(arr, 0, 5);
}

/**
 
void solveTowers(int count, char src, char dst, char spare)
{
    if (count == 1)
        cout << "Move top disk from pole " << src << " to pole " << dst << endl;
    solveTowers(count - 1, src, spare, dst);
    solveTowers(1, src, dst, spare);
    solveTowers(count - 1, spare, dst, src);
}

**/

// Divide and Conquer Approach:
// Paths throughout the function have more than one call to itself
// Example: solveTowers, and sort

// The first and the rest approach:
// Split the problem into two pieces, one for the current problem, and one from the rest
// The last one and the rest variant.

bool contains(int a[], int n, int target)
{
    // if the array ever has a size of 0, then target is not in the array
    if (n <= 0) return false;
    
    // if the current point is target, the function is done
    if (a[0] == target) return true;
    
    // if the current point is not the target, check the rest of the array
    else return (contains(a+1, n-1, target));
    
} // end contains

