/*
Conner Yin
Lab 3: Sequence
4.20.23
File: sequence.h
*/

#ifndef COEN79_SEQUENCE1_H
#define COEN79_SEQUENCE1_H

#include <iostream>

namespace coen79_lab3 {
    
    class sequence {
        
    public:
        // TYPEDEF and MEMBER CONSTANTS
        typedef double value_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 30;
        
        // CONSTRUCTOR
        sequence();
        
        // MODIFICATION MEMBER FUNCTIONS
        void start();
        void end();    
        void advance();
        void retreat();
        void insert(const value_type& entry);
        void insert_front(const value_type& entry);
        void attach(const value_type& entry);
        void attach_back(const value_type& entry);
        void remove_current();
        void remove_front();
        
        // CONSTANT MEMBER FUNCTINOS
        size_type size() const;
        bool is_item() const;
        value_type current() const;
        size_type index() const { return current_index; }
        
        // Subscript operator
        value_type operator[](int index) const;

        // Homework Question Functions
        double mean() const;
        double standardDeviation() const;

    private:
        value_type data[CAPACITY];
        size_type used;
        size_type current_index;
    };

    // NON-MEMBER functions for the sequence class
    sequence operator+(sequence& lhs, sequence& rhs);
    sequence operator+=(sequence& lhs, sequence& rhs);
    
    // Homework Question Functions
    sequence::value_type summation(const sequence &s);
}

#endif