// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;

/**
 * Defines an item by name, description, buyPrice, sellPrice, and quantity.
 * Functions relating to item usage are inside Player.
 */
class Item
{
private:
    string name;
    int buyPrice; //how much it costs for a player to buy the item
    int sellPrice; //how much the player can sell the item for
    int quantity; //how many of this item exists where it is stored
    string description;
public:
    Item(); //default, makes potion with 0 quantity
    
    /**
     * Parameterized Constructor
     * @param n: name
     * @param bp: buy price (price to buy from store)
     * @param sp: sell price (price when selling to store)
     * @param q: quantity
     * @param des: description
     */
    Item(string n, int bp, int sp, int q, string des); //parameterized constructor
    
    
    void setQuantity(int newQ); //directly change the quantity member variable of the item
    void changeQuantityBy(int amount); //add amount to quantity
    
    string getName() const;
    int getBuyPrice() const;
    int getSellPrice() const;
    int getQuantity() const;
    string getDescription() const;
};

#endif