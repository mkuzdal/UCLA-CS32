/** @file Main.cpp */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

//  Types of sort:
//  Selection sort  =>  O(N^2)
//  Goes through the sequence, finds the lowest one, then swaps it with the first one
//
//  Bubble sort     =>  O(N^2)
//  Better than selection sort by a coefficient
//
//  Insertion sort  =>  O(N^2)
//  Search through the array and shift objects over as other items need to be fit into place
//  Better than both bubble sort and selection sort
//
//  Shell sort      =>  O(N^1.25~)
//  Break up the problem into smaller insertion sorts
//
//  Merge sort      =>  O(N log N)
//  Tends to work best with more storage for supplementary arrays
//
//  Quick sort      =>  O(N log N)
//  Sort the stack into two piles where everything in the first pile comes before everything in the second pile, then merge the piles. Pick a pivot point, and sort the array so that everything < pivot comes before the pivot, and everything > pivot comes after.

/*  Go through the array until you find something greater than the pivot value starting from the beginning. Do the same going from the end to find something less than the pivot value, then swap them. The best pivot number is generally the median, however sometimes this is hard to find, so instead we can use any number within the number range (i.e., pick the (final - initial / 2) + initial.) or a[n/2] */

//  On average quick sort is O(N log N) with a better constant than merge sort; however, on the worst case, quick sort can become O(N^2)
//  One adaptation was to choose the median of the first middle last
//  Another was to sort each half until N < 10, then using an insertion sort to sort each < 10 items.

//  Intro sort      => avg: O(N log N)  worst: slightly worse O(N log N)
//  Uses quick sort until the recursive calls reach a certain depth, and when this is the case, it will stop using quick sort and instead use merge sort

/** Data Structures */

//  Trees Terminology:
//  Each object is a node
//  Two nodes are connected by an edge
//  Any way to go from one node to another is a path
//  Root is the initial node where every object branches off of
//  For a tree to exist, there has to be a single unique path to get from a node to the root
//  Leaf nodes are objects with no child objects (i.e., they reside at the bottom of the tree)
//  Interior nodes have at least 1 child object
//  Depth of a node is a measure of how into the tree a node is(e.g., the root node has a depth of 0, the roots children have a depth of 1, etc...)
//  Example:

struct Node
{
    std::string data;
    std::vector<Node*> children;
    Node* parent;
}; // end Node


int countNodesAux(Node* t)
{
    int total = 1;
    for (int i= 0; i < t->children.size(); i++)
        total+= countNodesAux(t->children[i]);
    return total;
} // end countNodesAux

int countNodes(Node* t)
{
    // Base case:
    if(t == nullptr)
        return 0;
    
    return countNodesAux(t);
} // end countNodes


// Prints all the data in the tree in the order in which they appear in the tree.
// If one were to switch the order of the for loop and the cout statement, the order would appear in reverse.
// Post Order: The operations are done after the children's operations are done.
void printTreeAux(const Node* t)
{
    std::cout << t->data << std::endl;
    for (int i = 0; i < t->children.size(); i++)
        printTreeAux(t->children[i]);
} // end printTreeAux

void printTree1(const Node* t)
{
    // Base case:
    if (t == nullptr)
        return;

    return printTreeAux(t);
} // end printTree


void printTreeAux(const Node* t, std::string header)
{
    std::cout << header << t->data << std::endl;
    for (int i = 0; i < t->children.size(); i++)
        printTreeAux(t->children[i], header + t->data);
} // end printTreeAux

void printTree2(const Node* t)
{
    // Base case:
    if (t == nullptr)
        return;
    
    return printTreeAux(t, "");
} // end printTree2


void printTreeAux(const Node* t, int depth)
{
    std::string temp(2*depth, ' ');
    std::cout << temp << t->data << std::endl;
    for (int i = 0; i < t->children.size(); i++)
        printTreeAux(t->children[i], depth + 1);
} // end printTreeAux

void printTree3(const Node* t)
{
    // Base case:
    if (t == nullptr)
        return;
    
    return printTreeAux(t, 0);
} // end printTree3

/** Binary tree:
        Either empty, or it's a node with a left binary tree as a subtree and a right binary tree as a subtree
        Example: Family tree:
        struct Node
        {
            std::string data;
            Node* oldestChild
            Node* nextYoungerSibling // Note: Max size of 2 (no more than 2 subtree's)
        }; // end Node
 
                                                    Lisa
                                                    /  \
                                                Bart    Marge
                                                /  \    /   \
                                               0 Homer Maggie Patty
                                                 / \    / \    / \
                                                0  0   0  0   0   Selma
                                                                  /  \
                                                                 0    0
        This tree is arranged alphabetically (i.e., everyone on the right's name is higher alhpabetically than the parent node and vice verse for the left)
 
        void printTree(const Node* t)
        {
            if (t != nullptr)
            {
                printTree(t->left);
                cout << t-> data << endl;
                printTree(t->right);
            } // end if
        } // end printTree
 
        How to add objects to a tree:
        Start with the root and see if it is equal to the root data. If it is, do nothing.
        If it is greater than the root, go to the right; otherwise go left.
        Repeat this process for the children of each parent
 
        The first thing read into the tree must have been lise.
        The second must have been either Bart of Marge (lets say it was Marge)
        Then the third must have been Bard, Maggie, or Patty (lets say it was Maggie)
        The the next was Bart or Patty
        etc...
 
        Binary trees are generally O(log N)
        However, worst case they are O(N)
        This can be caused by terrible unbalanced trees
        (for example, if all of the data comes in alphabetically)
 
        How to delete objects from a tree:
        To remove a leaf node, all we need to do is delete the node and replace the parent node with a nullptr
        To remove a node with only one child, all we need to do is to put the parents pointer to the deleted nodes child node (e.g., if we wanted
        to delete Bart, we would have Lisa's left pointer point to Bart's child pointer (Homer))
        If we want to delete a node where both the left and the right pointers are not null, the problem is more complicated
        Example: Delete Lisa
        promote Homer to the root node because Homer is 1 position alphabetically less than Lisa
        Then fix Homer's child nodes
        The end result:
        Homer points to Bart on the left and Marge on the right.
        Then replace Homer's child nodes by having them pointed to be Bart's right pointer
**/


