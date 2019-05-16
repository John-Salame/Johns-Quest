// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include "ValidInput.h"
#include <string>
#include <iostream>
using namespace std;


bool ValidInput::stringValidInt(string str, int lower, int upper)
{
    bool isValid = true; //true by default. Only look for cases which make this input invalid
    for(int i = 0; i < str.length(); i++)
    {
        //if some character is not a number, set isValid to false
        if(str[i] < '0' || str[i] > '9')
        {
            isValid = false;
        }
    }
    //if the input was an empty string, it is not valid
    if(str == "")
    {
        isValid = false;
    }
    
    //if the input is a number, use stoi and check to make sure it is in bounds
    if(isValid)
    {
        int num = stoi(str);
        
        //if num is too low or too high, it is invalid.
        if(num < lower || num > upper)
        {
            isValid = false;
        }
    }
    
    //if the number is invalid, clear the screen and print this statement
    if(!isValid)
    {
        std::system("clear"); //clear the screen
        cout << endl << endl;
        cout << "Invalid input! Please enter a number between " << lower << " and " << upper << "." << endl;
    }
    return isValid;
}