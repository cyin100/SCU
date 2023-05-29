// FILE: poly.cpp
// Nathan Yu and Conner Yin
// Lab 4
// Implementation file for polynomials
// 5/2/23
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
        unsigned int i;
        //search for the maximum degree starting from MAXIMUM_DEGREE downwards
        for(i = MAXIMUM_DEGREE; i > 0; i--){
            if(coef[i] != 0.0)break;
        }
        current_degree = i;
        
    }

    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        assert(exponent <= MAXIMUM_DEGREE);
        //set all coeficients except specified exponent to zero
        clear();
        coef[exponent] = c;
        //update current_degree
        current_degree = exponent;
    }

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        //check MAXIMUM_DEGREE first
        assert(exponent <= MAXIMUM_DEGREE);
        //set coefficient of specified exponent to coefficient
        coef[exponent] = coefficient;
        //update the degree
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        //check MAXIMUM_DEGREE first
        assert(exponent <= MAXIMUM_DEGREE);
        //update the coefficient of the specified exponent
        coef[exponent]+=amount;
        update_current_degree();
    }

	void polynomial::clear( ) {
        // Zero out all the coeficients.
        for(int i = 0; i < MAXIMUM_DEGREE+1;i++){
            coef[i] = 0.0;
        }
        //reset current degree
        current_degree = 0;
    }

	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const {
        //if there is a degree higher than MAXIMUM_DEGREE we will acceess unallocated memory
        assert(degree() < MAXIMUM_DEGREE);
        //create a polynomial object
        polynomial temp(0.0,0);
        //fill temp with the antiderivative of our polynomial
        for(int i = 0; i < MAXIMUM_DEGREE; i++){
            temp.coef[i+1] = (coef[i]/(i+1)); 
        }
        temp.update_current_degree();
        //return antiderivative
        return temp;
    }

	double polynomial::coefficient(unsigned int exponent) const {
        // Always return 0.0 if exponent is greater than maximum degree.
        if(exponent > MAXIMUM_DEGREE){
            return 0.0;
        } else {
            return coef[exponent];
        }
    }

    double polynomial::definite_integral(double x0, double x1) const {
        //create a polynomial object filled with the antiderivative of our polynomial
        polynomial temp = antiderivative();
        //evaluate from x0 to x1
        return temp.eval(x1)-temp.eval(x0);
    }

	polynomial polynomial::derivative( ) const {
        //create a polynomial object
        polynomial temp(0,0.0);
        //fill with derivative of our polynomial
        for(int i = 1; i < MAXIMUM_DEGREE+1; i++){
            temp.coef[i-1] = coef[i]*i;
        }
        //update derivative current degree
        temp.update_current_degree();

        return temp;
    }

	double polynomial::eval(double x) const {
        //a specified value for x is given
        double sum = 0;
        //iterate through 0th degree to 29th degree
        for(int i = 0; i < MAXIMUM_DEGREE+1; i++){
            //evaluate for a specified coefficient
            sum += coef[i] * pow(x,i);
        }

        return sum;
    }

    bool polynomial::is_zero( ) const {
        //whether it is a zero polynomial
        //iterate through polynomial
        for(int i = 0; i < MAXIMUM_DEGREE+1; i++){
            //check if zero 
            if(coef[i] != 0){
                return false;
            }
        }
        return true;
    }

	unsigned int polynomial::next_term(unsigned int e) const {
        //return zero if we are at MAXIMUM_DEGREE
        if(e == MAXIMUM_DEGREE){
            return 0;
        }
        //iterate through polynomial starting at specified degree
        for(int i = e; i < MAXIMUM_DEGREE+1;i++){
            //check for non-zero coefficient
            if(coef[i] != 0.0){
                return i;
            }
        }
        //if there are none return zero
        return 0;
    }

	unsigned int polynomial::previous_term(unsigned int e) const {
        //retun UINT_MAX if we are at the start
        if(e == 0){
            return UINT_MAX;
        }
        //iterate backwards through polynomial
        for(int i = e; i >= 0; i--){
            //check for non-zero
            if(coef[i] != 0.0){
                return i;
            }
        }
        //if there are no previous terms return UINT_MAX
        return UINT_MAX;
    }

    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial p3;
        //iterate through both polynomials 
        for(int i=0; i<polynomial::MAXIMUM_DEGREE+1; i++){
            //add them both to our new polynomial
            p3.add_to_coef(p1.coefficient(i), i);
            p3.add_to_coef(p2.coefficient(i), i);
        }
        //update the current degree of sum
        p3.update_current_degree();
        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p3;
        //iterate through both polynomaials
        for(int i=0; i<polynomial::MAXIMUM_DEGREE+1; i++){
            //subtract terms of p1 from p2
            p3.add_to_coef(p1.coefficient(i), i);
            p3.add_to_coef(-1 * p2.coefficient(i), i);
        }

        p3.update_current_degree();
        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree()+p2.degree() < polynomial::MAXIMUM_DEGREE+1);
        polynomial p3;
        // Loop through degrees for each polynomial 
        for(int i=0; i<=p1.degree(); i++)
            for(int j=0; j<=p2.degree(); j++)
                // Multiply the coefficients and add it to the the sum of the powers
                p3.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
        p3.update_current_degree();
        return p3;
    
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){

        for(int i=p.degree(); i>=0; i--){
            //always print with precision of 1 decimal
            if(i == p.degree())             out << round(p.coefficient(i)*10)/10;                    //for the highest degree i want the minus sign closer
            else if(p.coefficient(i) < 0.0) out << " - " << abs(round(p.coefficient(i)*10)/10);      //for other terms check for their sign
            else if(p.coefficient(i) > 0.0) out << " + " << round(p.coefficient(i)*10)/10;
            else                            out << "";                                               //we don't want to print 0 terms
            
            if(p.coefficient(i) == 0)       out << "";                          //don't want to print for 0 terms
            else if(i == 1)                 out << "x";                         //special cases
            else if(i == 0)                 out << "";
            else                            out << "x^" << i;                   //for most terms
        }
        return out;
    }
}
