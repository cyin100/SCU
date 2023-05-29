/*
 *  File Name: huffman.c
 *  Author: Conner Yin
 *  Date: 3/3/2022
 *  Description: Utilizies huffman coding to test pqueue.c, prints number of character occurences
 *      and how many bits they take up based on their position in priority queue tree
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>
# include "pqueue.h"
# include "pack.h"

//Define NODE, PQ and helper functions
typedef struct node NODE;
typedef struct pqueue PQ;

int depth(NODE *node);
int nodeCompare(NODE *first, NODE *second);
NODE *makeNode(int data, NODE* left, NODE* right);

int main(int argc, char *argv[]){

    //Count occurences of chars from file and store into counts array
    FILE * fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL) return -1;

    int counts[257];
    int i;
    for(i=0; i<257; i++){
        counts[i] = 0;
    }
    while(!feof(fp)){
        int c = fgetc(fp);
        counts[c]++;
    }

    //Create binary tree consisting of nonzero counts as leaves and end of file marker with 0 count
    PQ *pqueue = createQueue(nodeCompare);
    NODE* leaves[257];
    
    for(i=0; i<257; i++){
        leaves[i] = NULL;
    }
    for(i=0; i<257; i++){
        if(counts[i]>0){
            NODE* leafNode = makeNode(counts[i], NULL, NULL);
            addEntry(pqueue, leafNode);
            leaves[i] = leafNode;
        }
    }
    NODE* eofNode = makeNode(0, NULL, NULL);
    addEntry(pqueue, eofNode);
    leaves[256] = eofNode;

    //While pqueue has more than 1 entry, remove two lowest and add new parent with sum of counts
    while(numEntries(pqueue) > 1){
        NODE* first = removeEntry(pqueue);
        NODE* second = removeEntry(pqueue);
        NODE* third = makeNode(first->count+second->count, first, second);
        addEntry(pqueue, third);
    }

    //Prints data storage and then sends to pack.c for overall bits
    for(i=0; i<257; i++){
        if(leaves[i] != NULL){
            if(isprint(i)) printf("'%c': %d x %d bits = %d bits\n", i, counts[i], depth(leaves[i]), counts[i]*depth(leaves[i]));
            else printf("%03o: %d x %d bits = %d bits\n", i, counts[i], depth(leaves[i]), counts[i]*depth(leaves[i]));
        }
    }

    pack(argv[1], argv[2], leaves);
    return 0;
}

//Return depth of specific node using recursion
int depth(NODE *node){
    if(node == NULL) return 0;
    return 1+depth(node->parent);
}

//Returns positive integer if first node count > second note count and vice versa
int nodeCompare(NODE *first, NODE *second){
	return first->count - second->count;
}

//Returns node with passed in data, optionally make parent of passed in left and right node
NODE *makeNode(int data, NODE* left, NODE* right){
    NODE* newNode = malloc(sizeof(NODE));
    newNode->count = data;
    if(left != NULL && right != NULL){
        left->parent = newNode;
        right->parent = newNode;
    }
    return newNode;
}



