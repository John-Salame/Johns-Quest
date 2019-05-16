// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include "Item.h"
#include <iostream>
using namespace std;

Item::Item()
{
    name = "Unimplemented";
    buyPrice = 0;
    sellPrice = 0;
    quantity = 0;
    description = "This item has not been implemented in the game.";
}


/**
 * Parameterized Constructor
 * @param n: name
 * @param bp: buy price (price to buy from store)
 * @param sp: sell price (price when selling to store)
 * @param q: quantity
 * @param des: description
 */
Item::Item(string n, int bp, int sp, int q, string des)
{
    name = n;
    buyPrice = bp;
    sellPrice = sp;
    quantity = q;
    description = des;
}


void Item::setQuantity(int newQ)
{
    quantity = newQ;
}

//add amount to the quantity
void Item::changeQuantityBy(int amount)
{
    quantity += amount;
}


    
string Item::getName() const
{
    return name;
}
int Item::getBuyPrice() const
{
    return buyPrice;
}
int Item::getSellPrice() const
{
    return sellPrice;
}
int Item::getQuantity() const
{
    return quantity;
}
string Item::getDescription() const
{
    return description;
}