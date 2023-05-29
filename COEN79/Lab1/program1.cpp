/*
Nathan Yu and Conner Yin
Lab 1 Program 1
TA told us to work together because Conner had technical issues compiling
4.6.23
Print the number of alphanumeric characters and non-alphanumeric chracters from a user's string
*/
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main(){
    int alphanum = 0;
    int other = 0;
    string str;
    cout << "Please type something\n";
    //Input line from user into str
    getline(cin,str);

    //Iterate through the string to find the amount of alphanumeric characters
    for(int i = 0; i<str.length(); i++){

        //Add to respective counter depending on if alphanumeric
        if(isalnum(str[i]))
            alphanum++;
        else if(str[i] != ' ')
            other++;
    }
    
    cout << "The number of alphanumeric characters is " << alphanum << endl;
    cout << "The number of non-alphanumeric characters is " << other << endl;
    return 0;
}