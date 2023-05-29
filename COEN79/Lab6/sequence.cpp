// FILE: sequence.cpp
// Nathan Yu and Conner Yin
// Lab 6
// 5/17/23
#include "sequence.h"
#include "node.cpp"
#include <cassert>
#include <cstdlib>

using namespace std;

namespace coen79_lab6{

    void sequence::init(){
        // initialize a sequence to be empty
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    sequence::sequence(){
        //Postcondition: the sequence has been initialzed as an empty sequence
        init();                 
    }

    sequence::sequence(const sequence& source){
        init();
        *this = source;
    }

    //Destructor
    sequence::~sequence(){
        list_clear(head_ptr);
        init();
    }

    // Move cursor to start
    void sequence::start(){
        // Postcondition: cursor and precursor are changed so
        // the current is the first element
        precursor = NULL;
        cursor = head_ptr;
    }   

    // Move cursor to end
    void sequence::end(){
        // Postcondition: cursor and precursor are changed so
        // the current is the last element
        cursor = tail_ptr;
        // If only one element NULL precursor, else go one before end
        if(head_ptr == tail_ptr) precursor = NULL;
        else precursor = list_locate(head_ptr, many_nodes-1); 
    }

    // Advance the precursor and cursor
    void sequence::advance(){
        // Postcondition: New current is the next node unless current is the last node
        assert(is_item()); // Precondition
        precursor = cursor;
        cursor = cursor->link();
    }

    // Insert an item before cursor (or before head if not valid cursor)
    void sequence::insert(const value_type& entry){
        // Postcondition: A new copy of entry has been inserted in the sequence
        // before the current item. If there was no current item, then the new entry
        // has been inserted at the front of the sequence. In either case, the newly
        // inserted item is now the current item of the sequence.

        // If cursor and precursor both valid insert using list_insert
        if(is_item() && precursor != NULL){
            list_insert(precursor, entry);
            cursor = precursor->link();
        // If not pointing to anything, insert to head
        } else {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            if(tail_ptr == NULL){
                tail_ptr = head_ptr;
            }
        }
        many_nodes++; // Increment node count
    }

    // Attach entry after cursor
    void sequence::attach(const value_type& entry){
        // Postcondition: A new copy of entry has been inserted in the sequence after
        // the current item. If there was no current item, then the new entry has
        // been attached to the end of the sequence. In either case, the newly
        // inserted item is now the current item of the sequence.

        // If empty, attach/insert to head pointer
        if(head_ptr == NULL) insert(entry);
        // If cursor is invalid, attach to end
        else if(!is_item()){
            // Insert entry, advance cursor and precursor
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            tail_ptr = cursor = tail_ptr->link();
            many_nodes++;
        }
        // Otherwise attach after cursor
        else{
            // Insert entry, advance precursor and cursor
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            if(cursor->link() == NULL)
                tail_ptr = cursor;
            many_nodes++;
        }
    }

    void sequence::operator =(const sequence& source){
        
        list_copy(source.head_ptr,head_ptr,tail_ptr);   //copy from source
        start();                                        //get to beginning of the copy
        node* temp = source.head_ptr;
        while(temp != source.cursor){            //iterate through temp till our cursors are correct
            advance();
            temp = temp->link();
        }
        many_nodes = source.many_nodes;                 //set many_nodes
    }


    void sequence::remove_current(){
        // Precondition: cursor is pointing at a node
        // Postcondition: the node that the cursor was pointing at has been removed
        assert(is_item());
        if(cursor == head_ptr){
            if(head_ptr == tail_ptr){            //if we only have 1 item in the sequence
                list_head_remove(head_ptr);
                init();                         //remove then reset seqence
                return;
            }
            list_head_remove(head_ptr);         //if we are removing the head
            cursor = head_ptr;
            precursor = NULL;
            many_nodes--;
            return;
        }
        if(cursor == tail_ptr){                  //case when we are removing tail_ptr
            list_remove(precursor);
            tail_ptr = precursor;
            cursor = NULL;
            many_nodes--;
            return;
        }
        cursor = cursor->link();
        list_remove(precursor);                 //general case
        many_nodes--;
        return;
    }
    sequence::size_type sequence::size() const {
        // Postcondition: return value is the size of the sequence
        return many_nodes;
    }

    bool sequence::is_item( ) const{
        // Postcondition: returns whether or not the cursor points to an item
        return !(cursor == NULL);
    }

    sequence::value_type sequence::current() const{
        // Precondition: cursor points at a valid node
        // Postconditions returns the value of the node pointed by the cursor
        assert(is_item());
        return cursor->data();
    }


}
