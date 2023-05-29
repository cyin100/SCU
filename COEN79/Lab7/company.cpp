/*
    Nathan Yu and Conner Yin
    Lab 7
    5/18/23
    FILE: company.cpp
*/

#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // Precondition: company_name is a non-empty string
    // Postcondition: The company object is initialized with "company_name"
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);          // Precondition
        this->company_name = company_name;          // Initialize company name  
        this->head_ptr = this->tail_ptr = NULL;     // Initialize head and tail to NULL
    }
    
    // Copy constructor (Value Semantics)
    // Postcondition: The company object is equal to company src
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);          // Debug statement
        this->company_name = src.company_name;                      // Set company name to src company name
        list_copy(src.get_head(), this->head_ptr, this->tail_ptr);  // List copy from src head pointer
    }

    // Assignment operator (Value Semantics)
    // Postcondition: The company object is equal to company src
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);       // Debug statement
        this->company_name = src.company_name;                      // Set company name to src company name
        list_copy(src.get_head(), this->head_ptr, this->tail_ptr);  // List copy from src head pointer
        return *this;                                               // Return a reference to this company
    }
    
    company::~company() { list_clear(head_ptr); }

    std::string company::get_name() const { return company_name; }  
    const node *company::get_head() const { return head_ptr; }      
    const node *company::get_tail() const { return tail_ptr; }     
    node* company::get_head() { return head_ptr; }                  
    node* company::get_tail() { return tail_ptr; }          
    void company::print_items() { list_print(head_ptr); }        
    
    // Precondition: product_name is a non-empty string
    // Postcondition: Creates and inserts a new node (product) to the back of the linked list.
    // Returns true if successfully inserted, and returns false if there is a duplicate
    bool company::insert(const std::string& product_name, const float& price) {
        assert(product_name.length() > 0);                                          // Precondition
        if (list_contains_item(head_ptr, product_name)) return false;               // If list contains item, return false
        if (head_ptr == NULL) list_init(head_ptr, tail_ptr, product_name, price);   // If no items in list, initialize list
        else list_tail_insert(tail_ptr, product_name, price);                       // Otherwise, insert after tail_ptr
        return true;
    }

    // Postcondition:  Erases the product that its name matches product_name. Returns true if the
    // product has been found and deleted, returns false otherwise
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);                                                  // Precondition
        if(!list_contains_item(head_ptr, product_name)) return false;                       // Return false if list doesn't contain item
        node *cursor = head_ptr;                                                            // Cursor node to loop through
        while(cursor->getLink()->getName() != product_name){ cursor = cursor->getLink(); }  // Loop until product found at link
        node *to_delete = cursor->getLink();                                                // Set link as node to delete
        cursor->setLink(to_delete->getLink());                                              // Update cursor link to node to delete's link
        delete to_delete;                                                                   // Delete node
        return true;                                                                        // Return true
    }
}
