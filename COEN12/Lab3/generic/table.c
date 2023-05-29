# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

static int search(SET *sp, void *elt, bool *found);

//Variables for struct set, now includes compare and hash functions
struct set{
    int count;
    int length;
    void **data;
    char *flags;
    int(*compare)();
    unsigned(*hash)();
};

//Creates hash table in O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)()){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(void*)*maxElts);
    sp->flags = malloc(sizeof(char)*maxElts);
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for(i=0; i<maxElts; i++){
        sp->flags[i] = EMPTY;
    }
    assert(sp->data!= NULL);
    return sp;
}

//Destroys hash table in O(n)
void destroySet(SET *sp){
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

//Returns num elements O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp-> count;
}

//Adds element in hash table, uses search to find suitable locn
//Expected O(1) Worst case O(n)
void addElement(SET *sp, void *elt){
    assert (sp != NULL && elt != NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if (!found){
        assert(sp->count < sp->length);
        assert(elt != NULL);
        sp->data[locn] = elt;
        sp->flags[locn] = FILLED;
        sp->count++;
    }
}

//Remove element in hash table, search for element and remove if found
//Expected O(1) Worst case O(n)
void removeElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if(found){
        sp->flags[locn] = DELETED;
        sp->count--;
    }
}

//Find element in hash table using search helper
//Expected O(1) Worst case O(n)
void *findElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if(found) return sp->data[locn];
    else return NULL;
}

//Get all elements in hash table in O(n)
//Sequentially returns all data with FILLED flag at locn
void *getElements(SET *sp){
    assert(sp!=NULL);
    void **elts = malloc(sizeof(void*)*sp->count);
    int n = 0;
    int i;
    for(i=0; i<sp->length; i++){
        if(sp->flags[i] == FILLED){
            elts[n] = sp->data[i];
            n++;
        }
    }
    return elts;
}

//Search for element in hash table, uses sp->hash and sp->compare to test if data is same
//Search until found or hit empty flag, then return false or first locn of DELETED flag
//Expected O(1) Worst case O(n)
static int search(SET *sp, void *elt, bool *found){
    int locn = (*sp->hash)(elt)%sp->length;
    int i = 0;
    int firstDel = -1;
    for(i=0; i<sp->length; i++){
        locn = (locn+i)%sp->length;
        if(sp->flags[locn]==FILLED){
            if((*sp->compare)(sp->data[locn], elt) == 0){
                *found = true;
                return locn;
            }
        } else if(sp->flags[locn]==DELETED)
            firstDel = locn;
        else break;
    }
    *found = false;
    if(firstDel != -1) return firstDel;
    return locn;
}