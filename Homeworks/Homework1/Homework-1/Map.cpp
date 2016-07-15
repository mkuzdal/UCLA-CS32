/** @file: Map.cpp */

#include "Map.h"

#include <iostream>
using namespace std;

Map::Map()
:m_nKeys(0)
{
} // end default constructor

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
    if (this->contains(key) || m_nKeys >= DEFAULT_MAX_ITEMS)
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
    if (m_nKeys >= DEFAULT_MAX_ITEMS)
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
    
    int thisS = this->size();
    
    for (int i = 0; i < other.size();)
    {
        KeyType tempK;
        ValueType tempV;
        other.get(i,tempK, tempV);
        this->insert(tempK, tempV);
        other.erase(tempK);
    } // end loop
    
    for (int i = 0; i < thisS; i++)
    {
        KeyType tempK;
        ValueType tempV;
        this->get(i, tempK, tempV);
        other.insert(tempK, tempV);
        this->erase(tempK);
    }
    
} // end swap
