/** @file: testMap.cpp */
/*
#include "Map.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    ValueType tempV;
    KeyType tempK;
    Map m1;
    
    m1.insert("A", 10.5);
    assert(m1.size() == 1);
    m1.insert("B", 10.5);
    assert(m1.size() == 2);
    
    for (int i = 0; i < 5; i++)
    {
        cerr << m1.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    m1 = m1;
    
    assert(m1.size() == 2);
    assert(!m1.insert("B", 5));
    
    assert(m1.insertOrUpdate("C", 5));
    assert(m1.insertOrUpdate("B", 5));
    
    assert(m1.size() == 3);
    
    assert(m1.get("A", tempV) && tempV == 10.5);
    assert(m1.get("B", tempV) && tempV == 5);
    
    m1 = m1;
    tempV = 12;
    assert(!m1.get("D", tempV) && tempV == 12);
    
    for (int i = 0; i < 5; i++)
    {
        cerr << m1.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    Map m2;
    
    m2.insert("D", 20);
    m2.insert("A", 15);
    m2.insert("C", 25);
    m2.insert("B", 10.5);
    
    m2 = m2;
    
    for (int i = 0; i < 5; i++)
    {
        cerr << m2.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    m2.swap(m1);
    
    cerr << "M2: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m2.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    cerr << "M1: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m1.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    assert(m2.size() == 3);
    assert(m1.size() == 4);
    
    Map m3(m1);
    
    assert(m3.size() == 4);
    
    cerr << "M3: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m3.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    assert(!m1.empty());
    
    Map m4;
    subtract(m3, m1, m4);
    assert(m4.size() == 0);
    

    subtract(m1, m2, m4);
    assert(m4.size() == 1);
    
    cerr << "M4: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m4.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    subtract(m2, m1, m4);
    assert(m4.size() == 0);
    
    assert(combine(m1, m3, m4));
    
    cerr << "M4: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m4.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    assert(m4.size() == 4);
    
    m1.update("C", 5);
    m1.update("B", 5);
    
    assert(!combine(m1, m2, m4));
    cerr << "M4: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m4.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    assert(m4.size() == 3);
    
    assert(m4.erase("D"));
    cerr << "M4: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m4.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    Map m5;
    subtract(m4, m4, m5);
    
    cerr << "M5: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m5.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    combine(m4, m4, m5);
    cerr << "M5: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cerr << m5.get(i, tempK, tempV) << " " << tempK << " " << tempV << endl;
    }
    cerr << endl;
    
    
    cout << "PASSED ALL TESTS" << endl;
}
 
int main() {
    Map m;
    KeyType k = "Sally";
    ValueType v = 10.5;
    
    
    // EMPTY MAP TEST: (used for the empty map scenarios)
    assert(m.size() == 0);	// check that size works as intended
    assert(m.empty());	// check that empty works as intended
    assert(!m.erase("Jim"));	// check that erase returns false when trying to erase a key not in the map
    assert(!m.update("Jim", 60));	// check that update returns false when trying to update a key not in the map
    assert(!m.contains("Jim"));	// check that contains returns false when there are no keys
    assert(!m.get("Jim", v));	// check that get returns false when there are no key
    assert(k == "Sally" && v == 10.5);	// check that get did not change k or v
    
    assert(!m.get(10, k, v));	// check for out of bounds (upper)
    assert(k == "Sally" && v == 10.5);
    
    assert(!m.get(-5, k, v));	// check for out of bounds (lower)
    assert(k == "Sally" && v == 10.5);
    
    
    // 1 ITEM MAP TEST: (used for the single item scenarios)
    Map m2;
    assert(m2.insert("Jim", 60));	// check that insert returns true when inserting a unique key
    assert(!m2.insert("Jim", 50));	// check that insert returns false when inserting a duplicate
    assert(m2.size() == 1);	// check that size works as intended
    assert(!m2.empty());	// check that empty works as intended
    assert(m2.update("Jim", 65));	// check that update returns true when updating a key in the map
    assert(m2.insertOrUpdate("Jim", 60));	// check that update returns true when the key is in the map
    assert(m2.insertOrUpdate("Sarah", 15));	// check that update returns true when the key is not in the map
    assert(!m2.erase("Sally"));	// check that erase returns false when the key is not in the map
    assert(m2.erase("Sarah"));	// check that Sarah was properly inserted into the map
    assert(m2.contains("Jim"));	// check that contains returns true when a key is in the map
    assert(!m2.contains("Sarah"));	// check that contains returns false when a key is not in the map
    assert(!m2.get("Sally", v));	// check that get returns false when a key is not in the map
    
    assert(m2.get("Jim", v));	// check that get returns true when a key is in the map
    assert(k == "Sally" && v == 60);	// check that v is updated after get
    v = 10.5;
    
    assert(!m2.get(10, k, v));	// check for out of bounds (upper)
    assert(k == "Sally" && v == 10.5);
    
    assert(!m2.get(-5, k, v));	// check for out of bounds (lower)
    assert(k == "Sally" && v == 10.5);
    
    assert(m2.get(0, k, v));	// check that the 2nd iteration of get works as intended
    assert(k == "Jim" && v == 60);
    
    
    // MULTI-ITEM MAP TEST: (used for the normal item scenarios)
    // ALTHOUGH THESE TESTS SEEM REDUNDANT, THEIR PURPOSE IS TO MAKE SURE THAT THE FUNCTIONS STILL
    // WORK PROPERLY AFTER THE MAP HAS INCREASED IN SIZE BY MORE THAN A SINGLE ENTRY
    Map m3;
    assert(m3.insert("Jim", 60));	// thorough test of insert after keys have been added to the map
    assert(m3.insert("Mike", 15));
    assert(m3.insert("Kyle", 25));
    assert(m3.insert("Nancy", 35));
    assert(!m3.insert("Nancy", 15));
    assert(m3.size() == 4);	// check size for a larger map
    assert(!m3.empty());	// check to see that empty works as intended
    assert(m3.update("Jim", 50));	// check to see if update returns true when the key is in the map
    assert(!m3.update("Tyler", 50));	// check to see if update returns false otherwise
    assert(m3.insertOrUpdate("Jim", 60));	// check that insert works as intended
    assert(m3.insertOrUpdate("Tyler", 50));
    assert(!m3.erase("Sally"));	// check to see if erase works as intended
    assert(m3.erase("Tyler"));
    assert(m3.contains("Jim"));
    assert(!m3.contains("Tyler"));
    assert(m3.size() == 4);
    
    k = "Sally";
    v = 10.5;
    assert(!m3.get("Sally", v));
    assert(k == "Sally" && v == 10.5);
    
    assert(m3.get("Jim", v));
    assert(k == "Sally" && v == 60);
    v = 10.5;
    
    assert(!m3.get(10, k, v));	// out of bounds (upper)
    assert(k == "Sally" && v == 10.5);
    
    assert(!m3.get(-5, k, v));	// out of bounds (lower)
    assert(k == "Sally" && v == 10.5);
    
    for (int i = 0; i < m3.size(); i++)
    {
        m3.get(i, k, v);
        cerr << k << " " << v << endl;
    }
    // should write to cerr each of the 4 entries with their value right after
    
    cout << "Passed all basic tests" << endl;
    
    
    // AT THIS POINTS, THE BASIC MEMBER FUNCTION SHOULD ALL BE WORKING PROPERLY
    // m1 should be empty; m2 should contain only 1 entry: "Jim", 60; and m3 should
    // contain 4 entries: "Jim", 60; "Mike", 15; "Kyle", 25; and "Nancy", 35;
    
    
    // COPY CONSTRUCTOR / ASSIGNMENT OPERATOR
    
    Map m3Copy(m3);	// check the copy constructor…
    
    assert(m3Copy.size() == 4);	// the sizes should have been copied
    
    for (int i = 0; i < m3Copy.size(); i++)
    {
        m3Copy.get(i, k, v);
        cerr << k << " " << v << endl;
    }
    // should write to cerr each of the 4 entries with their value right after
    
    Map m3Copy2 = m3; // check the copy constructor…
    
    assert(m3Copy2.size() == 4);	// the size should have been copied
    
    for (int i = 0; i < m3Copy2.size(); i++)
    {
        m3Copy2.get(i, k, v);
        cerr << k << " " << v << endl;
    }
    // should write to cerr each of the 4 entries with their value right after
    
    Map empty;	// assignment operator on an empty map
    m3Copy = empty;
    assert(m3Copy.empty());	// make sure the new map is empty
    Map empty2(empty);	// copy constructor on an empty map
    assert(empty2.empty());	// make sure the new map is empty
    
    m3=m3;  // test m3 = m3
    assert(m3.size() == 4);
    assert(m3.contains("Mike"));
    
    Map m10 = m3;
    m10.insert("Random", 10);
    
    assert(m3.size() == 4);
    
    // TEST SWAP
    
    Map S1;
    S1.insert("Jim", 60);
    Map S2(S1);
    assert(S1.size() == 1);
    assert(S2.size() == 1);
    assert(S1.contains("Jim"));
    assert(S2.contains("Jim"));
    Map S3;
    S3.swap(S1);	// check swap
    assert(S1.empty());	// make sure hat s1 is now empty
    assert(S3.size() == 1);	// and s3 has a size
    assert(S3.contains("Jim"));	// check to see if s3 now contains the contents of s1
    S3.swap(S1);	// swap them back
    assert(S3.empty());	// re-check the sizes…
    assert(S1.size() == 1);
    
    
    // TEST COMBINE
    
    Map C1;
    Map C2;
    Map C3;
    C1.insert("A", 10);
    C1.insert("B", 20);
    C1.insert("C", 30);
    C1.insert("D", 40);
    
    C2.insert("C", 30);
    C2.insert("E", 50);
    C2.insert("D", 41);
    
    assert(!combine(C1, C2, C3));	// check that combine returns false when the contents of the map are not unique
    assert(C3.size() == 4);	// check that the maps combined properly
    assert(!combine(C1, C2, C2));	// check for aliasing
    assert(C2.size() == 4);
    
    Map C4;
    Map C5;
    Map C6;
    C4.insert("N", 1);
    C5.insert("M", -1);
    
    assert(combine(C4, C5, C6));	// check that combine returns true when the contents of the map are unique
    assert(C6.size() == 2);	// check that the function worked properly…
    assert(C6.contains("M"));
    assert(C6.contains("N"));
    
    for (int i = 0; i < C1.size(); i++)
    {
        C1.get(i, k, v);
        cerr << k << " " << v << endl;
    } // check 1
    
    combine(C1, C1, C1);    // check for the odd case of using the same map 3 times as input
    
    assert(C1.size() == 4);
    
    for (int i = 0; i < C1.size(); i++)
    {
        C1.get(i, k, v);
        cerr << k << " " << v << endl;
    } // should be the same as check 1
    
    
    // TEST SUBTRACT
    
    Map SUB1;
    Map SUB2;
    Map SUB3;
    SUB1.insert("A", 10);
    SUB1.insert("B", 20);
    SUB1.insert("C", 30);
    SUB1.insert("D", 40);
    
    SUB2.insert("C", 30);
    SUB2.insert("E", 50);
    SUB2.insert("D", 41);
    
    subtract(SUB1, SUB2, SUB3);	// check that subtract works properly…
    assert(SUB3.size() == 2);	// the size should now be 2
    assert(SUB3.contains("A"));	// with both A and B in the map
    assert(SUB3.contains("B"));
                  
    subtract(SUB1, SUB2, SUB2);	// check for aliasing
    assert(SUB2.size() == 2);
    assert(SUB2.contains("A"));
    assert(SUB2.contains("B"));
                                
    Map SUB4;
    Map SUB5;
    
    subtract(SUB1, SUB4, SUB5);	// check for subtracting empty map
    assert(SUB5.size() == 4);
    assert(SUB5.contains("A"));
    assert(SUB5.contains("B"));
    assert(SUB5.contains("C"));
    assert(SUB5.contains("D"));
    
    for (int i = 0; i < SUB1.size(); i++)
    {
        SUB1.get(i, k, v);
        cerr << k << " " << v << endl;
    }
    
    subtract(SUB1, SUB1, SUB1); // check for the odd case of using the same map 3 times as input
    
    assert(SUB1.empty());
    
    cout << "**********PASSED ALL TEST**********" << endl;
} */

#include "OurType.h"
#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
    return OurType::m_count;
}

inline int nasstcopys()
{
    return OurType::m_asstcopycount;
}

bool get2type(bool (Map::*)(const KeyType&, ValueType&) const) { return true; }
bool get2type(bool (Map::*)(const KeyType&, ValueType&)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&)) { return false; }
bool get3type(...) { return false; }

KeyType SOMEKEY = OurType(123);
KeyType DEFAULT = KeyType();
KeyType ARRAY[6] = {
    OurType(10), OurType(20), OurType(30),
    OurType(40), OurType(50), OurType(60)
};

ValueType SOMEVALUE = "junk";
ValueType DEFAULTV = ValueType();
ValueType ARRAYV[6] = {
    "able", "baker", "charlie", "delta", "echo", "foxtrot"
};

struct PairType
{
    PairType(const KeyType& kk, const ValueType& vv) : k(kk), v(vv) {}
    KeyType k;
    ValueType v;
};

bool isPermutation(const Map& m, const KeyType ka[], const ValueType va[], int n)
{
    if (m.size() != n)
        return false;
    vector<PairType> a;
    a.reserve(n);
    for (int i = 0; i < n; i++)
    {
        KeyType k;
        ValueType v;
        m.get(i, k, v);
        a.push_back(PairType(k,v));
    }
    for (int j = 0; j < n; j++)
    {
        int i;
        for (i = j; i < n; i++)
        {
            if (ka[j] == a[i].k  &&  va[j] == a[i].v)
            {
                PairType t = a[j];
                a[j] = a[i];
                a[i] = t;
                break;
            }
        }
        if (i == n)
            return false;
    }
    return true;
}

bool has(const Map& m, const KeyType& k, const ValueType& v)
{
    ValueType v2 = DEFAULTV;
    m.get(k, v2);
    ValueType v3 = SOMEVALUE;
    m.get(k, v3);
    return v2 == v  &&  v3 == v;
}

void testone(int n)
{
    Map m;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
        } break; case  4: {
            assert(get2type(&Map::get));
        } break; case  5: {
            assert(get3type(&Map::get));
        } break; case  6: {
            assert(m.empty());
        } break; case  7: {
            assert(m.size() == 0);
        } break; case  8: {
            assert(!m.update(DEFAULT, SOMEVALUE)  &&  m.size() == 0);
        } break; case  9: {
            assert(!m.erase(DEFAULT)  &&  m.size() == 0);
        } break; case 10: {
            assert(!m.contains(DEFAULT));
        } break; case 11: {
            ValueType v = SOMEVALUE;
            assert(!m.get(DEFAULT, v)  &&  v == SOMEVALUE);
        } break; case 12: {
            ValueType v = SOMEVALUE;
            assert(!m.get(0, DEFAULT, v)  &&  v == SOMEVALUE);
        } break; case 13: {
            assert(m.insert(SOMEKEY, SOMEVALUE));
        } break; case 14: {
            m.insert(SOMEKEY, SOMEVALUE);
            assert(!m.empty());
        } break; case 15: {
            m.insert(SOMEKEY, SOMEVALUE);
            assert(m.size() == 1);
        } break; case 16: {
            m.insert(SOMEKEY, SOMEVALUE);
            assert(m.contains(SOMEKEY));
        } break; case 17: {
            m.insert(SOMEKEY, SOMEVALUE);
            ValueType v = DEFAULTV;
            assert(m.get(SOMEKEY, v));
        } break; case 18: {
            m.insert(SOMEKEY, SOMEVALUE);
            ValueType v = DEFAULTV;
            m.get(SOMEKEY, v);
            assert(v == SOMEVALUE);
        } break; case 19: {
            m.insert(ARRAY[0], SOMEVALUE);
            ValueType v = DEFAULTV;
            assert(!m.get(ARRAY[1], v));
        } break; case 20: {
            m.insert(ARRAY[0], ARRAYV[0]);
            ValueType v = SOMEVALUE;
            m.get(ARRAY[1], v);
            assert(v == SOMEVALUE);
        } break; case 21: {
            m.insert(SOMEKEY, SOMEVALUE);
            KeyType k = DEFAULT;
            ValueType v = DEFAULTV;
            assert(m.get(0, k, v));
        } break; case 22: {
            m.insert(SOMEKEY, SOMEVALUE);
            KeyType k = DEFAULT;
            ValueType v = DEFAULTV;
            m.get(0, k, v);
            assert(k == SOMEKEY  &&  v == SOMEVALUE);
        } break; case 23: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(!m.empty()   &&  m.size() == 2);
        } break; case 24: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(m.contains(ARRAY[0])  &&  m.contains(ARRAY[1]));
        } break; case 25: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
        } break; case 26: {
            m.insert(ARRAY[0], SOMEVALUE);
            m.insert(ARRAY[1], SOMEVALUE);
            assert(has(m, ARRAY[0], SOMEVALUE)  &&  has(m, ARRAY[1], SOMEVALUE));
        } break; case 27: {
            assert(m.insert(ARRAY[0], ARRAYV[0]));
            assert(m.insert(ARRAY[1], ARRAYV[1]));
        } break; case 28: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[0], ARRAYV[2]);
            assert(m.size() == 2);
        } break; case 29: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[0], ARRAYV[2]);
            assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
        } break; case 30: {
            assert(m.insert(ARRAY[0], ARRAYV[0]));
            assert(m.insert(ARRAY[1], ARRAYV[1]));
            assert(!m.insert(ARRAY[0], ARRAYV[2]));
        } break; case 31: {
            assert(m.insert(ARRAY[0], ARRAYV[0]));
            assert(m.insert(ARRAY[1], ARRAYV[1]));
            assert(!m.insert(ARRAY[0], ARRAYV[0]));
        } break; case 32: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            m.update(ARRAY[1], SOMEVALUE);
            assert(m.size() == 3  &&  m.contains(ARRAY[0])  &&
                   m.contains(ARRAY[1])  &&  m.contains(ARRAY[2]));
        } break; case 33: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            m.update(ARRAY[1], SOMEVALUE);
            assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], SOMEVALUE)  &&
                   has(m, ARRAY[2], ARRAYV[2]));
        } break; case 34: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            assert(m.update(ARRAY[1], SOMEVALUE));
        } break; case 35: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.update(ARRAY[2], ARRAYV[0]);
            assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                   has(m, ARRAY[1], ARRAYV[1])  &&  !m.contains(ARRAY[2]));
        } break; case 36: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(!m.update(ARRAY[2], ARRAYV[2])  &&  !m.update(ARRAY[3], ARRAYV[0]));
        } break; case 37: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
            assert(!m.empty()   &&  m.size() == 2);
        } break; case 38: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
            assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
        } break; case 39: {
            m.insert(ARRAY[0], SOMEVALUE);
            m.insertOrUpdate(ARRAY[1], SOMEVALUE);
            assert(has(m, ARRAY[0], SOMEVALUE)  &&  has(m, ARRAY[1], SOMEVALUE));
        } break; case 40: {
            assert(m.insert(ARRAY[0], ARRAYV[0]));
            assert(m.insertOrUpdate(ARRAY[1], ARRAYV[1]));
        } break; case 41: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
            assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[2])  &&
                   has(m, ARRAY[1], ARRAYV[1]));
        } break; case 42: {
            assert(m.insert(ARRAY[0], ARRAYV[0]));
            assert(m.insert(ARRAY[1], ARRAYV[1]));
            assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
        } break; case 43: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            m.insertOrUpdate(ARRAY[1], SOMEVALUE);
            assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                   has(m, ARRAY[1], SOMEVALUE)  &&  has(m, ARRAY[2], ARRAYV[2]));
        } break; case 44: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            assert(m.insertOrUpdate(ARRAY[1], SOMEVALUE));
        } break; case 45: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
            assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                   has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[0]));
        } break; case 46: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
        } break; case 47: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(m.erase(ARRAY[1]));
        } break; case 48: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.erase(ARRAY[1]);
            assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                   !m.contains(ARRAY[1]));
        } break; case 49: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.erase(ARRAY[0]);
            assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[1], ARRAYV[1])  &&
                   !m.contains(ARRAY[0]));
        } break; case 50: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.erase(ARRAY[0]);
            m.erase(ARRAY[1]);
            assert(m.size() == 0);
        } break; case 51: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            m.erase(ARRAY[1]);
            m.erase(ARRAY[2]);
            m.insert(ARRAY[3], ARRAYV[3]);
            assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
                   has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[1])  &&
                   !m.contains(ARRAY[2]));
        } break; case 52: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            assert(!m.erase(ARRAY[2])  &&  m.size() == 2);
        } break; case 53: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            KeyType k;
            ValueType v;
            assert(!m.get(-1, k, v));
        } break; case 54: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            KeyType k = SOMEKEY;
            ValueType v = SOMEVALUE;
            m.get(-1, k, v);
            assert(k == SOMEKEY  &&  v == SOMEVALUE);
        } break; case 55: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            KeyType k;
            ValueType v;
            assert(!m.get(2, k, v));
        } break; case 56: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            KeyType k = SOMEKEY;
            ValueType v = SOMEVALUE;
            m.get(2, k, v);
            assert(k == SOMEKEY  &&  v == SOMEVALUE);
        } break; case 57: {
            m.insert(DEFAULT, SOMEVALUE);
            assert(m.size() == 1  &&  has(m, DEFAULT, SOMEVALUE));
        } break; case 58: {
            m.update(DEFAULT, SOMEVALUE);
            assert(m.size() == 0  &&  !m.contains(DEFAULT));
        } break; case 59: {
            m.insertOrUpdate(DEFAULT, SOMEVALUE);
            assert(m.size() == 1  &&  has(m, DEFAULT, SOMEVALUE));
        } break; case 60: {
            m.insert(DEFAULT, SOMEVALUE);
            m.erase(DEFAULT);
            assert(m.size() == 0  &&  !m.contains(DEFAULT));
        } break; case 61: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m.swap(m2);
                assert(m.size() == 3);
            }
        } break; case 62: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m.swap(m2);
                assert(has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[2])  &&
                       has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[0]));
            }
        } break; case 63: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m.swap(m2);
                assert(m2.size() == 2);
            }
        } break; case 64: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m.swap(m2);
                assert(has(m2, ARRAY[0], ARRAYV[0])  &&  has(m2, ARRAY[1], ARRAYV[1])  &&
                       !m2.contains(ARRAY[2])  &&  !m2.contains(ARRAY[3]));
            }
        } break; case 65: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            m.insert(ARRAY[3], ARRAYV[3]);
            m.insert(ARRAY[4], ARRAYV[4]);
            {
                Map m2;
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[4], ARRAYV[4]);
                m2.insert(ARRAY[0], ARRAYV[0]);
                int n = nasstcopys();
                m.swap(m2);
                int n2 = nasstcopys();
                assert(n2 < n+3);
            }
        } break; case 66: {
            int before = itemcount();
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                assert(itemcount() > before);
            }
            assert(itemcount() == before);
        } break; case 67: {
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.erase(ARRAY[1]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.erase(ARRAY[2]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.erase(ARRAY[0]);
                m2.erase(ARRAY[3]);
                m2.insert(ARRAY[4], ARRAYV[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 68: {
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                Map m3(m2);
                m3.insert(ARRAY[2], ARRAYV[2]);
                m3.erase(ARRAY[1]);
                m3.insert(ARRAY[3], ARRAYV[3]);
                m3.erase(ARRAY[2]);
                m3.insert(ARRAY[1], ARRAYV[1]);
                m3.erase(ARRAY[0]);
                m3.erase(ARRAY[3]);
                m3.insert(ARRAY[4], ARRAYV[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 69: {
            int before = itemcount();
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.insert(ARRAY[2], ARRAYV[2]);
                int mid = itemcount();
                Map m3(m2);
                assert(m3.size() == 3);
                assert(itemcount() - mid == mid - before);
            }
            assert(itemcount() == before);
        } break; case 70: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            {
                Map m2(m);
                m2.insert(ARRAY[3], ARRAYV[3]);
                assert(m2.size() == m.size()+1);
            }
        } break; case 71: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            {
                Map m2(m);
                m2.insert(ARRAY[3], ARRAYV[3]);
                assert(isPermutation(m2, ARRAY, ARRAYV, 4));
            }
        } break; case 72: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            {
                Map m2(m);
                m2.insert(ARRAY[3], ARRAYV[3]);
                assert(isPermutation(m, ARRAY, ARRAYV, 3));
            }
        } break; case 73: {
            int before = itemcount();
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.insert(ARRAY[2], ARRAYV[2]);
                int mid = itemcount();
                Map m3;
                m3.insert(ARRAY[4], ARRAYV[4]);
                m3.insert(ARRAY[5], ARRAYV[5]);
                m3 = m2;
                assert(itemcount() - mid == mid - before);
            }
        } break; case 74: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[4], ARRAYV[4]);
                m2 = m;
                m2.insert(ARRAY[5], ARRAYV[5]);
                assert(m2.size() == m.size()+1);
            }
        } break; case 75: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[4], ARRAYV[4]);
                m2.insert(ARRAY[5], ARRAYV[5]);
                m2 = m;
                m2.insert(ARRAY[2], ARRAYV[2]);
                assert(isPermutation(m2, ARRAY, ARRAYV, 3));
            }
        } break; case 76: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            {
                Map m2;
                m2.insert(ARRAY[3], ARRAYV[3]);
                m2.insert(ARRAY[4], ARRAYV[4]);
                m2.insert(ARRAY[5], ARRAYV[5]);
                m2 = m;
                m2.insert(ARRAY[2], ARRAYV[2]);
                assert(isPermutation(m, ARRAY, ARRAYV, 2));
            }
        } break; case 77: {
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.insert(ARRAY[2], ARRAYV[2]);
                int n2 = itemcount();
                m2 = m2;
                assert(itemcount() == n2);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 78: {
            {
                Map m2;
                m2.insert(ARRAY[0], ARRAYV[0]);
                m2.insert(ARRAY[1], ARRAYV[1]);
                m2.insert(ARRAY[2], ARRAYV[2]);
                m2 = m2;
                m2.insert(ARRAY[3], ARRAYV[3]);
                assert(isPermutation(m2, ARRAY, ARRAYV, 4));
            }
        } break; case 79: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            Map m3;
            combine(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 3));
        } break; case 80: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            Map m3;
            combine(m2, m, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 3));
        } break; case 81: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            Map m3;
            combine(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 5));
        } break; case 82: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            Map m3;
            assert(combine(m, m2, m3));
        } break; case 83: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            Map m3;
            m3.insert(ARRAY[2], ARRAYV[5]);
            combine(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 5));
        } break; case 84: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            Map m3;
            m3.insert(ARRAY[2], ARRAYV[5]);
            assert(combine(m, m2, m3));
        } break; case 85: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            Map m3;
            combine(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 4));
        } break; case 86: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            Map m3;
            assert(combine(m, m2, m3));
        } break; case 87: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[3], ARRAYV[3]);
            Map m2;
            m2.insert(ARRAY[2], ARRAYV[2]);
            m2.insert(ARRAY[3], ARRAYV[4]);
            Map m3;
            combine(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 3));
        } break; case 88: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[3], ARRAYV[3]);
            Map m2;
            m2.insert(ARRAY[2], ARRAYV[2]);
            m2.insert(ARRAY[3], ARRAYV[4]);
            Map m3;
            assert(!combine(m, m2, m3));
        } break; case 89: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            combine(m, m2, m);
            assert(isPermutation(m, ARRAY, ARRAYV, 5));
        } break; case 90: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            combine(m, m2, m2);
            assert(isPermutation(m2, ARRAY, ARRAYV, 5));
        } break; case 91: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            Map m3;
            subtract(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 3));
        } break; case 92: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            Map m3;
            subtract(m2, m, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 0));
        } break; case 93: {
            m.insert(ARRAY[3], ARRAYV[3]);
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[1], ARRAYV[1]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[4], ARRAYV[4]);
            m2.insert(ARRAY[2], ARRAYV[5]);
            m2.insert(ARRAY[5], ARRAYV[5]);
            m2.insert(ARRAY[3], ARRAYV[3]);
            Map m3;
            subtract(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 2));
        } break; case 94: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[1], ARRAYV[1]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            Map m3;
            m3.insert(ARRAY[3], ARRAYV[3]);
            m3.insert(ARRAY[4], ARRAYV[4]);
            subtract(m, m2, m3);
            assert(isPermutation(m3, ARRAY, ARRAYV, 1));
        } break; case 95: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[1], ARRAYV[1]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            subtract(m, m2, m);
            assert(isPermutation(m, ARRAY, ARRAYV, 1));
        } break; case 96: {
            m.insert(ARRAY[0], ARRAYV[0]);
            m.insert(ARRAY[2], ARRAYV[2]);
            Map m2;
            m2.insert(ARRAY[1], ARRAYV[1]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            subtract(m, m2, m2);
            assert(isPermutation(m2, ARRAY, ARRAYV, 1));
        } break; case 97: {
            const int NITEMS = 2000;
            for (int k = 0; k < NITEMS; k++)
                assert(m.insert(OurType(k), SOMEVALUE));
            assert(m.size() == NITEMS);
        }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}
