/*
    File Name: count.c
    Author: Conner Yin
    Date: 1/6/2022
    Description: counts the number of words in a text file
*/

//Include libraries
# include <stdio.h>
# include <stdlib.h>

//Set maximum word length to 30
# define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
    //Initialize wordCount to 0, word to char array with max length 30
    char word[MAX_WORD_LENGTH+1];
    int wordCount = 0;
     
    //Open file pointer and point to file outlined in second arg
    FILE * fp;

    if(argc == 2){
        fp = fopen(argv[1], "r");

        //Process file not found error
        if(fp == NULL){
            printf("Cannot open file\n");
            return -1;
        }

    //Process incorrect number of arguments
    } else{
        printf("Incorrect number of arguments\n");
        return -1;
    }
    
    //While string is found in file, read into word and increment wordCount
    while(fscanf(fp, "%s", word) > 0){
        wordCount++;
    }

    //Print wordCount, close file
    printf("%d total words\n", wordCount);
    fclose(fp);
    return 0;
}