// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "Player.h"
#include "Weapon.h"
#include "Inventory.h"
using namespace std;

class Shop
{
private:
    Inventory itemStock; //Holds the quantity of each item available. There will be 5 items in the game, at most.
    vector<Weapon> weaponStock; //a vector of weapons for sale. Buy prices and sell prices are stored in the Weapon object.
public:
    Shop(); //default constructor
    
    /**
     * Constructor which sets the quantities of the items.
     * @param quantities: array of ints representing the quantity each item should have in the Inventory
     * @param size: the number of elements in the quantities array
     */
    Shop(int quantities[], int size);
    
    
    void addWeapon(Weapon w); //add a weapon to the weaponStock vector
    
    void printItemOptions(); //print out the name, description, price, and quantity of each item in stock
    void printWeaponOptions(); //print out the name, price, and quantity of each weapon in stock
    
    bool buyItem(Player& player); //have a player buy an item from the shop
    bool sellItem(Player& player); //have a player sell an item to the shop
    
    bool buyWeapon(Player& player); //have a player buy a weapon from the shop
    bool sellWeapon(Player& player); //have a player sell a weapon to the shop
};

#endif