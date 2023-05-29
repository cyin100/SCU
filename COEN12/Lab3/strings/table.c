# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

static int search(SET *sp, char *elt, bool *found);

//Variables for struct set
struct set{
    int count;
    int length;
    char **data;
    char *flags;
};

//Helper method for hashing strings
unsigned strhash(char *s)
{
    unsigned hash = 0;
    while (*s != '\0')
    hash = 31 * hash + *s ++;
    return hash;
}

//Creates hash table in O(n)
SET *createSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    sp->flags = malloc(sizeof(char)*maxElts);
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
    int i;
    for (i=0; i<sp->length; i++)
        if(sp->flags[i] == FILLED)
            free(sp->data[i]);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

//Returns num elements in O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp-> count;
}

//Adds element in hash table, uses search to find suitable locn
//Expected O(1) Worst case O(n)
void addElement(SET *sp, char *elt){
    assert (sp != NULL && elt != NULL);
    bool found;
    char *copy;
    int locn = search(sp, elt, &found);
    if (!found){
        assert(sp->count < sp->length);
        copy = strdup(elt);
        assert(copy != NULL);
        sp->data[locn] = copy;
        sp->flags[locn] = FILLED;
        sp->count++;
    }
}

//Remove element in hash table, search for element and remove if found
//Expected O(1) Worst case O(n)
void removeElement(SET *sp, char *elt){
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if(found){
        free(sp->data[locn]);
        sp->flags[locn] = DELETED;
        sp->count--;
    }
}

//Find element in hash table using search helper
//Expected O(1) Worst case O(n)
char *findElement(SET *sp, char *elt){
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int locn = search(sp, elt, &found);
    if(found) return sp->data[locn];
    else return NULL;
}

//Get all elements in hash table in O(n)
//Sequentially returns all data with FILLED flag at locn
char **getElements(SET *sp){
    assert(sp!=NULL);
    char **elts = malloc(sizeof(char*)*sp->count);
    int n = 0;
    int i;
    for(i=0; i<sp->length; i++){
        if(sp->flags[i] == FILLED){
            elts[n] = strdup(sp->data[i]);
            n++;
        }
    }
    return elts;
}

//Search for element in hash table, uses strhash and strcmp to test if data is same
//Search until found or hit empty flag, then return false or first locn of DELETED flag
//Expected O(1) Worst case O(n)
static int search(SET *sp, char *elt, bool *found){
    int locn;
    int i = 0;
    int firstDel = -1;
    for(i=0; i<sp->length; i++){
        locn = (strhash(elt)+i)%sp->length;
        if(sp->flags[locn]==FILLED){
            if(strcmp(sp->data[locn], elt)==0){
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