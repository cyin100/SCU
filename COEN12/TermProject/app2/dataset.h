/*
 * File:        dataset.h
 * Author:      Conner Yin
 * Description: Outlines functions to be defined in dataset.c
 */

# include <stdbool.h>

typedef struct set SET;

SET *createDataSet(int maxElts);
void destroySet(SET *sp);
void *searchID(SET *sp, int id);
void insert(SET *sp, int id, int age);
void delete(SET *sp, int id);