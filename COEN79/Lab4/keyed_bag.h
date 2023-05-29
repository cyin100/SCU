/*
Conner Yin & Nathan Yu
COEN 79 Lab 4
Keyed Bag Header File
5/3/23
*/

#ifndef COEN79_KEYBAG_H
#define COEN79_KEYBAG_H

#include <cstdlib>  // Provides size_t
#include <string>

using namespace std;

namespace coen79_lab4 {
    class keyed_bag {
        public:
            // TYPEDEFS and MEMBER CONSTANTS
            typedef int value_type;
            typedef string key_type;
            typedef std::size_t size_type;
            static const size_type CAPACITY = 30;
            
            // CONSTRUCTOR
            keyed_bag( ) { used = 0; }
            
            // MODIFICATION MEMBER FUNCTIONS
            void erase( ) { used = 0; }
            bool erase(const key_type& key);
            void insert(const value_type& entry, const key_type& key);
            void operator +=(const keyed_bag& addend);
            
            // CONSTANT MEMBER FUNCTIONS
            bool has_key(const key_type& key) const;
            value_type get(const key_type& key) const;
            bool hasDuplicateKey(const keyed_bag& otherBag) const;
            size_type size( ) const { return used; }
            size_type count(const value_type& target) const;
        
        private:
            key_type keys[CAPACITY];    // The array to store the keys
            value_type data[CAPACITY];  // The array to store items
            size_type used;             // How much of array is used  
        };

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2);
}

#endif
