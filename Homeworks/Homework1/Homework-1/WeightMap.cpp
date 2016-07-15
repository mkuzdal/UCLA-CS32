/** @file: WeightMap.cpp */

#include "WeightMap.h"
#include "Map.h"

#include <string>
#include <iostream>
using namespace std;

WeightMap::WeightMap()
{
} // end default constructor

bool WeightMap::enroll(KeyType name, ValueType startWeight)
{
    if (startWeight < 0)
        return false;
    
    return m_weightMap.insert(name, startWeight);
} // end enroll

ValueType WeightMap::weight(KeyType name) const
{
    ValueType w;
    // if name is in the map...
    if(m_weightMap.get(name, w))
        // return the weight.
        return w;
    
    return -1;
} // end weight

bool WeightMap::adjustWeight(KeyType name, ValueType amt)
{
    ValueType w;
    
    // if the final weight is negative...
    if(!m_weightMap.get(name, w) || w + amt < 0)
        // return false.
        return false;
    
    m_weightMap.update(name, w + amt);
    return true;
    
} // end adjustWeight

int WeightMap::size() const
{
    return m_weightMap.size();
} // end size

void WeightMap::print() const
{
    KeyType K;
    ValueType V;
    for (int i = 0; i < m_weightMap.size(); i++)
    {
        m_weightMap.get(i, K, V);
        cout << K << " " << V << endl;
    } // end loop
    
} // end print
