/*
Conner Yin & Nathan Yu
COEN 79 Lab 5
5/4/2023
mystring.cpp - string implementation file
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include "mystring.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5{

    // CONSTRUCTORS

    // Char Array Constructor
    string::string(const char str[]){
        current_length = strlen(str);   // set current_length to the length of str
        allocated = current_length + 1; // so we can include \0
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    // Single char constructor
    string::string(char c){
        current_length = 1;
        allocated = current_length + 1; // so we can have c\0
        characters = new char[allocated];
        characters[0] = c; // fill our string
        characters[1] = '\0';
    }

    // Copy constructor 
    string::string(const string &source){
        current_length = source.current_length;         // Copy current length
        allocated = source.allocated;                   // Copy allocated
        characters = new char[source.current_length];   // Create empty char array with current length
        strncpy(characters, source.characters, source.current_length); //strncpy character array
    }

    // Destructors
    string::~string(){
        current_length = 0;     // Reset current length
        allocated = 0;          // Reset allocated
        delete[] characters;    // Free characters array
    }

    // CONSTANT MEMBER FUNCTIONS

    // Return character at [] position
    char string::operator[](size_t position) const{
        assert(position < length()); // Assert position is in bounds
        return characters[position]; // Return character at position
    }

    // Return index of c if found, else -1
    int string::search(char c) const{
        for (int i = 0; i < length(); i++) // Loop through string
            if (characters[i] == c)
                return i; // Return index of char if found
        return -1;        // Return -1 if not found
    }

    // Return index of start of substring if found, else -1
    int string::search(const string &substring) const{
        char *firstChar = strstr(characters, substring.characters); // Returns pointer of first char of substring
        if (firstChar != NULL)
            return firstChar[0] - characters[0]; // If found char, calculate index and return
        return -1;                               // Return -1 if not found
    }

    // Count instances of c
    unsigned int string::count(char c) const{
        size_t count = 0;
        for (int i = 0; i < length(); i++) // Loop through characters
            if (characters[i] == c)
                count++; // If equal to c, increment count
        return count;    // Return count
    }

    // MODIFICATION MEMBER FUNCTIONS

    // += operator for addend string object
    void string::operator+=(const string &addend){
        current_length += addend.length();                       // Add addend length to current length
        reserve(current_length);                                 // Allocate current length
        strncat(characters, addend.characters, addend.length()); // Concatenate addend to characters
    }

    // += operator for addend char array
    void string::operator+=(const char addend[]){
        current_length += strlen(addend);            // Add addend length to current length
        reserve(current_length);                     // Allocate current length
        strncat(characters, addend, strlen(addend)); // Concatenate addend to characters
    }

    // += operator for char addend
    void string::operator+=(char addend){
        current_length++;                    // Increment current length
        reserve(current_length);             // Allocate current length
        characters[current_length-1] = addend; // Set last character to new char
    }

    // Reserve/allocate memory
    void string::reserve(size_t n){
        char *temp = new char[allocated = n + 1]; // Allocate n+1 characters to temp array
        strncpy(temp, characters, n);             // Copy current characters into temp
        delete[] characters;                      // Free old characters array
        characters = temp;                        // Set characters to new temp array
    }

    // Assignment operator - use strncpy 
    string& string::operator =(const string& source){
        this->dlt(0, current_length);                                    // Delete all chars in array                                             // Create temp new String
        reserve(source.length());                                        // Reserve source.length() space
        strncpy(characters, source.characters, source.current_length);   // Copy over source values
        current_length = source.current_length;                          // Set new string current length to source current length
        return *this;                                                    // Return pointer of string
    }

    // Insert source at position - shift all other chars over
    void string::insert(const string &source, unsigned int position){
        assert(position <= length());                     // Assert position in bounds
        size_t total_length = length() + source.length(); // Keeps track of total length after adding
        size_t post_source = position + source.length();  // Keeps track of where source will end

        if (allocated < total_length)
            reserve(allocated = total_length); // Allocate current length + source length if necessary

        // Loop through and shift characters at position source.length() chars right
        for (int i = total_length-1; i >= post_source; i--)
            characters[i] = characters[i - source.length()];

        // Insert the source string into the remaining slot
        for (int i = 0; i < source.length(); i++)
            characters[position + i] = source.characters[i];

        current_length = total_length; // Update current length
    }

    // Delete num characters from sequence and shift following characters down
    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= length());          // Assert position in bounds
        for (int i = position; i < length(); i++) // Loop through from position to num
            characters[i] = characters[i + num];    // Set them to chars at num, effectively deleting them
        current_length -= num;                     // Decrement current length
    }

    //
    void string::replace(char c, unsigned int position){
        assert(position < length()); // Assert position in bounds
        characters[position] = c;    // Replace char at position with c
    }

    // 
    void string::replace(const string &source, unsigned int position){
        assert(position + source.length() <= length());       // reserve(position + source.length();
        for (int i = 0; i < source.length(); i++)            // Loop from position to source length
            characters[position + i] = source.characters[i]; // Change character to source character
    }

    // Ostream operator - for printing string obj
    std::ostream &operator<<(std::ostream &outs, const string &source){
        outs << source.characters;          // Print out characters
        return outs;                        // Return ostream
    }

    // TOTAL ORDER SEMANTICS - use the strcmp function on characters of each string
    // Match ==, !=, >, <, >=, <= and return if function is _ to 0
    bool operator==(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) == 0);}
    bool operator!=(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) != 0);}
    bool operator>(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) > 0);}
    bool operator<(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) < 0);}
    bool operator>=(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) >= 0);}
    bool operator<=(const string &s1, const string &s2){ return (strcmp(s1.characters, s2.characters) <= 0);}

    // NON-MEMBER FUNCTIONS

    // + operator with 2 strings
    string operator+(const string &s1, const string &s2){
        string str;
        str.reserve(s1.length() + s2.length() + 1); // Allocate memory
        str += s1;                                  // Use string obj += on s1
        str += s2;                                  // Use string obj += on s2
        return str;                                 
    }

    // + operator with string and char array
    string operator+(const string &s1, const char addend[]){
        string str;
        str.reserve(s1.length() + strlen(addend) + 1); // Allocate memory
        str += s1;                                     // Use string obj += on s1
        str += addend;                                 // Use addend += on s2
        return str;
    }

    // >> operator - user inputs a string into istream
    std::istream& operator >> (std::istream& ins, string& target){
        char* input_arr = new char[100];                // Buffer array
        while(ins && isspace(ins.peek())) ins.ignore(); // Until EOF or whitespace
        ins >> input_arr;                               // Istream input
        target = string(input_arr);                     // Create str object from input_arr in target
        return ins;                                     // Return istream
    }
}