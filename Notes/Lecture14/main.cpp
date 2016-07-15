/** @file: main.cpp */

// HASH FUNCTIONS

#include <string>

int main() {}

unsigned int hash(const std::string& s)
{
    unsigned int h = 2166136261;
    for (int i = 0; i != s.size(); i++)
    {
        h ^= s[i];
        h *= 16777619;
    } // end for
    
    return h;
} // end hash

// NOTE: the end product of hash will be large, so one should take the result, and perform % with the number of buckets in order to get a reasonable result based on the number of buckets in the hash. hash (key) % # buckets

// 10000 * year + 100 * month + day

// Load factor: # of items / # of buckets
// A bucket is a term used to describe a portion of the hash table with similar keys.

// We can dynamically allocate the array and keep track of the number of buckets. We can then compute the load factor, and if it crosses some threshhold we can allocate a bigger array to get more buckets

// BST: O(log N)

// Hash function takes the number and results in a number that is in the range of buckets, which is used to store that specific key and all other keys that hash to that bucket.

// Collisions occur when to keys map to the same bucket.

// The elements in the hash table array are arrays of vectors / lists / hand built linked lists.

// Load factor is the number of items in the hash table divided by the number of buckets.

// A brand new hash table has a load factor of 0.

// When an item is added to the hash table, increment the # of items.

// Bucket Nodes would store the key and the data for an element. Whereas the table would be an array of lists that hold bucket nodes.

// Or we can have the table hold pointers to bucket nodes where the element points to the head of a linked list.

// This style is known an as open hash table. A closed hash table is one in which the number of buckets is fixed and when a collision occurs, the other key will be placed in a different element in the array. The problem with closed hash tables is that large factors result in larger run times.

// Hash table with a fixed number of buckets:
// If we have 40000 students and 100000 buckets, we have a load factor of .4 and an average length of a linked list of .4. If we now have 10 times the students, we will result in an average linked list size of (10 * .4) or 4. This results in a time complexity of N; however, the constant of proportianality is very small. ( 1 / number of buckets assuming perfect distribution)

// Hash table with a maximum load factor:
// Dynamically allocate an array of some number of buckets.

// At some point we have 10000 buckets. The hash function gives a very large integer, and then we use some scheme to reduce the value of this integer. (Usually the number % the number of buckets)

// If we chose the load factor limit to be .7, if we ever exceed this load factor by adding in another item, we reallocate the memory (by doubling the number of buckets). This would cut the load factor in half.

// This can work by creating a new array of buckets (with twice the size), and then copy each of the previous keys into the new array with their new hash value.

// This results in O(1) constant time look up on average, but there are occassional spikes

// To solve this issue:
// 1.) We allocate a larger number of buckets.
// 2.) As we put intems into the new table, we put some number of items in the previous table (e.g., 5 items) into the new one.
// This is essentially doing a rehash, but incrementally, rather than all at once.

// This concept is known as an incremental rehashing scheme.

// Possible Hashes:
// Strings:

/*  int hash(std::string s)
    {
        int h = 0;
        for (int k = 0; k != s.size(); k++)
            h += s[k];
        return h;
    }
*/

// Problems with this hash:
// 1.) Multiple names hash to the same resulting in more hash
// 2.) Many buckets will go unused because most people's names are not large enough to be placed in the later end of the buckets.

// Possible Fix:
// Use multiplication instead of addition.
// However, must use insigned int. This would fix the issue where you may end up with a number so large, it overloads to a negative number.

// If h is almost always an even number, then h % buckets will almost always be an even number.
// This would result in many unused buckets.

// Possible Fix:
// Have the number of buckets in the hash function be a large prime number.
// A better solution is to pick a better hash function.

// FNV-1 Algorithm:

/*  unsigned int hash(std::string s)
    {
        unsigned int h = 2166136261U;
        for (int i = 0; i != s.size(); i++)
        {
            h += s[k];
            h *= 16777619;
        }
        return h;
    }
*/

// The hash function has to be deterministic. That is, it has to result in the same result for a given key every time.

// Must be uniformally distributed as best as possible.

// To look something up:
// 1.) We compute the hash function for the given key (should be cheap)
// 2.) We look up the bucket based on the result of the hashed key.
// 3.) We then search through the bucket to find the key.

// To make visiting each item faster, one could store a pointer to the next item as well as storing the data. This way, when one is to search through the entire list, rather than visiting each bucket, one could just follow the pointers that link the items.

// 8 more containers:

// 1.) unordered_set<type>
// 2.) unordered_mutliset<type> // allows duplicates
// 3.) unordered_map<type1, type 2>
// 4.) unordered_multimap<type1, type2> // allows duplicates
// Utilizes a hash table
// These are O(1) for insert / erase / search
// type requires == operator

// 5.) set<type>
// 6.) multiset<type> // allows duplicates
// 7.) map<type1, type2>
// 8.) multimap<type1, type2> // allows duplicates
// Utilizes a binary search tree
// There are O(log N) for insert / erase / search
// type requires < operator

// Each container allows for:
// - insert(type) // adds the item to the set
// - size() // returns the number of items in the set
// - find(type) // returns whether or not the item is in the list
// - count(type) // returns the number of time count occurs in the list
// - erase(type) // removes all items with the same value as the item
// - contains iterators:
// - .end() -> just past the end iterator
// - .begin() -> begining iterator

/** 
    std::unordered_set s;
    for (std::unordered_set::iterator<type> q = s.begin(); q != s.end(); s++)
        std::cout << *p << endl;
    
    std::cout << s.count(20) << std::endl;
**/

// Maps:
/** map<std::string, double> m;
                                        [Fred | 123.45]
                                        /              \
                                [Ethel | ...]     [Lucy | ...]
 
    pair<const std::string, double>
    Why const for the key part? So that way we can not modify its value, which would ruin 
    the integrity of the tree.
 
    map<std::string, double> m;
    m.insert(pair<std::string, double>("Fred", 123.45));
    m.insert(make_pair("Fred", 123.45));
    m["Fred"] = 123.45; (if Fred exists, its value will be overwritten, otherwise Fred will be 
    created)
    map<std::stding, double>::iterator p = m.find("Fred");
    if (p != m.end())
        m.erase(p);
    for (p = m.begin(); p != m.end(); p++)
    {
        *p.first (same as  p->first;)
        *p.second( sme a p->second;)
        cout << m.count("Fred");
        x.erase("Fred);
 
    }
    - when calling find , only one will be given not all pointers
 
    multimap<std::string, double> m;
    ... = m.equal_range
    for (map<str::string, double>iterator p = pr.first(); p!= pr.end(); p++)
        std::cout << p->second << std::endl;
 
    auto i = 17;
    auto x = sqrt(3.5+i);
 
    for (pair<const std::string, double> pr : m) // pr will be a copy of each pair in the map
        std:: cout << pr.first << " owes me $" << pr.second << std::endl;
    for ( auto& pr : m) // pr will be a reference to each pair in the map
        pr.second+=10;
 
**/

// Priority Queue:
// Using unsorted vector / list:
// Insertion: O(1)
// Remove item: O(N)
// Not that good.

// Sorted list: (with respect to priority)
// Remove item: O(1)
// Insertion: O(N)
// Still not very good.

// BST:
// Insertion: O(log N)
// Remove item: O(log N)
// Can do better

// Complete Binary Tree:
// Has every level filled except possibly the bottom one, and that one is filled from left-to-right

// New Data Sctructure:
// Heap.
// A complete binary tree where the value at each node is >= the the values in the subtrees of that node

//                                  90
//                                 /  \
//                               60    80
//                              / \   / \
//                            40  50 70  20
//                           / \
//                          10 30

// Removal:
// Remove the root value
// Then make the tree complete (i.e., put the 30 in the position of the 90)

//                                  30
//                                 /  \
//                               60    80
//                              / \   / \
//                            40  50 70  20
//                           /
//                          10

// Figure out where the new root will be (it has to be one of the root's children)
// In this case, it is the 80
// Then swap the two

//                                  80
//                                 /  \
//                               60    30
//                              / \   / \
//                            40  50 70  20
//                           /
//                          10

// Now fix the subtree where the 80 was swapped from. (recursion)

//                                  80
//                                 /  \
//                               60    70
//                              / \   / \
//                            40  50 30  20
//                           /
//                          10

// Done.

// To reiterate: Compare each root with its 2 children to find out which one will be the root.

// Removing is O(log N) w/ better constant than the BST

// Insertion:

// Inserting 65
// Step 1: Make the tree complete (i.e., put it in the bottom right-most item)

//                                  80
//                                 /  \
//                               60    70
//                              / \   / \
//                            40  50 30  20
//                           / \
//                          10 65

// Now instead of moving down, we will move up (i.e., we will compare the 65 to its parent)

//                                  80
//                                 /  \
//                               60    70
//                              / \   / \
//                            65  50 30  20
//                           / \
//                          10 40

//                                  80
//                                 /  \
//                               65    70
//                              / \   / \
//                            60  50 30  20
//                           / \
//                          10 40

// Done.

// Heaps in an array:
// For a given child at position i, we can see that integer divison between (i-1) / 2 gives us the parent if the array is sorted in descending order: e.g.,

// 80 | 65 | 70 | 60 | 50 | 30 | 20 | 10 | 40

// To find the children, we use 2j + 1 and 2j + 2. 2j+1 would result in the left child, and 2j+2 in the right. Provided that the result is still less than the size of the heap.

// Inserting: (Inserting 75)
// 1.) Insert the 75 into the final position into the array

// 80 | 65 | 70 | 60 | 50 | 30 | 20 | 10 | 40 | 75
// 0    1    2    3    4    5    6    7    8    9

// 2.) Using that ninth position, find its parent using (i-1) / 2
// (9 - 1) / 2 = 4.

// 3.) Compare the item in the 4th position to its children at 2j+1 and 2j+2.
// (2*4 + 1) , (2*4 + 2) = 9, 10
// Since 10 is invalid, only compare to 9.

// 4.) Since 75 is greater than 50, swap them
// 80 | 65 | 70 | 60 | 75 | 30 | 20 | 10 | 40 | 50
// 0    1    2    3    4    5    6    7    8    9

// 5.) Rinse and repeat.

// Removing -> Trickle down
// Inserting -> Trickle up

// Sorting a heap

// 6 | 3 | 5 | 9 | 2 | 10 |

// Heap-Sort:
// 1.) Make the array into a heap

// Start from the bottom
// - Take the 10, and compare it to the 5, its parent
// - 10 > 5 (10 is 5's only child) so swap the 10 and 5
// 6 | 3 | 10 | 9 | 2 | 5 |
// - Now finish trickling down the five. It has no children, so it is done
// - Then go to position 1 (position 2 which we already made a heap - 1)
// - 9 > 3, so swap the 9 and 3
// 6 | 9 | 10 | 3 | 2 | 5 |
// - Finish trickling down the 3. It has no children so it is done.
// Now decrement the count to 0 and repeat the process for the root.

// 2.) Now swap the top item from the heap (i.e., the 10), and re-heap the heap not including the 10
// | 10 | 9 | 6 | 3 | 2 | 5 | ==> | 5 | 9 | 6 | 3 | 2 | 10 |
//                          ^                         ^
//                       cut off                   cut off

// - Now repeat this process
// | 9 | 5 | 6 | 3 | 2 | 10 | ==> | 2 | 5 | 6 | 3 | 9 | 10 | ==> | 6 | 5 | 3 | 2 | 9 | 10 | ==>
//                     ^                          ^                              ^
//                  cut off                    cut off                        cut off

// | 2 | 5 | 3 | 6 | 9 | 10 | ==> | 5 | 2 | 3 | 6 | 9 | 10 | ==> | 3 | 2 | 5 | 6 | 9 | 10 | ==>
//             ^                              ^                          ^
//          cut off                        cut off                    cut off

// | 2 | 3 | 5 | 6 | 9 | 10 | <== Done;

// O(N log N)

// All order N log N sorts:
// Quick sort
// Merge sort
// Heap sort

// Quick sort and Heap sort require random access, Merge sort does not.
// However, Merge sort has the largest constant of proportionality, and it requires extra space.
// Quick sort also has a better constant of proportionality than heap sort.
// However, quick sorts worst case is O(N^2), Heap sorts worst case is also O(N log N)
// Intro sort is a marrage of quick sort and heap sort. It will use quick sort until it starts reaching O (N^2) in which case it will swap to using heap sort.

/*************************************************************************************************\

 Graphs:
 Edge: A connection between 2 nodes
 Directed Edge: A connection between 2 nodes where order matter
 
 Cyclic Graph: A graph in which a node may point to another node that points to it
 Acyclic Graph: A graph in which is not Cyclic
 
 Directed Graph: A graph in which direction of edge matters
 Directed Acyclic Graph: An acyclic graph where direction matters
 
 Topological Sort: Takes a directed graph and either tells you that there is a cycle in the graph, or gives an ordering in which that condition is satisfied.
 
 Graphs can be represented in a square Matrix known as an adjacency matrix where each element in the matrix contains a value (true or false) based on whether or not you can go from node a to node b
 
 An alternate way to store a graph is an adjaceny list. It is basically a list where each node contains a reference to each of the objects it has a directed edge to.
 
\*************************************************************************************************/
 





