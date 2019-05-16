// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
using namespace std;

class Weapon
{
private:
    string name; //the name of the weapon
    int damage; //the base damage of the weapon.
    
    int buyPrice;
    int sellPrice;
public:
    Weapon(); //constructs the "Fist" weapon with base damage 1.
    Weapon(string name, int damage); //constructs a weapon based on the stats
    Weapon(string name, int damage, int bp, int sp); //parameterized constructor with buy price and sell price
    void printDetails() const; //prints name and damage. FOR TESTING PURPOSES ONLY
    
    string getName() const; //return the name of the weapon
    int getDamage() const;
    int getBuyPrice() const;
    int getSellPrice() const;
};

#endif