// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include "TextFormat.h"
using namespace std;

//THIS IS NOT A MEMBER FUNCTION
void TextFormat::clearScreen()
{
    cout << flush; //make sure nothing else needs to cout.
    std::system("clear"); //clear the screen
    cout << endl << endl << endl; //make the first line appear lower
}


//wait for the user to type something and press enter before continuing the program.
void TextFormat::wait()
{
    cout << "Press enter to continue." << endl;
    string wait;
    getline(cin, wait);
}