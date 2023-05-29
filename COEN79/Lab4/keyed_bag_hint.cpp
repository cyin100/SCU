// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//
//
//
// INVARIANT for the keyed_bag class:
//   1. The number of items in the keyed_bag is in the member variable used;
//   2. For an empty keyed_bag, we do not care what is stored in any of data; for a
//      non-empty keyed_bag the items in the keyed_bag are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.


#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    const keyed_bag::size_type keyed_bag::CAPACITY;

    bool keyed_bag::erase(const key_type& key){
        //find the key first
        //if cannot find, return false
        //otherwise, erase the specified item and key & decrease the used variable
        //Think about how to move other items forward to make up the deleted empty entry. (Remeber you do NOT need to maintain the order of the item)
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key){
        //check the capacity and key first
        //then insert the new item in the bag
    }

    void keyed_bag::operator +=(const keyed_bag& addend){
    // Library facilities used: algorithm, cassert
        //check the capacity and keys first
        //then combine them together
    }

    bool keyed_bag::has_key(const key_type& key) const {
        //check whether a duplicate key exists or not
    }

    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
        //check key first
        //return the item
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        //item can be duplicated
        //this function returns the number of target items in the bag
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        //check capacity and keys first
        //return a new keyed_bag object
    }

    // Check whether the other keyed_bag shares a key with this keyed_bag.
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        
    }
}
