/*
Conner Yin
Lab 2 Sub-Project 2: Pseudorandom Number Generator
4.13.23
Random num gen class definition .h file
*/

#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H
#include <iostream>
#include <cassert>

using namespace std;

namespace coen79_lab2 {
    class rand_gen {

        // Public functions
        public:
            rand_gen(int seed_ = 1, int multiplier_ = 1, int increment_ = 1, int modulus_ = 1); // Constructor
            void set_seed(int newSeed);
            int next();
            void print_info();
        
        // Private variables
        private:
            int seed;
            int multiplier;
            int increment;
            int modulus;
    };
}

#endif
