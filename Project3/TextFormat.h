// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

//has functions to clear the screen and wait for the user to press enter to continue
class TextFormat
{
public:
    void clearScreen(); //clear the screen, then move the cursor down a few lines
    void wait(); //print "Press enter to continue" and wait for user to type something and hit enter
};

#endif