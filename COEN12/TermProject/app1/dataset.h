/*
 * File:        dataset.c
 * Author:      Conner Yin
 * Description: Outlines functions to be defined in dataset.c
 */

# include <stdbool.h>

typedef struct set SET;
typedef struct node NODE;
typedef struct list LIST;

SET *createDataSet(int maxElts);
void destroyDataSet(SET *sp);
void searchAge(SET *sp, int age);
void insertion(SET *sp, int numID, int age);
void deletion(SET *sp, int curAge);
void maxAgeGap(SET *sp);
