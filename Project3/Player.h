// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3 / Hmwk9

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Weapon.h"
#include "Inventory.h"
using namespace std;

/**
 * Holds attributes and gameplay features for the Player.
 */
class Player
{
private:
    string name;
    int hp; //the health points of the player. Starts at 10.
    int maxHp; //the maximum health points the player can have. Starts at 10.
    bool isAlive; //true if the player is alive
    
    //attributes
    double strength; //the strength attribute of the player. Good for strong attacks.
    double attack; //the attack attribute of the player. Describes how good your swordsmanship is. Good for normal (quick) attacks.
    double agility; //the agility attribute of the player. Good for dodging.
    double defense; //the defense level of the player
    
    //combat-related variables
    double vulnerability; //the player's damage multipiyer when they take damage.
    bool canMove; //true if the player can attack, block, or use items this turn; false otherwise.
    
    //stuff related to inventory
    const int sizeWeapons = 5; //max number of weapons (5)
    vector<Weapon> weapons; //inventory of weapons; the player can have up to 10 weapons.
    Weapon weapon; //the weapon the player is currently using
    int gold; //how much money the player has
    Inventory items; //holds an array of 5 items
    
    
public:

    /**
     * Default constructor,
     * Sets name to "Brave Hero"
     * Sets isAlive to true;
     * Sets max hp to 10;
     * Sets each attribute to 1 and then randomly distributes 6 more points among the attributes and max health;
     * Sets hp equal to maxHp;
     * Sets gold equal to 0.
     */
    Player();
    
    //PARAMETERIZED CONSTRUCTOR FOR PLAYER. USE THIS WHEN LOADING SAVES.
    Player(string newName, int newHp, int newMaxHp, double str, double att, double ag, double def, int newGold);
    
    //add a num extra stats to the player, randomly distributed amont maxHp, str, att, ag, and def.
    void addRandomStats(int num);
    
    //a function to set the value of isAlive
    void setIsAlive(bool tf);
    //a function to set canMove
    void setCanMove(bool tf);
    
    void setHp(int amount); //if amount is between 0 and maxHp, directly set the value of hp equal to amount.
    
    void setMaxHp(int amount); //set the max HP of a player to amount. Useful for recruiting players in high level areas.
    
    /**
     * int takeDamage
     * Description: Decrease the hp of the player by <damage> * vulnerability.
     * If the player's health dips below 0, set it to 0.
     * Print out how much damage the player took.
     * @param damage: how much damage the attack deals without multipliers.
     * @return the amount of damage the player took to the monster
     */
    int takeDamage(double damage);
    
    //heal this player. Only works if amount is nonzero and positive. Also set canMove to true.
    void heal(int amount);
    
    
    /**
     * Description: Change currentWeapon to 
     * 
     * @param weaponIndex: the index of the weapon in the array which we will switch to.
     * @output "Switched to <name of new weapon>" if successful
     */
    void switchWeapons(int weaponIndex);
    
    //getters
    string getName() const;
    int getHp() const;
    int getMaxHp() const;
    bool getIsAlive() const; //returns isAlive
    double getStrength() const;
    double getAttack() const;
    double getAgility() const;
    double getDefense() const;
    bool getCanMove() const; //returns canMove
    int getNumWeapons() const; //returns the current size of weapons vector
    Weapon getWeapon() const;
    int getGold() const;
    
    
    void showInventory() const; //print out the player's items
    
    void showWeaponInventory() const; //print out all of the player's weapons in list form
    
    void printDetails() const; //prints name, health, stats, and weapon info.
    
    
    //setters / mutators
    void setName(string newName);
    void setVulnerability(double d);
    void gainStrength(double amount); //gain strength experience
    void gainAttack(double amount); //gain attack experience
    void gainAgility(double amount); //gain agility experience
    void gainDefense(double amount); //gain defense experience
    void gainGold(int amount); //add gold to coin pouch (or subtract if amount is negative.)
    bool addWeapon(Weapon w); //attempt to add a weapon to weapons; return true if it is added.
    
    
    /**
     * Remove a weapon from an index of the weapons vector.
     * If you were holding that weapon, change weapon member variable to fist.
     * Return true if the weapon was removed.
     * Return false if the weapon was not removed (invalid index)
     */
    bool removeWeapon(int index);
    
    Weapon getWeaponAt(int index) const; //return the weapon at the index (or fist if index is invalid)
    
    //code for dealing with player's items
    Item getItemAt(int index) const; //return the item at the index of inventory (or default item is index is invalid)
    void changeItemQuantity(int index, int deltaq); //from another class, change the quantity of an item in this player's inventory
    
    
};

#endif