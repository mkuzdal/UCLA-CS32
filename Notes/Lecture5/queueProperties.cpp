/** @file: queueProperties.cpp */

// Generally, the member functions of a queue include:

//  1.) create a new queue
//  2.) enqueue: put an item onto a queue
//  3.) dequeue: remove an item from the queue
//  4.) look at the top item of the queue
//  5.) check if it is empty
//  6.) how many items are in the queue

//  * Utilizes circular array (circular buffer)

/*
#include <queue>
#include <iostream>
using namespace std;

int main()
{
    queue<int> q;
    q.push(10);
    q.push(20);
    int k = q.front(); // should be 20
    cout << k << endl;
    q.pop();
    if(!q.empty())
        cout << q.size() << endl;
    
} // end main
*/