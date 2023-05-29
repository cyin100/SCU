/*
Conner Yin & Nathan Yu
COEN 79 Lab 4
Poly Header File
5/3/23
*/

#ifndef COEN79_POLY_H
#define COEN79_POLY_H

#include <iostream>  // Provides ostream

namespace coen79_lab4
{
    class polynomial
    {

    public:
    	// CONSTANTS
    	static const unsigned int MAXIMUM_DEGREE = 29;

        // CONSTRUCTOR
        polynomial(double c = 0.0, unsigned int exponent = 0);

        // MODIFICATION MEMBER FUNCTIONS
        void assign_coef(double coefficient, unsigned int exponent);
        void add_to_coef(double amount, unsigned int exponent);
        void clear( );

        // CONSTANT MEMBER FUNCTIONS
        void update_current_degree();
        polynomial antiderivative( ) const;
        double coefficient(unsigned int exponent) const;
        double definite_integral(double x0, double x1) const;
        unsigned int degree( ) const { return current_degree; }
        polynomial derivative( ) const;
        double eval(double x) const;
        bool is_zero( ) const;
        unsigned int next_term(unsigned int e) const;
        unsigned int previous_term(unsigned int e) const;

        // CONSTANT OPERATORS
        double operator( ) (double x) const { return eval(x); }

    private:
        double coef[MAXIMUM_DEGREE+1];
        unsigned int current_degree;
    };

    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p1, const polynomial& p2);

    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p);
}
#endif
