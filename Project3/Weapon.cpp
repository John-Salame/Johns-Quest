// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include "Weapon.h"
using namespace std;

//default constructor
Weapon::Weapon()
{
    name = "fist";
    damage = 1;
    buyPrice = 0;
    sellPrice = 0;
}

//parameterized constructor
Weapon::Weapon(string nameParam, int damageParam)
{
    name = nameParam;
    damage = damageParam;
    buyPrice = 0;
    sellPrice = 0;
}


//parameterized constructor 2
Weapon::Weapon(string nameParam, int damageParam, int bp, int sp)
{
    name = nameParam;
    damage = damageParam;
    buyPrice = bp;
    sellPrice = sp;
}

//THIS FUNCION IS ONLY HERE FOR TESTING
void Weapon::printDetails() const
{
    cout << "Weapon: " << name << endl;
    cout << "Weapon damage: " << damage << endl;
}


string Weapon::getName() const
{
    return name;
}
int Weapon::getDamage() const
{
    return damage;
}
int Weapon::getBuyPrice() const
{
    return buyPrice;
}
int Weapon::getSellPrice() const
{
    return sellPrice;
}