// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef INVENTORY_H
#define INVENTORY_H


#include "Item.h"
using namespace std;


/**
 * Inventory is an array of 5 items.
 * The default constructor makes the 5 items, all with 0 quantity
 */
class Inventory
{
private:
    //I had to make this static so the program would let me compile statements like shop1 = shop2.
    static const int sizeItems = 5; //size of the items array
    Item items[5];
public:
    Inventory(); //default constructor makes the 5 items used universally by players and shops
    
    /**
     * Set a new quantity for the item.
     * Only do this if index is valid and quant is not negative.
     * @return true if the quantity is changed.
     * @return false if the index is invalid or quant is negative.
     */
    bool setItemQuantity(int index, int quant);
    
    //Add deltaq to the quantity. Only do this if the index is valid and the change would not make quantity negative.
    bool changeItemQuantity(int index, int deltaq);
    
    Item getItemAt(int index) const; //this only produces a copy; do not modify the Item it returns
    int getSizeItems() const; //return sizeItems
};

#endif