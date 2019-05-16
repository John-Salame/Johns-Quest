// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include "Inventory.h"
using namespace std;

Inventory::Inventory()
{
    Item potion("Potion", 8, 5, 0, "An item that heals wounds; heals 10 hp, but won't wake you up.");
    items[0] = potion;
    Item revive("Revive", 12, 8, 0, "A rare herbal remedy that wakes up a fainted player and restores them to 50\% health.");
    items[1] = revive;
    Item superPotion("Super Potion", 12, 8, 0, "A potion that heals 15 hp instead of 10.");
    items[2] = superPotion;
    //all other items are unimplemented
}


//set a new quantity for the item
bool Inventory::setItemQuantity(int index, int quant)
{
    bool returnValue;
    
    //check if index is valid
    if(index >= 0 && index < sizeItems)
    {
        //if quant is positive, update the quantity
        if(quant >= 0)
        {
            items[index].setQuantity(quant);
            returnValue = true;
        }
        else //negative quantity
        {
            cout << "You cannot set an item quantity to a negative number." << endl;
            returnValue = false;
        }
    }
    else //invalid index
    {
        cout << "Invalid index in setItemQuantity." << endl;
        returnValue = false;
    }
    return returnValue;
} //end of setItemQuantity function

//add deltaq to the quantity
bool Inventory::changeItemQuantity(int index, int deltaq)
{
    bool returnValue;
    if(index >= 0 && index < sizeItems)
    {
        int oldQ = items[index].getQuantity();
        
        //if the change will not produce a negative quantity, change the quantity.
        if(oldQ + deltaq >= 0)
        {
            items[index].changeQuantityBy(deltaq);
            returnValue = true;
        }
        else //new quantity would be negative
        {
            cout << "Unable to trade " << items[index].getName() << ". You can only trade up to ";
            cout << items[index].getQuantity() << " of that item." << endl;
            cout << "Message produced in Inventory::changeItemQuantity(" << index << ", " << deltaq << ")." << endl;
            returnValue = false;
        }
    }
    else //invalid index
    {
        cout << "Invalid index in changeItemQuantity." << endl;
        returnValue = false;
    }
    return returnValue;
}


//this only produces a copy; do not modify the Item it returns
Item Inventory::getItemAt(int index) const
{
    if(index >= 0 && index < sizeItems)
    {
        return items[index];
    }
    else
    {
        cout << index << " is an invalid index in the inventory. Returning default item." << endl;
        Item def; //default Item
        return def;
    }
}


//return sizeItems
int Inventory::getSizeItems() const
{
    return sizeItems;
}