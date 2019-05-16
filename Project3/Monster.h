// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Weapon.h"
#include "Player.h"
using namespace std;

/**
 * Monsters are similar to the Player, except they cannot 
 * hold multiple weapons, 
 * start with random stats, 
 * or gain experience.
 */
class Monster
{
private:
    string name; //the name of the monster
    
    int hp; //health points on monster
    int maxHp; //the maximum health points the monster can have. Starts at 10.
    bool isAlive; //true if the player is alive
    
    //attributes
    double strength; //the strength attribute of the monster. Good for strong attacks.
    double attack; //the attack attribute of the monster. Describes how good your swordsmanship is. Good for normal (quick) attacks.
    double agility; //the agility attribute of the monster. Good for dodging.
    double defense; //the defense level of the monster
    
    //combat-related variables
    double vulnerability; //the monster's damage multiplier when it takes damage.
    bool canMove; //true if the monster can attack, block or use items this turn; false otherwise.
    
    Weapon weapon; //the weapon is "Fists" by default, because of Weapon's default constructor.
    int gold; //how much gold the monster is carrying
    
public:
    Monster(); //default constructor, creates "Thief" with 4 health and "Fists" weapon and 1 for each attribute
    
    //parameterized constructor
    Monster(string newName, int maxHealth, double str, double att, double ag, double def, Weapon w, int money);
    
    //a function to set the value of isAlive
    void setIsAlive(bool tf);
    //a function to set canMove
    void setCanMove(bool tf);
    
    
    /**
     * int takeDamage
     * Description: Decrease the hp of the player by <damage> * vulnerability.
     * @param damage: how much damage the attack deals without multipliers.
     * @return the amount of damage the player took to the monster
     */
    int takeDamage(double damage);
    
    void setWeapon(string name, int damage); //give the monster a weapon
    
    void setWeapon(Weapon w); //give the monster a weapon. Overload of the method above.
    
    
    string getName() const; //return the name of the monster
    int getHp() const;
    bool getIsAlive() const; //returns isAlive
    double getStrength() const;
    double getAttack() const;
    double getAgility() const;
    double getDefense() const;
    bool getCanMove() const; //returns canMove
    Weapon getWeapon() const;
    int getGold() const; //return how much gold the Monster is carrying
    
    void printDetails() const; //prints name, health, stats, and weapon info.
    
    void setVulnerability(double d);
    void gainGold(int amount);
};

#endif