/*
 * File:        dataset.c
 * Author:      Conner Yin
 * Description: Establishes a dataset for Student IDs and ages with a
 *      hash table that is represented using an array
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "dataset.h"

struct set {
    int length;
    int data[3000];
};

typedef struct set SET;

//Creates data set in O(n) 
SET *createDataSet(int maxElts){
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL && maxElts != 0);
    sp->length = maxElts;
    int i=0;
    for(i=0; i<sp->length; i++)
        sp->data[i] = 0;
    return sp;
}

//Destroy data set in O(1) by freeing set pointer
void destroyDataSet(SET *sp){
    assert(sp != NULL);
    free(sp);
}

//Search for specific ID in O(1) by hashing ID
void *searchID(SET *sp, int id){
    assert(sp != NULL);
    if(sp->data[id] != 0)
        printf("SEARCH: found student id %d with age %d\n", id, sp->data[id]);
    else
        printf("SEARCH: no student found with id %d\n", id);
}

//Insert age into specific ID in O(1) by hashing ID
void insert(SET *sp, int id, int age){
    assert(sp != NULL && sp->data != NULL);
    sp->data[id] = age;
}

//Delete user ID in O(1) by setting age to 0
void delete(SET *sp, int id){
    assert(sp != NULL);
    if(sp->data[id] !=0)
        printf("DELETE: succesfully deleted student %d\n", id);
    else
        printf("DELETE: no student found at id %d\n", id);
    sp->data[id] = 0;
}