/*
Nathan Yu and Conner Yin
Lab 1 Program 3
TA told us to work together because Conner had technical issues compiling
4.6.23
Read a file. Remove all non-letters and make letters uppercase. Print all remaining words that are 10+ characters
*/
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){

    //assert that a filename is included
    assert(argc == 2);

    string str;
    string word;
    string filename = argv[1];

    //create file pointer and open file
    ifstream in_file;
    in_file.open(filename);

    //iterate through each word in the file until the end
    while(in_file && in_file.peek() != EOF){
        //for each word we start with an empty string
        word = "";
        //set str to the next word
        in_file >> str;

        //iterate through each word
        for(int i = 0; i<str.length();i++){
            //add the alphabetical letters from str to the new word and make them uppercase
            if(isalpha(str[i])){
                word += (toupper(str[i]));
            }
        }
        //if the word is 10 characters or longer, print it
        if(word.length() >= 10){
            cout << word << endl;
        }
    }
    in_file.close();
    return 0;
}