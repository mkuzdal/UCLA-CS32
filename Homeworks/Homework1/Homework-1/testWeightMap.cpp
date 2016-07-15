/** @file: testWeightMap.cpp */

#include "WeightMap.h"

#include <iostream>
#include <cassert>
using namespace std;

void f(WeightMap w)
{
    w.enroll("Sally", 150.0);
    w.print();
}

int main()
{
    WeightMap w1;
    WeightMap w2;
    
    assert(w1.enroll("Jim", 200.0));
    assert(w1.enroll("Sarah", 170.0));
    
    w1.print(); // Jim 200 \n Sarah 170
    
    w2 = w1;
    
    w2.print(); // Jim 200 \n Sarah 170
    w1.print(); // Jim 200 \n Sarah 170
    
    f(w1); // Jim 200 \n Sarah 170 \n Sally 150
    
    w1.print(); // Jim 200 \n Sarah 170
    
    w1 = w1;
    w2 = w2;

    assert(w1.size() == 2);
    assert(w2.enroll("John", 140.0));
    assert(w2.size() == 3);
    
    assert(w1.adjustWeight("Jim", 10.0) && w1.weight("Jim") == 210.0);
    assert(w1.weight("John") == -1);
    
    assert(!w2.adjustWeight("John", -200.0) && w2.weight("John") == 140.0);
    
    assert(!w1.adjustWeight("John", 20.0));
    
    WeightMap w3(w2);
    
    assert(!w3.enroll("Carol", -200));
    assert(w3.size() == w2.size());
    
    w3.print(); // Jim 200 \n Sarah 170 \n John 140
    
    cout << "Passed all test." << endl;

} // end main
