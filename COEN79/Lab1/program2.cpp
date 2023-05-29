/*
Nathan Yu and Conner Yin
Lab 1 Program 2
TA told us to work together because Conner had technical issues compiling
4.6.23
Reverse a string of digits and use setw to space them out
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
using namespace std;

int main(){
    string str;
    
    cout << "Please enter a 10 digit number" << endl;

    //Take user input, assert str length = 10 and every element is a number
    cin >> str;
    assert(str.length()==10);
    for(int n = 0; n<str.length();n++){
        assert(isdigit(str[n]));
    }
    

    //Repeat 5 times, incrementing space at beginning by 1 each time
    for(int i=0; i<5; i++){
        cout << setw(i) << "" << str << setw(i+5);

        //Print the letters of str in reverse
        for(int j=str.length()-1; j>=0; j--){
            cout << str[j];
        }
        cout << endl;
    }
    return 0;
}