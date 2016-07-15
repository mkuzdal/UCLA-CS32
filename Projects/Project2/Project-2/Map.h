/** @file: Map.h */

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>
#include "OurType.h"

typedef OurType KeyType;
typedef std::string ValueType;

class Map
{
private:
    
    struct node
    {
        node* m_next;
        node* m_prev;
        KeyType m_key;
        ValueType m_value;
    }; // end node
    
    int m_size;
    node* m_tail;
    node* m_head;
    
public:
    
    /** Create an empty map (i.e., one with no key/value pairs). */
    Map();
    
    
    /** Copy-Constructor. */
    Map(const Map& other);
    
    
    /** Deconstructor. */
    ~Map();
    
    
    /** Assignment-Operator. */
    Map& operator=(const Map& rhs);
    
    
    /** Sees whether or not the map is empty.
        @return: True if the map is empty, otherwise false. */
    bool empty() const;
    
    
    /** Gets the current number of entries in the map.
        @return: The number of key/value pairs in the map. */
    int size() const;
    
    
    /** Inserts a new entry into the map.
        @post: If successful, key is added to the map with value and the
            number of the items in the map is increased by 1.
        @param: key: the key to be added to the map.
        @param: value: the value that is mapped to key.
        @return: True if the insertion was succesful (i.e., if key is not equal
            to any current key in the map.) Otherwise, false and no changes made. */
    bool insert(const KeyType& key, const ValueType& value);
    
    
    /** Updates the mapping of a certain key.
        @post: If successful, key is remapped to value.
        @param: key: the key to be remapped.
        @param: value: the value to remap key to.
        @return: True if the change was succesful (i.e., if key is equal to a
            key currently in the map.) Otherwise, false and no changes were made. */
    bool update(const KeyType& key, const ValueType& value);
    
    
    /** Either updates the mapping of a certain key, or inserts it if it is not already
        in the map.
        @post: If successful, key is in the map and is mapped to value, and the number
            of items in the map is increased by 1 if key was not originally in the map.
        @param: key: the key to be updated or inserted.
        @param: value: the value to give key.
        @return: True if the insertion or change was successful (i.e., if key was originally
            in the map, or if it was inserted.) Always returns true. */
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    
    
    /** Delete an entry from the map.
        @post: If successful, key and its mapped value is to be removed from the map.
        @param: key: the key to be removed.
        @return: True if the deletion was successful (i.e., if the key was originally
            in the map and it was, therefore, deleted.) Otherwise, false and no changes
            were made. */
    bool erase(const KeyType& key);
    
    
    /** Gets whether or not the map contains a certain key.
        @param: key: the key to check.
        @return: True if the key is equal to a key currently in the map.
            Otherwise false. */
    bool contains(const KeyType& key) const;
    
    
    /** Gets a certain key from the map.
        @post: If successful, value should be equal to the value mapped to key.
        @param: key: the key to get.
        @param: value: the value that the key will map its value to.
        @return: True if the operation was successful (i.e., if the key was in the
            map.) Otherwise, false and no changes made to value. */
    bool get(const KeyType& key, ValueType& value) const;
    
    
    /** Gets a certain key from the map for a given index i.
        @post: If successful, both key and value will be equal to the key and value
            mapped to that key at the index i.
        @param: i: the index to get the key-value pair from.
        @param: key: the key that the function will copy the key to.
        @param: value: the value that the function will copy the value to.
        @return: True if the operation was successful (i.e., if the index was greater
            than or equal to zero and less than the size of the map.) Otherwise, return
            false and no changes made to key or value. */
    bool get(int i, KeyType& key, ValueType& value) const;
    
    
    /** Exchange the contents of this map with the other one.
        @post: other will have the contents of this, and this will have the contents
            of other.
        @param: other: the map that this is swapped with. */
    void swap(Map& other);
    
    
}; // end Map


    /** Combines the contents of two maps.
        @post: If successful, result will have the contents of m1 and m2 with no duplicates.
        @param: m1: the first map to get the key-value pairs from.
        @param: m2: the second map to get the key-value pairs from.
        @param: result: the map where the contents of the others will be combines into.
        @return: True if the operation was successful (i.e., if there were no duplicate keys that
            had different values that went along with them) Otherwise, false and the key
            with two different values is NOT included in the result. */
    bool combine(const Map& m1, const Map& m2, Map& result);


    /** Takes the difference of two maps.
        @post: Result contains a copy of all the pairs in m1 whose keys don't appear in m2.
        @param: m1: the first map (i.e., the one to subtract m2 by).
        @param: m2: the second map.
        @param: result: the map where the contents that are in m1, but not m2. */
    void subtract(const Map& m1, const Map& m2, Map& result);


#endif /** MAP_INCLUDED */
