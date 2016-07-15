/** @file: newMap.cpp */

#include "newMap.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Map::Map()
:m_nKeys(0), m_maxItems(DEFAULT_MAX_ITEMS)
{
    m_keys = new Pair[m_maxItems];
} // end default constructor

Map::Map(int numItems)
:m_nKeys(0), m_maxItems(numItems)
{
    if (m_maxItems < 0)
    {
        cout << "Map size must be non-negative" << endl;
        exit(-1);
    } // end if
    
    m_keys = new Pair[m_maxItems];
} // end constructor

Map::Map(const Map& other)
{
    m_nKeys = 0; // the size is set to 0 because as new entries are added to the map,
                 // the size will update automatically.
    m_maxItems = other.m_maxItems;
    m_keys = new Pair[m_maxItems];
    KeyType tempK;
    ValueType tempV;
    for (int i = 0; i < other.m_nKeys; i++)
    {
        other.get(i, tempK, tempV);
        this->insert(tempK, tempV);
    } // end loop
    
} // end copy constructor

Map::~Map()
{
    delete [] m_keys;
} // end deconstructor

Map& Map::operator=(const Map& rhs)
{
    Map temp(rhs);
    this->swap(temp);
    return *this;
} // end assignemt operator

bool Map::empty() const
{
    return (m_nKeys == 0);
} // end empty

int Map::size() const
{
    return m_nKeys;
} // end size

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (this->contains(key) || m_nKeys >= m_maxItems)
        return false;
    
    // map the key
    m_keys[m_nKeys].k = key;
    m_keys[m_nKeys].v = value;
    m_nKeys++;
    return true;
    
} // end insert

bool Map::update(const KeyType& key, const ValueType& value)
{
    // search through the keys
    for (int i = 0; i < m_nKeys; i++)
    {
        // if the key is in the map...
        if(m_keys[i].k == key)
        {
            // update the key
            m_keys[i].v = value;
            return true;
        } // end if
        
    } // end loop
    
    return false;
    
} // end update

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (m_nKeys >= m_maxItems)
        return false;
    
    // if it contains key...
    if(this->contains(key))
    {
        // update the key...
        this->update(key, value);
        return true;
    } // end if
    // if it doesnt contain key...
    else
    {
        // insert the key...
        this->insert(key, value);
        return true;
    } // end else
    
} // end insertOrUpdate

bool Map::erase(const KeyType &key)
{
    // search through the keys...
    for (int i = 0; i < m_nKeys; i++)
    {
        // if key was found...
        if (m_keys[i].k == key)
        {
            // remove the key
            m_keys[i].k = m_keys[m_nKeys-1].k;
            m_keys[i].v = m_keys[m_nKeys-1].v;
            m_nKeys--;
            return true;
        } // end if
        
    } // end loop
    
    return false;
    
} // end erase

bool Map::contains(const KeyType& key) const
{
    // search through the keys...
    for (int i = 0; i < m_nKeys; i++)
    {
        // if key was found...
        if (m_keys[i].k == key)
        {
            return true;
        } // end if
        
    } // end loop
    
    return false;
    
} // end contains

bool Map::get(const KeyType &key, ValueType &value) const
{
    // search through the keys...
    for (int i = 0; i < m_nKeys; i++)
    {
        // if key was found...
        if (m_keys[i].k == key)
        {
            // get the value
            value = m_keys[i].v;
            return true;
        } // end if
        
    } // end loop
    
    return false;
    
} // end get

bool Map::get(int i, KeyType &key, ValueType &value) const
{
    if(i<0 || i >= m_nKeys)
        return false;
    
    key = m_keys[i].k;
    value = m_keys[i].v;
    return true;
    
} // end get

void Map::swap(Map& other)
{
    Pair* temp1 = this->m_keys;
    int temp2 = this->m_nKeys;
    int temp3 = this->m_maxItems;
    
    this->m_keys = other.m_keys;
    this->m_nKeys = other.m_nKeys;
    this->m_maxItems = other.m_maxItems;
    
    other.m_keys = temp1;
    other.m_nKeys = temp2;
    other.m_maxItems = temp3;
    
} // end swap
