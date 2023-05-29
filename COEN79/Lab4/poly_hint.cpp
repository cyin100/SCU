// FILE: poly.cpp
//
// 
// 
//
//
// NOTE: current_degree is always equal to the largest exponent with a non-zero
//          coefficient. If all coeficients are 0.0, then current_degree is 0.

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    // CONSTANTS
    const unsigned int polynomial::MAXIMUM_DEGREE;

    // HELPER FUNCTIONS
    void polynomial::update_current_degree() {
        //set current degree to the index of the item with the maximum degree
    }

    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        //all coefficients should set to be 0 except for the specified one
        //don't forget to set the current_degree pointing to it
    }

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        //check MAXIMUM_DEGREE first
        //assign the coefficient, update the current_degree if necessary
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        //update the coefficient of the specified exponent
    }

	void polynomial::clear( ) {
        // Zero out all the coeficients.
        //don't forget to reset the current_degree
    }

	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const {

    }

	double polynomial::coefficient(unsigned int exponent) const {
        // Always return 0.0 if exponent is greater than maximum degree.
    }

    double polynomial::definite_integral(double x0, double x1) const {

    }

	polynomial polynomial::derivative( ) const {

    }

	double polynomial::eval(double x) const {
        //a specified value for x is given
    }

    bool polynomial::is_zero( ) const {
        //whether it is a zero polynomial
    }

	unsigned int polynomial::next_term(unsigned int e) const {
        //return the next valid exponent
        //otherwise return 0
    }

	unsigned int polynomial::previous_term(unsigned int e) const {
        //return the previous valid exponent
        //otherwise retun UINT_MAX
    }

    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial p3;
        for(int i=0; i<polynomial::MAXIMUM_DEGREE+1; i++){
            p3.add_to_coef(p1.coefficient(i), 1);
            p3.add_to_coef(p2.coefficient(i), 1);
        }
        p3.update_current_degree();
        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p3;
        for(int i=0; i<polynomial::MAXIMUM_DEGREE+1; i++){
            p3.add_to_coef(p1.coefficient(i), 1);
            p3.add_to_coef(-1 * p2.coefficient(i), 1);
        }
        p3.update_current_degree();
        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree()*p2.degree() < polynomial::MAXIMUM_DEGREE+1);
        polynomial p3;
        for(int i=0; i<p1.degree(); i++){
            for(int j=0; j<p2.degree(); j++)
                p3.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j)
        p3.update_current_degree();
        return p3;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){
        
        for(int i=degree(); i>=0; i--){
            
            if(i!=degree()){
                if(coefficient(degree()) < 0){
                    assign_coef(-1 * coefficient(i), i);
                    out << " - "
                else
                    out << " + "
            }
                
            if(i==1) out << coefficient(1) << "x";
            else if(i==0) out << coefficient(0);
            out << coefficient(degree()) << "x^" << degree();
        }
    }
}
