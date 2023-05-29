// FILE: node.cpp
// Nathan Yu and Conner Yin
// Lab 6
// 5/17/23

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
	//Precondition: head_ptr is the head pointer of a linked list.
	//Postcondition: The value returned is the number of nodes in the linked list.
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	//increment answer for every node
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
		//Precondition: head_ptr is the head of a linked list
		//Postcondition: a new node with value entry is at the head
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
		// Precondition: previous_ptr points to a node in a linked list.
		// Postcondition: A new node containing the given entry has been added
		// after the node that previous_ptr points to.
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
		//Precondition: head_ptr is the head pointer of a linked list.
		//Postcondition: the node returned points to the first instance of target in the list
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
		//Precondition: head_ptr is the head pointer of a linked list.
		//Postcondition: the node returned points to the first instance of target in the list		
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
		// Precondition: head_ptr is the head pointer of a linked list, and position > 0.
		// Postcondition: Pointer returned points to the node at the specified
		// position in the list. If there is no such position, then the null
		// pointer is returned.
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
		// Precondition: head_ptr is the head pointer of a linked list, and position > 0.
		// Postcondition: Pointer returned points to the node at the specified
		// position in the list. If there is no such position, then the null
		// pointer is returned.
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
		// Precondition: head_ptr is the head pointer of a linked list, with at least one node.
		// Postcondition: The head node has been removed and returned to the heap;
		// head_ptr is now the head pointer of the new, shorter linked list.
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
		//Precondition: previous_ptr points to a node in the list that is not the tail
		//Postcondition: node after previous_ptr is removed
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
	// Precondition: head_ptr is the head of a linked list
	// Postcondition: all nodes returned to heap and head_ptr is NULL
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
	// Precondition: source_ptr is the head of a linked list
	// Postcondition: head_ptr and tail_ptr are the head and tail of a new list
	// with the same elements as source_ptr
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
		//    Precondition: start_ptr and end_ptr are pointers to nodes on the same
		//    linked list, with the start_ptr node at or before the end_ptr node
		//    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
		//    new list that contains the items from start_ptr up to but not including
		//    end_ptr.  The end_ptr may also be NULL, in which case the new list
		//    contains elements from start_ptr to the end of the list.
		head_ptr = NULL;
		tail_ptr = NULL;

		if(start_ptr == end_ptr || start_ptr == NULL){return;}

		list_head_insert(head_ptr,start_ptr->data());
		tail_ptr = head_ptr;

		while(start_ptr->link() != end_ptr){
			start_ptr = start_ptr->link();
			list_insert(tail_ptr,start_ptr->data());
			tail_ptr = tail_ptr->link();
		}

	}

	size_t list_occurrences(node* head_ptr, const node::value_type& target){
		// Precondition: head_ptr is the head of a linked list
		// Postcondition: returned value is the number of times target appears
		// in the list
		node* temp = head_ptr;
		if(head_ptr == NULL) return 0;
		size_t count = 0;
		while(temp != NULL){
			if(temp->data() == target) {count++;}
			temp = temp->link();
		}
		return count;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     position > 0 and position <= list_length(head_ptr)+1.
		//     Postcondition: A new node has been added to the linked list with entry
		//     as the data. The new node occurs at the specified position in the list.
		//     (The head node is position 1, the next node is position 2, and so on.)
		//     Any nodes that used to be after this specified position have been
		//     shifted to make room for the one new node.
		assert(position > 0 && position <= list_length(head_ptr)+1);
		
		if(position == 1){list_head_insert(head_ptr,entry);}
		else {list_insert(list_locate(head_ptr,position-1),entry);}
	}

	node::value_type list_remove_at(node*& head_ptr, size_t position){
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     position > 0 and position <= list_length(head_ptr).
		//     Postcondition: The node at the specified position has been removed from
		//     the linked list and the function has returned a copy of the data from
		//     the removed node.
		node::value_type result;
		if(position == 1){
			result = head_ptr->data();
			list_head_remove(head_ptr);
			return result;
		}
		else {
			result = list_locate(head_ptr,position-1)->data();
			list_remove(list_locate(head_ptr,position-1));
			return result;
		}
	}

	// Print out list with comma separated values
    void list_print (const node* head_ptr){
        // Loop through list until NULL
        while(head_ptr != NULL){
            cout << head_ptr->data();
            // Add comma and space unless this is last value
            if(head_ptr->link() != NULL) cout << ", ";
            head_ptr = head_ptr->link();
        }
        cout << endl;
    }

    // Remove duplicates from list
    void list_remove_dups(node* head_ptr){
        node* pointer = head_ptr;
        node* duplicate = pointer;

        // Loop through entire list
        while(pointer != NULL){
            duplicate = pointer;
            // Loop through duplicate
            while(duplicate->link() != NULL){
                // Remove duplicate if found, else continue loop
                if(pointer->data() == duplicate->link()->data()) list_remove(duplicate);
                else duplicate = duplicate->link();
            }
            pointer = pointer->link();
        }
    }

    // Detect loop if found (uses Floyd's Loop Detection Algo)
    node* list_detect_loop (node* head_ptr){
        node* slow = head_ptr;
        node* fast = head_ptr;

        // Advance slow by 1 and fast by 2 each loop until found or reached end
        while(fast != NULL && fast->link() != NULL){
            slow = slow->link();
            fast = fast->link()->link();
            if(slow == fast) break;
        }
        // If reached end of loop without finding, return NULL
        if(fast == NULL || fast->link() == NULL) return NULL;
        slow = head_ptr;
        // Loop through until start of loop found
        while(slow != fast){
            slow = slow->link();
            fast = fast->link();
        }
        return slow;
    }

	// Return pointer to head pointer of copied list segment
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert(1 <= start && start <= finish && finish <= list_length(head_ptr)); // Precondition
        node* newHead = NULL;
        node* newTail = NULL;
        // Get list piece from start to finish and return list to newHead
        list_piece(list_locate(head_ptr, start), list_locate(head_ptr, finish+1), newHead, newTail);
        return newHead;
    }
    
}
