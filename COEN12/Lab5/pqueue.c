/*
 *  File Name: pqueue.c
 *  Author: Conner Yin
 *  Date: 2/24/2022
 *  Description: defines functions outlined in pqueue.h to implement
 *      a priority queue using an array
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "pqueue.h"
# define p(x) (x-1)/2
# define l(x) x*2+1
# define r(x) x*2+2

//Define pqueue variables
struct pqueue {
    int count;
    int length;
    void **data;  
    int (*compare)();
};

//Creates priority queue initialized length 10 in O(1) 
PQ *createQueue(int (*compare)()){
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = 10;
    pq->data = malloc(sizeof(void*)*pq->length);
    pq->compare = compare;
    return pq;
}

//Destroys priority queue by freeing data in O(n)
void destroyQueue(PQ *pq){
    assert(pq != NULL);
    int i;
    for(i=0; i<pq->count; i++){
        free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
}

//Returns number of entries in O(1)
int numEntries(PQ *pq){
    assert(pq != NULL);
    return pq->count;
}

//Add entry to pq by O(logn)
void addEntry(PQ *pq, void *entry){

    //Reallocate double memory if reached limit
    assert(pq!=NULL && entry!=NULL);
    int loc = pq->count;
    if(pq->count == pq->length){
        pq->length = pq->length*2;
        pq->data = realloc(pq->data, sizeof(void*)*pq->length);
    }

    pq->data[loc] = entry;

    //If data > p(loc) then swap
	while (loc>0 && pq->compare(pq->data[loc], pq->data[p(loc)])<0) {
		void* temp = pq->data[p(loc)];
		pq->data[p(loc)] = pq->data[loc];
		pq->data[loc] = temp;
		loc = p(loc);
	}
	pq->count++;	
}

//Remove entry in O(logn)
void *removeEntry(PQ *pq){

    //Define initial loc and smallest to keep track
    assert(pq!=NULL);
    void* root = pq->data[0];
	int loc = 0;
    int smallest = l(loc);
    pq->data[0] = pq->data[pq->count-1];
	pq->count--;

    //While left child exists, find smaller of children and swap with p(loc)
	while (l(loc)<pq->count){
        smallest = l(loc);
		if (r(loc)<pq->count) {
			if (pq->compare(pq->data[l(loc)], pq->data[r(loc)]) < 0) smallest = l(loc);
            else smallest = r(loc);
		}
		
		if (pq->compare(pq->data[smallest],pq->data[loc])<0) {
			void* temp = pq->data[smallest];
			pq->data[smallest] = pq->data[loc];
			pq->data[loc] = temp;
			loc=smallest;											
		}
		else break;
	}
	return root;	
}