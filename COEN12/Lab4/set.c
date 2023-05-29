/*
 *  File Name: list.c
 *  Author: Conner Yin
 *  Date: 2/18/2022
 *  Description: defines functions outlined in list.h
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"
# include "set.h"

# define EMPTY 0
# define FILLED 1
# define DELETED 2

struct set{
    int count;
    int length;
    LIST **data;
    int(*compare)();
    unsigned(*hash)();
};

//Creates a set in O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count = 0;
    sp->length = maxElts/20; //shouldn't be maxelts 2nd paragraph 3rd section pdf
    sp->data = malloc(sizeof(LIST*)*sp->length);
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for(i=0; i<sp->length; i++)
        sp->data[i] = createList(compare);
    assert(sp->data!=NULL);
    return sp;
}

//Destroys the set one list at a time in O(n)
void destroySet(SET *sp){
    int i;
    for(i=0; i<sp->length; i++)
        destroyList(sp->data[i]);
    free(sp->data);
    free(sp);
}

//Returns number of elements in O(1)
int numElements(SET *sp){
    assert(sp!=NULL);
    return sp->count;
}

//Adds item elt to set in O(1)
void addElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int i = (sp->hash)(elt)%sp->length;
    if(findItem(sp->data[i], elt)==NULL){
        addFirst(sp->data[i], elt);
        sp->count++;
    }
}

//Removes element from the set in O(n)
void removeElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int i =(sp->hash)(elt)%sp->length;
    if(findItem(sp->data[i], elt)!=NULL){
        removeItem(sp->data[i], elt);
        sp->count--;
    }
}

//Find element in the set in O(n)
void *findElement(SET *sp, void *elt){
    assert(sp!=NULL);
    int i =(sp->hash)(elt)%sp->length;
    return findItem(sp->data[i], elt);
}

//Return all data in the element in O(n)
void *getElements(SET *sp){
    assert(sp!=NULL);
    void **temp = malloc(sizeof(void*)*sp->count);
    assert(temp!=NULL);
    int i;
    int j=0;
    for(i=0; i<sp->length; i++){
        memcpy(temp+j, getItems(sp->data[i]), sizeof(void*)*numItems(sp->data[i])); //dest, source, how many bytes
        j += numItems(sp->data[i]);
    }
    return temp;
}