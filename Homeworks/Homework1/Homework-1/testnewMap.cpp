/** @file: testmewMap.cpp */

#include "newMap.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    // DEFAULT TEST CASES
    
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = { "abc", "cde", "efg", "hij", "lmn", "opq" };
    ValueType v  = 12.1;
    
    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));
    
    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));
    
    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));
    
    cout << "Passed all default tests." << endl;
    
    // MY TEST CASES
    
    Map m1(0);
    Map m2;
    Map m3(100);
    Map m4(3);
    Map m5(10);
    
    assert(m1.size() == 0);
    assert(m2.size() == 0);
    assert(m3.size() == 0);
    
    m1.insert("A", 5);
    assert(m1.size() == 0);
    assert(m1.empty() && m2.empty());
    
    KeyType k2[10] = {"A", "B", "C", "D", "E", "A", "F", "C", "G", "D" };
    ValueType v2 = 10.5;
    for (int n = 0; n < 10; n++)
    {
        m2.insert(k2[n], v2);
        m4.insert(k2[n], v2);
        m5.insert(k2[n], v2);
    }
    
    m2 = m2;
    m4 = m4;
    m5 = m5;
    
    // SIZE TEST
    assert(m2.size() == 7);
    assert(m4.size() == 3);
    assert(m5.size() == 7);
    
    // GET TEST
    assert(m2.get("A", v2));
    assert(m4.get("A", v2));
    assert(m5.get("A", v2));
    assert(!m4.get("E", v2));
    
    // INSERT / UPDATE TEST
    assert(!m2.insert("A", 10.1));
    assert(m2.insertOrUpdate("A", 10.0));
    assert(!m2.update("H", 10.0));
    assert(m2.insertOrUpdate("H", v2));
    assert(m2.update("H", 10.0));
    
    assert(!m4.insert("H", 10.0));
    assert(!m4.insertOrUpdate("H", 10.0));
    
    // EMPTY / CONTAINS TEST
    assert(!m2.empty() && !m4.empty());
    assert(m4.contains("A") && !m4.contains("H"));
    assert(m2.contains("A") && m2.contains("G"));
    
    // GET TEST 2
    int i = 0;
    int j = 5;
    KeyType k3;
    ValueType v3;
    assert(m4.get(i, k3, v3));
    cerr << k3 << " " << v3 << endl;
    i++;
    assert(m4.get(i, k3, v3));
    cerr << k3 << " " << v3 << endl;
    assert(!m4.get(j, k3, v3));
    
    cout << "Passed all basic tests." << endl;
    
    // Copy Constructor Test
    ValueType v5;
    Map bag(5);
    bag.insert("Sock", 4);
    bag.insert("Shirt", 3);
    
    assert(bag.get("Sock", v5) && v5 == 4);
    assert(bag.contains("Shirt") && bag.size() == 2);
    
    Map BigBag(bag);
    
    assert(BigBag.size() == 2);
    assert(BigBag.contains("Sock") && BigBag.contains("Shirt"));
    
    KeyType k5[3] = {"Shorts", "Pants", "Shoes"};
    for (int i = 0; i < 3; i++)
        assert(BigBag.insert(k5[i], i+1));
    
    assert(!BigBag.insert("Jacket", 1));
    
    KeyType k6[5] = {"Sock", "Shirt", "Shorts", "Pants", "Shoes"};
    ValueType v6;
    ValueType v7[5] = {4, 3, 1, 2, 3};
    for (int i = 0; i < 5; i++)
    {
        assert(BigBag.get(i, k6[i], v6) && v6 == v7[i]);
    }
    
    // Assignment Operator Test
    Map smallBag = BigBag;
    
    assert(BigBag.size() == 5);
    assert(BigBag.contains("Sock") && BigBag.contains("Shirt"));
    
    assert(!BigBag.insert("Jacket", 1));
    
    for (int i = 0; i < 5; i++)
    {
        assert(BigBag.get(i, k6[i], v6) && v6 == v7[i]);
    }
    
    assert(smallBag.size() == 5);
    assert(smallBag.contains("Sock") && smallBag.contains("Shirt"));
    
    assert(!smallBag.insert("Jacket", 1));
    
    for (int i = 0; i < 5; i++)
    {
        assert(smallBag.get(i, k6[i], v6) && v6 == v7[i]);
    }
    
    // Swap Test
    Map JunkBag(2);
    JunkBag.swap(BigBag);
    
    assert(JunkBag.size() == 5);
    assert(JunkBag.contains("Sock") && JunkBag.contains("Shirt"));
    
    assert(!JunkBag.insert("Jacket", 1));
    
    for (int i = 0; i < 5; i++)
    {
        assert(JunkBag.get(i, k6[i], v6) && v6 == v7[i]);
    }
    
    assert(BigBag.size() == 0);
    assert(!BigBag.contains("Sock") && !BigBag.contains("Shirt"));
    
    assert(BigBag.insert("Jacket", 1));
    assert(BigBag.insert("Nothing", 0));
    assert(!BigBag.insert("Something", 1.1));
    
    cout << "Passed all tests." << endl;
    
} // end main
