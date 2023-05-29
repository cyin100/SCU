/*
Conner Yin
Lab 2 Sub-Project 1: Statistician
4.13.23
Implement statistician implementation .cpp file
*/

#include <cassert>
#include <iostream>
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
     
    // Constructor - functionally same as reset function
    statistician::statistician(){
        reset();
    }

    // Next function
    void statistician::next(double r){

        // Add new element to total, increment size
        total += r;
        size++; 
        avg = total/size;

        // Update min/max, set min/max to r if only element
        if(size == 1) min = max = r;
        min = (r < min) ? r : min;
        max = (r > max) ? r : max;
    }

    // Reset function
    void statistician::reset(){
        total = size = 0;
    }

    // Size get function
    int statistician::length() const { return size; }

    // Total get function
    double statistician::sum() const { 
        assert(length()>0);
        return total; 
    }

    // Mean get function
    double statistician::mean() const { 
        assert(length()>0);
        return avg; 
    }

    // Min get function
    double statistician::minimum() const { 
        assert(length()>0);
        return min; 
    }

    // Max get function
    double statistician::maximum() const { 
        assert(length()>0);
        return max; 
    }

    // + operator function
    statistician operator +(const statistician& s1, const statistician& s2){
    
        // If either s1/s2 is empty, return other statistician
        if(s1.length() == 0) return s2;
        if(s2.length() == 0) return s1;

        // Add/recalculate relevant variables, update to new statistician object
        statistician s0;
        s0.total = s1.sum() + s2.sum();
        s0.size = s1.length() + s2.length();
        s0.avg = s0.total/s0.size;
        s0.min = min(s1.minimum(), s2.minimum());
        s0.max = max(s1.maximum(), s2.maximum());
        return s0;
    }

    // * operator function
    statistician operator *(double scale, const statistician& s){

        // Create new statistican object, multiply relevant variables by scale
        statistician s0;
        s0.size = s.length();
        s0.total = scale * s.sum();
        s0.avg = scale * s.mean();
        s0.min = scale * s.minimum();
        s0.max = scale * s.maximum();

        // If min/max swapped via negatives, swap them back
        if(s0.min > s0.max){
            int temp = s0.min;
            s0.min = s0.max;
            s0.max = temp;
        }
        return s0;
    }

    // == operator function
    bool operator ==(const statistician& s1, const statistician& s2){
        // If either have length 0, return true if both are same length - else return true if all variables are the same
        if(s1.length() == 0 || s2.length() == 0) return s1.length() == s2.length();
        else return s1.length() == s2.length() && s1.sum() == s2.sum() && s1.mean() == s2.mean() && s1.minimum() == s2.minimum() && s1.maximum() == s2.maximum();
    }
};