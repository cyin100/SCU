/*
Conner Yin
Lab 2 Sub-Project 1: Statistician
4.13.23
Statistican class definition .h file
*/

#ifndef STATS_H
#define STATS_H
#include <iostream>

namespace coen79_lab2 {
    class statistician {   
        
        // Private variables
        private: 
            double total, min, max, avg;
            int size;

        // Public functions
        public:
            statistician(); //Constructor
            void next(double r);
            void reset();
            int length() const;
            double sum() const;
            double mean() const;
            double minimum() const;
            double maximum() const;
            friend statistician operator +(const statistician& s1, const statistician& s2);
            friend statistician operator *(double scale, const statistician& s);
    };
    bool operator ==(const statistician& s1, const statistician& s2); //Non-member function
}

#endif