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

struct node{
    void *data; 
    struct node *next;
    struct node *prev;
};
typedef struct node NODE;

struct list{
    int count;
    struct node *head;
    int (*compare)(); 
};

//Creates empty list with dummy node in O(1)
LIST *createList(int (*compare)()){    
	struct list *lp;    
	lp = malloc(sizeof(struct list));    
	assert(lp != NULL);    
	lp->count = 0;    
	lp->compare = compare;    
	NODE *dummy = malloc(sizeof(struct node));    
	assert(dummy != NULL);    
	dummy->next = dummy;
    dummy->prev = dummy;  
    lp->head = dummy; 
	return lp;
}

//Destroys list by traversing and freeing in O(n)
void destroyList(LIST *lp) {
    assert(lp != NULL);
    NODE *pCur = lp->head->next;
    while (pCur!=lp->head){
        NODE *temp = pCur;
        pCur = pCur->next;
        free(temp);
    }
    free(lp->head);
    free(lp);
}

//Returns number of items in O(1)
int numItems(LIST *lp){
    assert(lp != NULL);
    return lp->count;
}

//Adds an item to head of list in O(1)
void addFirst(LIST *lp, void *item){
    assert(lp != NULL);
    NODE *pNew, *pNext;
    pNext = lp->head->next;

    pNew = malloc(sizeof(struct node));  
    pNew->data = item;
    pNew->prev = lp->head;
    pNew->next = lp->head->next;

    lp->count++;
    lp->head->next = pNew;
    pNext->prev = pNew;
}

//Adds item to the tail of a list in O(1)
void addLast(LIST *lp, void *item){
    assert(lp != NULL);
    NODE *pNew, *pPrev;
    pPrev = lp->head->prev;

    pNew = malloc(sizeof(struct node));  
    pNew->data = item;
    pNew->prev = pPrev;
    pNew->next = lp->head;

    lp->count++;
    lp->head->prev = pNew;
    pPrev->next = pNew;
}

//Remove the head in the list in O(1)
void *removeFirst(LIST *lp){
    assert(lp != NULL && lp->count>0);
    NODE *temp = malloc(sizeof(NODE));
    temp = lp->head->next;
    lp->head->next = temp->next;
    temp->next->prev = lp->head;
    lp->count++;
    void *data = temp->data;
    free(temp);
    return data;
}

//Remove the tail in the list in O(1)
void *removeLast(LIST *lp){
    assert(lp != NULL && lp->count>0);
    NODE *temp = malloc(sizeof(NODE));
    temp = lp->head->prev;
    lp->head->prev = temp->prev;
    temp->prev->next = lp->head;
    lp->count--;
    void *data = temp->data;
    free(temp);
    return data;
}

//Return the head/first item in list in O(1)
void *getFirst(LIST *lp){
    assert(lp != NULL && lp->count>0);
    return lp->head->next->data;
}

//Return tail/last item in list in O(1)
void *getLast(LIST *lp){
    assert(lp != NULL && lp->count>0);
    return lp->head->prev->data;
}

//Searches and removes an item from list by traversing
//through in O(n)
void removeItem(LIST *lp, void *item){
    assert(lp != NULL);
    if(lp->count != 0){
        NODE *pCur = lp->head->next;
        while(pCur != lp->head){
            if ((*lp->compare)(pCur->data, item) == 0){
                pCur->prev->next = pCur->next;
                pCur->next->prev = pCur->prev;
                free(pCur);
                lp->count--;
                return;
            }
            pCur = pCur->next;
        }
    }
}

//Finds item in list by traversing through in O(n)
void *findItem(LIST *lp, void *item){
    assert(lp != NULL);
    NODE *pCur = lp->head->next;
    while(pCur != lp->head){
        if ((*lp->compare)(pCur->data, item) == 0)
            return pCur->data;
        pCur = pCur->next;
    }
    return NULL;
}

//Returns an array of all elements in O(n)
void *getItems(LIST *lp){
    assert(lp!=NULL);
    void **elts = malloc(sizeof(void*)*lp->count);
    NODE *p = lp->head->next;
    int i=0;
    while(p != lp->head){
        elts[i] = p->data;
        p = p->next;
        i++;
    }
    return elts;
}