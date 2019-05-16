// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef VALIDINPUT_H
#define VALIDINPU_H

#include <string>
using namespace std;

class ValidInput
{
public:
    /**
     * @param str: the input the user provided
     * @param lower: the lowest number allowed for valid input
     * @param upper: the greatest number allowed for valid input
     */
    bool stringValidInt(string str, int lower, int upper);
};

#endif