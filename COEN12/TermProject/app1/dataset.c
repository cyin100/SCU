/*
 * File:        dataset.c
 * Author:      Conner Yin
 * Description: Establishes a dataset for Students IDs and ages using a set containing linked lists
 *      for each age with nodes containing each student
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "dataset.h"

struct set{
    LIST ** lists;
    int length;
    int totCount;
    int oldest;
    int youngest;
};
struct node{
    int studentID; 
    int age;
    NODE *next;
    NODE *prev;
};
struct list{
    int count;
    NODE *head; 
};

typedef struct set SET;
typedef struct node NODE;
typedef struct list LIST;

//Creates data set in O(n) time
SET *createDataSet(int maxElts){

    //Initialize variables
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL && maxElts != 0);
    sp->length = maxElts;
    sp->totCount = 0;
    sp->oldest = 0;
    sp->youngest = 0;
    sp->lists = malloc(sizeof(LIST*)*sp->length);
    int i;

    //Create empty lists with starter node
    for(i = 0; i<sp->length; i++){
        LIST *lp;
        lp = malloc(sizeof(LIST));
        assert(lp != NULL);
        lp->count = 0;

        NODE *temp = malloc(sizeof(NODE));
        assert(temp != NULL);
        lp->head = temp;
        temp->prev = temp;
        temp->next = temp;
        sp->lists[i] = lp;
    }
    return sp;
}
// Destroys data set in O(n^2) time by freeing data
void destroyDataSet(SET *sp){

    assert(sp!=NULL);
    int i;
    for(i = 0; i<sp->length; i++){
        LIST *lp = sp->lists[i];
        assert(lp != NULL);
        while(lp->count > 0){
            NODE* tempNode = malloc(sizeof(NODE));
            assert(tempNode != NULL && lp->head->next != NULL);
            tempNode = lp->head->next;
            lp->head->next = tempNode->next;
            tempNode->next->prev = lp->head;
            free(tempNode);
            lp->count--;
        }
        free(lp->head);
        free(lp);
    }
    free(sp->lists);
    free(sp);
}

//Search all students with specific age in O(n) by returning the list
void searchAge(SET *sp, int age){
    assert(sp!=NULL && age>17);
    int index = age-18;
    LIST* lp = sp->lists[index];
    assert(lp!=NULL);

    printf("SEARCH: students with age %d\n", age);
    if(lp->count == 0){
        printf("SEARCH: no students found with age %d\n", age);
        return;
    }
    NODE *pCur = lp->head->next;
    int i;
    for(i = 0; i<lp->count; i++){
        printf("%d, ", pCur->studentID);
        pCur = pCur->next;
    }
}

//Insert student into age list in O(1) by adding node to list
void insertion(SET *sp, int numID, int age){
    assert(sp!=NULL && age>17);
    assert(numID!=0);
    assert(sp->totCount<sp->length);
    int index = age-18;
    //maxAgeGap check
    if(sp->youngest == 0){
        sp->youngest = age;
        sp->oldest = age;
    }
    if(age > sp->oldest)
        sp->oldest = age;
    else if(age < sp->youngest)
        sp->youngest = age;

    //add first
    LIST *lp = sp->lists[index];
    assert(lp!=NULL);
    NODE *pNew = malloc(sizeof(NODE));
    assert(pNew!=NULL);
    pNew->studentID = numID;
    pNew->age = age;
    NODE *pCur = lp->head->next;
    pNew->prev = lp->head;
    pNew->next = pCur;
    pCur->prev = pNew;
    lp->head->next = pNew;

    //increment count
    lp->count++;
    sp->totCount++;
    return;
}

//Delete all students with specific age in O(n) by freeing list
void deletion(SET *sp, int curAge){

    //Assertions
    assert(sp!=NULL && curAge>17);
    int index = curAge-18;
    assert(sp->totCount>0);
    assert(sp->lists!=NULL);
    LIST *lp = sp->lists[index];
    assert(lp!=NULL);
    if(lp->count==0){
        printf("DELETE: no students with age %d\n", curAge);
        return;
    }

    //Update youngest and oldest
    int age = curAge;
    if(age == sp->youngest && age == sp->oldest){
        sp->youngest = 0;
        sp->oldest = 0;
    }
    else if(age == sp->youngest){
        age++;
        while(sp->lists[age-18]->count==0 && age<=30){
            age++;
        }
        sp->youngest = age;
    }
    else if(age == sp->oldest){
        age--;
        while(sp->lists[age-18]->count==0 && age>=18){
            age--;
        }
        sp->youngest = age;
    }

    //Delete list with age
    NODE* tempNode;
    printf("\nDELETE: students with age %d\n", curAge);
    while(lp->count!=0){
        tempNode = malloc(sizeof(NODE));
        assert(tempNode != NULL);
        assert(lp->head->next != NULL);
        tempNode = lp->head->next;
        printf("%d, ", tempNode->studentID);
        lp->head->next = tempNode->next;
        tempNode->next->prev = lp->head;
        free(tempNode);
        lp->count--;
        sp->totCount--;
    }
    printf("\nDELETE: deletion success!\n");
    return;
}

//Returns max age gap in O(1)
void maxAgeGap(SET *sp){
    printf("MAX AGE GAP: %d\n", sp->oldest - sp->youngest);
}
