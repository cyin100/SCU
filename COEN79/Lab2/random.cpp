/*
Conner Yin
Lab 2 Sub-Project 2: Pseudorandom Number Generator
4.13.23
Random num gen implementation .cpp file
*/

#include "random.h"

namespace coen79_lab2 {

    // Constructor - set variables to passed in values
    rand_gen::rand_gen(int seed_, int multiplier_, int increment_, int modulus_) {
        seed = seed_;
        multiplier = multiplier_;
        increment = increment_;
        modulus = modulus_;
    }

    // Set seed function - update seed
    void rand_gen::set_seed(int new_seed) {
        seed = new_seed;
    }

    // Next function - set next seed using formula and return
    int rand_gen::next() {
        int next = (multiplier * seed + increment) % modulus;
        set_seed(next);
        return next;
    }

    // Prints information about variables
    void rand_gen::print_info() {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}
