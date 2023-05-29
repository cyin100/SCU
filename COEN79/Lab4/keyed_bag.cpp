/*
Conner Yin & Nathan Yu
COEN 79 Lab 4
Keyed Bag Implementation File
5/3/23
*/

#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include <iostream>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4{

    const keyed_bag::size_type keyed_bag::CAPACITY;

    // Find key and swap with last slot, then decrement used to "erase" last slot
    bool keyed_bag::erase(const key_type& key){
        for(int i=0; i<size(); i++)     // Loop through bag
            if(keys[i] == key){         // If found the key
                used--;                 // Decrement used
                keys[i] = keys[used];   // Set key to last key
                data[i] = data[used];   // Set data to last data
                return true;
            }  
        return false;
    }

    // Insert key:entry into last slot and increment used
    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(size() < CAPACITY && !has_key(key));   // Pre-condition
        keys[used] = key;                             // Set last+1 key to key
        data[used] = entry;                           // Set last+1 data to entry
        used++;                                       // Increment used
    }

    // Use insert function with addend data and keys addend.size() times
    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(size()+addend.size() <= CAPACITY && !hasDuplicateKey(addend));       // Pre-condition
        for(int i=0; i<addend.size(); i++)                                          // Loop through addend
            insert(addend.data[i], addend.keys[i]);                                 // Insert key:data pairs
    }

    // Loop through keys and return true if found, else false
    bool keyed_bag::has_key(const key_type& key) const {
        for(int i=0; i<size(); i++)
            if(keys[i] == key) return true;     // If key found return true
        return false;                           // If through loop and not found, return false
    }

    // Loop through keys and return if found, else -1
    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
        assert(has_key(key));                      // Pre-condition
        for(int i=0; i<size(); i++)
            if(keys[i] == key) return data[i];     // When key found, return data
        return -1;                                 // If key not found, return -1
    }

    // Loop through data and increment when data = target
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type count = 0;
        for(int i=0; i<size(); i++)
            if(data[i] == target) count++;  // Increment when data = target
        return count;
    }

    // Create new keyed_bag and utilize += operator for b1 and b2
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.size()+b2.size() < keyed_bag::CAPACITY && !b1.hasDuplicateKey(b2));   // Pre-condition
        keyed_bag b3;   
        b3 += b1;       // Addend bag1
        b3 += b2;       // Addend bag2
        return b3;      
    }

    // Loop through each key and check if otherbag has_key
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i=0; i<size(); i++)                     // Loop through all keys in object
            if(otherBag.has_key(keys[i])) return true;  // If otherBag has the key, return true
        return false;                                   // If completed loop and not found, return false
    }
}