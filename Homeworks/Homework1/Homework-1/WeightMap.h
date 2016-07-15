/** @file: WeightMap.h */

#ifndef WEIGHT_MAP_INCLUDED
#define WEIGHT_MAP_INCLUDED

#include "Map.h"

#include <string>

typedef std::string KeyType;
typedef double ValueType;

class WeightMap
{
public:
    /** Create an empty weight map. */
    WeightMap();
    
    
    /** Adds a person to the Weight Map.
        @post: a person with name and weight startWeight are added to the map
            and the number of people is increased by 1.
        @param: name: the name of the person to be added to the map.
        @param: startWeight: the weight of that person.
        @return: True if the insertion was successful (i.e., the name was not already
            in the map, there was room in the map, and start weight was not negative.)
            Otherwise, return false and no changes were made.*/
    bool enroll(KeyType name, ValueType startWeight);
    
    
    /** Gets the weight of a person.
        @param: name: the name of the person to get the weight of.
        @return: The weight of that person if succesful (i.e., name is in the
            map.) Otherwise, return -1. */
    ValueType weight(KeyType name) const;
    
    
    /** Updates the weight of a person.
        @post: the person with name 'name', has their weight increased by amt.
        @param: name: the name of the person.
        @param: amt: the amount to add to the current weight to.
        @return: True if successful (i.e., the person is already in the map and
            their weight + amt is non-negative.) Otherwise, false and no changes
            made. */
    bool adjustWeight(KeyType name, ValueType amt);
    
    
    /** Get the size of the map
        @return: The number of people in the map. */
    int size() const;
    
    
    /** Write out everyone and their weights.
        Writes to cout one line for every person in the map. Each line is of the
        form: Name Weight (e.g., Jim 149.6). */
    void print() const;
    
    
private:
    
    Map m_weightMap;
    
}; // end WeightMap

#endif /** WEIGHT_MAP_INCLUDED */
