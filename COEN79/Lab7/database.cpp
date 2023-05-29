/*
    file : database.cpp
    Nathan Yu and Conner Yin
    COEN 79
    Lab 7
*/
// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    // constructor
    // postcondition: creates an empty database with aloc_slots = initial_capacity
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // copy constructor
    // postcondition: creates a database that is equal to src
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;
        company_array = new company[aloc_slots];
        *company_array = *src.company_array;

    }
    
    // assignment operator
    // postcondition: this is now equal to rhs
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        if(this == &rhs) {return *this;}

        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        delete[] company_array;
        company_array = new company[aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);        //copy contents of rhs into our new array
        return *this;
        
    }
    
    // Deconstructor
    database::~database() {
        delete[] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    // Postcondition: The database's current capacity is changed to the
    // new_capacity (but not less than the number of items already in the
    // database). The insert_company function will work efficiently (without allocating
    // new memory) until the new capacity is reached.
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company* temp = new company[new_capacity];                          // make a new company with new_capacity
        std::copy(company_array, company_array + used_slots, temp);         // copy company_array into temp
        delete[] company_array;
        aloc_slots = new_capacity;
        company_array = temp;                                               // set company_array to temp
    }
    
    // Precondition: company_name is a non-empty string
    // Postcondition: A new Company is added to the list
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);          //find index of company
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        if (used_slots == aloc_slots){                  // if array is full reserve 1 more
            reserve(aloc_slots+1);
        }
        company temp = company(entry);                  // create company named entry
        company_array[used_slots++] = temp;             // add to company_array
        return true;                                    
    }
    
    // Precondition: company_name and product_name are non-empty strings
    // Postcondition: A new product is added to the list pertaining to the company
    // This function also checks to see if the company is already in the database.
    // Returns false if the compnay is already in the database, otherwise returns true.
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        size_type company_index = search_company(company);                      // find index of company
        if(company_index == COMPANY_NOT_FOUND){ return false; }                 // if the company is not in the array return false
        else{
            return company_array[company_index].insert(product_name,price);     // if company in company_array insert product
            
        }
    }
    
    // Precondition: company_name and product_name are non-empty strings
    // Postcondition:  A product is erased from the company in the database.  Returns false if
    // the company or the item was not found.
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        if(company_index == COMPANY_NOT_FOUND){ return false;}
        company_array[company_index] = company_array[--used_slots];
        return true;
    }
    
    //Precondition: company name and product name lengths are greater than 0
    //Postcondition: return true if the product name is removed else return false
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type company_index = search_company(cName);                        // use search to find index of company
        if(company_index == COMPANY_NOT_FOUND) { return false; }                
        return company_array[company_index].erase(pName);     
    }
    
    
    // Precondition: company is a non-empty string
    // Postcondition: return the index of the company or -1 if it does not exist
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        //iterate through company_array and return the index of company
        for(int i = 0; i < used_slots; i++){
            if(company_array[i].get_name() == company){
                return i;
            }
        }
        return -1;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
