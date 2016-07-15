/** @file: testMap.cpp */

#include "Map.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    cout << "Passed all default tests" << endl;
    
    // MY TEST CASES
    
    Map m1;
    Map m2;
    Map m3;
    Map m4;
    Map m5;
    
    assert(m1.size() == 0);
    assert(m2.size() == 0);
    
    m1.insert("A", 5);
    assert(m1.size() == 1);
    assert(!m1.empty() && m2.empty());
    
    KeyType k2[10] = {"A", "B", "C", "D", "E", "A", "F", "C", "G", "D" };
    ValueType v2 = 10.5;
    for (int n = 0; n < 10; n++)
    {
        m2.insert(k2[n], v2);
        m4.insert(k2[n], v2);
    }
    
    m2 = m2;
    m4 = m4;
    
    // SIZE TEST
    assert(m2.size() == 7);
    assert(m4.size() != 6);

    
    // GET TEST
    assert(m2.get("A", v2) && v2 == 10.5);
    assert(m4.get("B", v2) && v2 == 10.5);
    
    // INSERT / UPDATE TEST
    assert(!m2.insert("A", 10.1));
    assert(m2.insertOrUpdate("A", 10.0));
    assert(!m2.update("H", 10.0));
    assert(m2.insertOrUpdate("H", v2));
    assert(m2.update("H", 10.0));
    
    assert(m4.insert("H", 10.0));
    assert(m4.insertOrUpdate("H", 5.0));
    
    // EMPTY / CONTAINS TEST
    assert(!m2.empty() && !m4.empty());
    assert(m4.contains("A") && m4.contains("H"));
    assert(m2.contains("A") && m2.contains("G"));
    
    // GET TEST 2
    int i = 0;
    int j = DEFAULT_MAX_ITEMS + 1;
    int l = -5;
    KeyType k3;
    ValueType v3;
    assert(m4.get(i, k3, v3));
    cerr << k3 << " " << v3 << endl;
    i++;
    assert(m4.get(i, k3, v3));
    cerr << k3 << " " << v3 << endl;
    assert(!m4.get(j, k3, v3));
    assert(!m4.get(l, k3, v3));
    
    // SWAP TEST
    ValueType v5;
    Map bag;
    bag.insert("Sock", 4);
    bag.insert("Shirt", 3);
    
    assert(bag.get("Sock", v5) && v5 == 4);
    assert(bag.contains("Shirt") && bag.size() == 2);
    
    Map BigBag;
    BigBag.swap(bag);
    
    assert(BigBag.size() == 2);
    assert(BigBag.contains("Sock") && BigBag.contains("Shirt"));
    
    KeyType k5[3] = {"Shorts", "Pants", "Shoes"};
    for (int i = 0; i < 3; i++)
        assert(BigBag.insert(k5[i], i+1));
    
    assert(BigBag.insert("Jacket", 1));
    
    KeyType k6[6] = {"Sock", "Shirt", "Shorts", "Pants", "Shoes", "Jacket"};
    ValueType v6;
    ValueType v7[6] = {4, 3, 1, 2, 3, 1};
    for (int i = 0; i < 5; i++)
    {
        assert(BigBag.get(i, k6[i], v6) && v6 == v7[i]);
    }
    
    cout << "Passed all basic tests." << endl;
 
} // end main
