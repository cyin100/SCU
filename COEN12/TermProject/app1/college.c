/*
 * File:        college.c
 * Author:      Conner Yin
 * Description: Contains the main function for testing application 1
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "dataset.h"
# include <time.h>

typedef struct set SET;

int main(int argc, char *argv[]){
    //Create data set and insert values
    SET *set = createDataSet(3000);
    int age, random, i;
    int ID = 0;
    srand(time(0));
    for(i=0; i<1000;i++){
        age = rand()%13+18;
        random = rand()%2+1;
        ID += random;
        insertion(set, ID, age);
    }
    //Search and delete all students with specific age, find max age gap, destroy set
    age = (rand() % 13) +18;
    searchAge(set, age);
    int curAge = (rand() % 13) +18;
    deletion(set, curAge);
    maxAgeGap(set);
    destroyDataSet(set);
}