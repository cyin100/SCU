/*
 *  File Name: unsorted.c
 *  Author: Conner Yin
 *  Date: 1/20/2022
 *  Description: defines functions outlined in set.h for
 *               sorted data set
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

static int search(SET *sp, char *elt, bool *found);

// Define variables count, length, and data
struct set{
    int count;
    int length;
    char **data;
};

// Creates set in O(n)
SET *createSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp ->data!= NULL);
    return sp;
}


// Frees memory for the set in O(n)
void destroySet(SET *sp){
    assert(sp != NULL);
    int i;
    for (i=0; i<sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
}

// Returns number of elements in set in O(1)
int numElements(SET *sp){
    return sp->count;
}

// Adds element to set in O(n)
void addElement(SET *sp, char *elt){
    bool found;
    int idx = search(sp, elt, &found);
    if(!found){
        int i;
        
        for(i=sp->count; i>idx; i--)
            sp->data[i] = sp->data[i-1];
        sp->count++;
        sp->data[idx] = strdup(elt);
    }
}

// Removes element from set in O(n)
void removeElement(SET *sp, char *elt){
    bool found;
    int idx = search(sp, elt, &found);
    if(found){
        int i;
        free(sp->data[idx]);
        for(i = idx+1; i<sp->count; i++)
            sp->data[i-1] = sp->data[i];
        sp->count--;
    }
}

// Returns element in O(n)
char *findElement(SET *sp, char *elt){
    bool found;
    int index = search(sp, elt, &found);
    if(found)
        return sp->data[index];
    return NULL;
}

// Returns list of elements in O(n)
char **getElements(SET *sp){
    char **dest;
    dest = malloc(sizeof(char*)*sp->count);
    memcpy(dest, sp->data, sizeof(char*)*sp->count); //memcpy(dest, source, size (bytes))
    return dest;
}

// Returns index of specified element using binary search in O(logn)
static int search(SET *sp, char *elt, bool *found){
    int low = 0;
    int high = sp->count-1;
    while(low <= high){
        int mid = (low+high)/2;
        if(strcmp(sp->data[mid], elt) == 0){
            *found = true;
            return mid;
        }
        if(strcmp(sp->data[mid], elt) < 0){
            low = mid+1;
        }
        else high = mid-1;    
    }
    *found = false;
    return low;
}