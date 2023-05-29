/*
Nathan Yu and Conner Yin
Lab 1 Program 4
TA told us to work together because Conner had technical issues compiling
4.6.23
Randomly guess a user's number 1-20
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
using namespace std;

int main(){
    string response;
    int steps = 1;
    bool guessed = false;
    set<int> set;

    //Wait for user to start, generate random number from 1-20
    cout << "Think of a number between 1 and 20. Press enter when you are ready." << endl;
    cin.ignore();
    int curGuess = rand() % 20 + 1;

    //Repeat loop until conditions are broken
    while(true){

        //Ask user for 'Y' or 'N'
        cout << "Is the number " << curGuess << "? Y or N ";
        cin >> response;

        //If response is 'Y', print # of steps and break out of loop
        if(response == "Y" || response == "y" || response == "yes"){
            cout << "I found the number in " << steps << " steps" << endl;
            break;
        }

        //If response is 'N', add to steps, go to next guess
        else if(response == "N" || response == "n" || response == "no"){
            curGuess = rand() % 20 + 1;
            steps++;
        }

        //If response is neither, prompt them to re-enter
        else{
            cout << "Only enter Y or N" << endl;
        }
    }
    
    return 0;
}