/*
Conner Yin
Lab 3: Sequence
4.20.23
File: sequence.cpp
*/

#include "sequence1.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	sequence::sequence() { current_index = used = 0; }                  // CONSTRUCTOR: Set current index/used to 0
	void sequence::start() { current_index = 0; }                       // Set current index to 0
    void sequence::end() { current_index = used - 1; }                  // Set current index to end
    void sequence::advance() { if(is_item() && used<CAPACITY) current_index++; }         // Advance if in bounds
    void sequence::retreat() { if(current_index>0) current_index--; } // Retreat if in bounds
    
    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);                                      // Precondition 
        if(!is_item()) data[0] = entry;                                 // Insert to front if no current item              
        else {
            // Shift data and insert entry to current index
            for(int i=used; i>current_index; i--) data[i] = data[i-1];
            data[current_index] = entry;
        }
        used++;
	}

    bool sequence::is_item() const { return current_index < used; }     // Return if current index is in bounds

    void sequence::attach(const value_type& entry) {
    	assert(size() < CAPACITY);                                      // Precondition
        if(!is_item()) data[used] = entry;                              // Attach to end if no current item
        else {
            // Shift data and attach entry to current index + 1
            current_index++;
            for(int i=used; i>current_index; i--) data[i] = data[i-1];
            data[current_index] = entry;
        }
        used++;
    }

    void sequence::remove_current() {
    	assert(is_item());                                              // Precondition
    	for(int i=current_index+1; i<used; i++) data[i-1] = data[i];    // Shift items into current index
        used--;
    }

	void sequence::insert_front(const value_type& entry) {
		start();                                                        // Set current index to start
        insert(entry);                                                  // Insert entry (satisfies pre-cond as well)
	}

	void sequence::attach_back(const value_type& entry) {                                          
		end();                                                          // Set current index to end
        attach(entry);                                                  // Attach entry (satisifies pre-cond as well)
	}

	void sequence::remove_front() {
		assert(is_item());                                              // Precondition
        start();                                                        // Set current index to start
        remove_current();                                               // Remove start index
	}

    sequence::value_type sequence::current() const { 
        assert(is_item());                                              // Precondition
        return data[current_index];                                     // Return data at current index under pre-cond
    }    
	sequence::size_type sequence::size() const { return used; }         // Used getter function
    sequence::value_type sequence::operator[](int index) const {
    	assert(index<used);                                             // Precondition
        return data[index];                                             // Return data at index   
    }
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		assert(lhs.size() + rhs.size() <= lhs.CAPACITY);                // Precondition (make sure sum of sizes < capacity)

        // Create copies of lhs and rhs (s to be returned)
        sequence s(lhs);
        sequence r(rhs);
        r.start();

        // Loop through r and attach to s
        for(int i=0; i<rhs.size(); i++){
            s.attach(r.current());
            r.advance();
        }
        return s;
	}
    
	sequence operator+=(sequence& lhs, sequence& rhs) {
        lhs = lhs+rhs;                                                // Use + operator to implement +=
        return lhs;
	}
    
	double sequence::mean() const { return summation(*this)/size(); } // Return sum/size

	double sequence::standardDeviation() const {
		sequence::value_type stdev;
        double mean = sequence::mean();

        // Calculate square sum of differences
        for(int i = 0; i < size(); i++) {
            stdev += (data[i]-mean) * (data[i]-mean);
        }
        // Calculate sqrt(sum of differences/size)
        return sqrt(stdev/size());
	}

	sequence::value_type summation(const sequence &s){
        sequence::value_type sum;

        // Create clone of s, start at beginning
        sequence c(s);
        c.start();

        // Loop through clone and add to sum
		for(int i=0; i<s.size(); i++){
            sum += c.current();
            c.advance();
        }
        return sum;
	}
}