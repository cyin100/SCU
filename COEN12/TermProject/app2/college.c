/*
 * File:        college.c
 * Author:      Conner Yin
 * Description: Contains the main function for testing application 2
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>
# include "dataset.h"

typedef struct set SET;

int main(int argc, char *argv[]){

    SET *set = createDataSet(3000);

    //Generates random user IDs and ages and enters into database
    int i, id = 0;
    srand(time(0));
    for(i=0; i<1000; i++){
        int random = rand()%2+1;
        id += random;
        int age = rand()%13+18;
        insert(set, id, age);
    }
    
    //Searches random user, then deletes random user from database and then destroys set
    int randomID = rand()%2000;
    searchID(set, randomID);
    randomID = rand()%2000;
    delete(set, randomID);
    destroyDataSet(set);
    return 0;
}

