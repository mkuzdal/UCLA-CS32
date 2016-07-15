/** @file: STL.cpp */

/**     #include <stack>
        std::stack<type> stack name
        (e.g., stack<int> s)
        functions:
        push(arg type): adds a number to the top of the stack
        empty(): returns whether or not the stack is empty
        pop(): removes the top entry of the stack
        top(): returns the top entry of the stack
        size(): returns the number of items in the stack
        **/

/**     #include <queue>
        std::queue<type> queue name
        (e.g., queue<int> q)
        functions:
        push(arg type): adds a number to the end of the queue
        pop(): ...
        ...
        **/

/**     #include <vector>
        std::vector<type> vector name
        (e.g., vector<int> v)
        functions:
        push_back(arg type): puts an item onto the end of the vector
        size(): returns the size of the vector
        front(): returns the first object in the vector
        back(): returns the object in the end of the vector
        v[n]: returns the n-1th item in the vector
        pop_back(): removes the last item in the vector
        at(n) = K: sets the item at the index n to K.
        v.insert(arg iterator, arg type): inserts the number type into the position pointed by the iterator and returns an iterator pointing to what was just inserted.
        vector<double> v2(10)
        (i.e., the size is 10 with each item 0.0 (calls the default constructor for each item))
        vector<string> v3(20, "Hello")
        (i.e., the size is 20 with each item "Hello")
        int a[5] = {10,20,30,40,50}
        vector<int> v4(a, a+5)
        (i.e., the size is 5 with 10, 20, 30, 40, 50 as the items)
        **/

/**     #include <list>
        std::list<type> list name
        (e.g., list<int> l)
        functions:
        push_back(arg type): puts an item onto the end of the list
        push_front(arg type): puts an item onto the front of the list
        size(): returns the size of the list
        front(): returns the first item in the list
        back(): returns the item at the back of the list
        pop_front(): removes the first item from the list
        pop_back(): removes the last item from the list
        begin(): returns an iterator to the first item in the list
        end(): returns an iterator to just after the last item in the list
        insert(arg iterator, arg type): inserts the number type into the position pointed by the iterator and returns an iterator pointing to what was just inserted.
        erase(arg iterator): removes the iterator and returns an iterator pointing right after it.
        (i.e., an iterator is a pointer to a node in the linked list)
        list<double> v2(10)
        (i.e., the size is 10 with each item 0.0)
        list<string> v3(20, "Hello")
        (i.e., the size is 20 with each item "Hello")
        vector<string> v5(l3.begin(), l3.end())
        (i.e., creates a vector whose size is that of l3, and whose items are the same as l3)
 
        **/

/**     Key Points:
        Vectors can not push front.
        Why? Vectors use dynamically allocated arrays, so to put an item to the front of the vector, the entire array has to be shifted.
        Lists can push front because they use doubly linked lists.
 
        Iterator's act as pointers to nodes.
        If I is an iterator for a list of ints of size 10, and it points to the first item in the list...
        Then I++ would make I point to the next item in the list.
        Likewise for I--
 
        Iterators to linked lists can only be incremented and decremented (i.e., Iterator i += 2 would not compile)
        However, for Iterators to vectors, this can be done.
 
        **/

/**     Algorithms: (find, search, remove, etc)
        Arguments are generally:
        A pointer / Iterator to the beginning position of the array
        A pointer / Iterator to the end + 1 position of the array
        The topic of interest
        Returns are generally:
        A pointer / Iterator to the position of interest.
        or
        A pointer / Iterator to the last position + 1 of the array (incase of failure)
        **/

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    std::vector<int> v;
    v.push_back(10);
    cout << v.size() << endl;
    cout << v[0] << endl;
    
    v.push_back(20);
    v.push_back(40);
    
    cout << v.back() << endl;
    v.at(2) = 5;
    cout << v.back() << endl;
    
    
    std::list<int> l1;
    l1.push_back(20);
    l1.push_back(30);
    l1.push_front(10);
    
    for(list<int>::iterator i = l1.begin(); i != l1.end(); i++)
    {
        cout << *i << endl;
    } // end for
    
    list<int>::iterator i;
    
    
} // end main


