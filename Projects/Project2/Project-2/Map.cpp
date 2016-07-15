/** @file: Map.cpp */

#include "Map.h"

#include <iostream>
using namespace std;


//////////////////////////////////////////////////////////////
// MAP IMPLEMENTATIONS
//////////////////////////////////////////////////////////////


Map::Map()
:m_size(0), m_head(nullptr), m_tail(nullptr)
{
} // end default constructor

Map::Map(const Map& other)
:m_size(0), m_head(nullptr), m_tail(nullptr)
{
    KeyType tempK;
    ValueType tempV;
    for (int i = 0; i < other.m_size; i++)
    {
        other.get(i, tempK, tempV);
        this->insert(tempK, tempV);
    } // end for
    
} // end copy constructor

Map::~Map()
{
    if(!empty())
    {
        node* temp=m_head;
        while(temp->m_next != nullptr)
        {
            temp = temp->m_prev;
            delete temp->m_next;
        } // end while
        delete temp;
    } // end if
    
} // end deconstructor

Map& Map::operator=(const Map& rhs)
{
    Map temp(rhs);
    this->swap(temp);
    return *this;
    
} // end assignment operator

bool Map::empty() const
{
    return (m_size == 0);
    
} // end empty

int Map::size() const
{
    return m_size;
    
} // end size

bool Map::insert(const KeyType& key, const ValueType& value)
{
    // if key is already in the map...
    if (this->contains(key))
        return false;
    
    // otherwise make a new node...
    node* N;
    N = new node;
    N->m_key = key;
    N->m_value = value;
    N->m_next = nullptr;
    N->m_prev = m_head;
    m_size++;
    
    // if the list is not empty (i.e., m_head is not pointing to the null ptr)...
    if (this->m_head != nullptr)
        // set that nodes previous pointer to N.
        m_head->m_next = N;
    
    else
        m_tail = N;
    
    // update m_head.
    this->m_head = N;
    return true;
    
} // end insert

bool Map::update(const KeyType& key, const ValueType& value)
{
    // search through the keys...
    node* N;
    for (N = m_tail; N != nullptr && N->m_key != key; N = N->m_next)
        ;
    
    // if key was not in the list...
    if (N == nullptr)
        // do nothing.
        return false;
    
    // otherwise update the value.
    N->m_value = value;
    return true;
    
} // end update

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    // if the list contains key...
    if (this->update(key, value))
        // update it and return true.
        return true;
    
    // otherwise insert it.
    this->insert(key, value);
    return true;
    
} // end insertOrUpdate

bool Map::erase(const KeyType& key)
{
    // search through the keys...
    node* N;
    for (N = m_tail; N != nullptr && N->m_key != key; N = N->m_next)
        ;
    
    // if the key was not found...
    if (N == nullptr)
        // do nothing.
        return false;
    
    if (m_head == N)
        m_head = m_head->m_prev;
    
    if (m_tail == N)
        m_tail = m_tail->m_next;
    
    // otherwise delete the key.
    if (N->m_prev != nullptr)
        N->m_prev->m_next = N->m_next;
    if (N->m_next != nullptr)
        N->m_next->m_prev = N->m_prev;
    
    delete N;
    m_size--;
    return true;
    
} // end erase

bool Map::contains(const KeyType& key) const
{
    // search through the keys...
    node* N;
    for (N = m_tail; N != nullptr && N->m_key != key; N = N->m_next)
        ;
    
    return (N != nullptr); // if key is equal to nullptr, return false.
    
} // end contains

bool Map::get(const KeyType& key, ValueType& value) const
{
    // search through the keys...
    node* N;
    for (N = m_tail; N != nullptr && N->m_key != key; N = N->m_next)
        ;
    
    // if key was not found...
    if (N == nullptr)
        // do nothing.
        return false;
    
    // otherwise get the value.
    value = N->m_value;
    return true;
    
} // end get

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    // if the index is out of bounds...
    if (i < 0 || i >= m_size)
        return false;
    
    // otherwise search through the keys
    node* N;
    int count = 0;
    for (N = m_tail; N != nullptr && count < i; N = N->m_next, count++)
        ;
    
    if (N == nullptr)
        return false;
    
    // set the values and return true
    key = N->m_key;
    value = N->m_value;
    return true;
    
} // end get

void Map::swap(Map& other)
{
    // create a temporary variable for each member...
    node* tempH = this->m_head;
    node* tempT = this->m_tail;
    int tempI = this->m_size;
    
    // now swap them.
    this->m_head = other.m_head;
    this->m_tail = other.m_tail;
    this->m_size = other.m_size;
    
    other.m_head = tempH;
    other.m_tail = tempT;
    other.m_size = tempI;
    
} // end swap


//////////////////////////////////////////////////////////////
// NON-MEMBER FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////


bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map tempM;
    KeyType tempKM1, tempKM2;
    ValueType tempVM1, tempVM2;
    bool toReturn = true;
    
    // search through the keys...
    for (int i = 0; i < m1.size(); i++)
    {
        // for each key get its key and value
        m1.get(i, tempKM1, tempVM1);
        // check if m2 has the same key
        if (m2.contains(tempKM1))
        {
            // if it does, get m2's value for that key
            m2.get(tempKM1, tempVM2);
            // if they are the same...
            if (tempVM2 == tempVM1)
                // insert it.
                tempM.insert(tempKM1, tempVM1);
            else
                toReturn = false;
        } // end if
        // if m2 doesn't have the key that was in m1, insert it
        else
            tempM.insert(tempKM1, tempVM1);
    } // end for
    
    // now go through m2, and get all the keys that are in m2, but not in m1
    for (int i = 0; i < m2.size(); i++)
    {
        m2.get(i, tempKM2, tempVM2);
        if (!m1.contains(tempKM2))
            tempM.insert(tempKM2, tempVM2);
    } // end for
    
    result = tempM;
    return toReturn;

}  // end combine

void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map tempM;
    KeyType tempK;
    ValueType tempV;
    
    // search through the keys in m1...
    for (int i = 0; i < m1.size(); i++)
    {
        // for each key, get its value and key
        m1.get(i, tempK, tempV);
        // if m2 doesn't contain the key...
        if (!m2.contains(tempK))
            // insert it.
            tempM.insert(tempK, tempV);
    }
    
    result = tempM;
    
} // end subtract


