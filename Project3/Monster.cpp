// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include "Monster.h"
using namespace std;

//default constructor
Monster::Monster()
{
    name = "Thief";
    maxHp = 4;
    hp = maxHp;
    isAlive = true;
    
    strength = 1;
    attack = 1;
    agility = 2;
    defense = 1;
    
    vulnerability = 1;
    canMove = true;
    //weapon is already the default: Fists
    gold = 10;
    
    //knife with 1 damage, buy price 5, sell price 3
    Weapon knife("knife", 1, 5, 3);
    setWeapon(knife);
}

//this will be used when creating monsters by reading a file
Monster::Monster(string newName, int maxHealth, double str, double att, double ag, double def, Weapon w, int money)
{
    name = newName;
    maxHp = maxHealth;
    strength = str;
    attack = att;
    agility = ag;
    defense = def;
    weapon = w;
    gold = money;
    
    isAlive = true;
    canMove = true;
    vulnerability = 1;
    hp = maxHp;
}

//a function to set the value of isAlive
void Monster::setIsAlive(bool tf)
{
    isAlive = tf;
}
//a function to set canMove
void Monster::setCanMove(bool tf)
{
    canMove = tf;
}


int Monster::takeDamage(double baseDamage)
{
    int damage = baseDamage * vulnerability; //damage taken, rounded down.
    hp = hp - damage; //take the damage by subracting from hp.
    
    
    //if the monster is out of hp, kill the monster.
    if(hp <= 0)
    {
        //if it was overkill, change damage to how much health the monster had left before it died.
        damage = damage + hp;
        hp = 0;
        isAlive = false;
    }
    cout << name << " took " << damage << " damage." << endl << endl;
    if(!isAlive)
    {
        cout << name << " fainted." << endl << endl;
    }
    
    return damage;
}


void Monster::setWeapon(string name, int damage)
{
    Weapon newWeapon(name, damage);
    weapon = newWeapon; //set the member variable "weapon" of Monster.
}

//overload of first setWeapon method
void Monster::setWeapon(Weapon w)
{
    weapon = w;
}


string Monster::getName() const
{
    return name;
}
int Monster::getHp() const
{
    return hp;
}
bool Monster::getIsAlive() const
{
    return isAlive;
}
double Monster::getStrength() const
{
    return strength;
}
double Monster::getAttack() const
{
    return attack;
}
double Monster::getAgility() const
{
    return agility;
}
double Monster::getDefense() const
{
    return defense;
}
bool Monster::getCanMove() const
{
    return canMove;
}
Weapon Monster::getWeapon() const
{
    return weapon;
}
int Monster::getGold() const
{
    return gold;
}


//FOR TESTING PURPOSES
void Monster::printDetails() const
{
    cout << "Name: " << name << endl;
    cout << "Current health: ";
    if(hp > 0)
    {
        cout << hp << " HP" << endl;
    }
    else
    {
        cout << "unconscious." << endl;
    }
    cout << "Max Health: " << maxHp << " HP" << endl;
    cout << "Can move: ";
    if(canMove)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    cout << "Strength: " << strength << endl;
    cout << "Attack: " << attack << endl;
    cout << "Agility: " << agility << endl;
    cout << "Defense: " << defense << endl;
    
    weapon.printDetails();
    cout << endl;
}


void Monster::setVulnerability(double d)
{
    vulnerability = d;
}

//add gold (or subtract if amount is negative) to coin pouch
void Monster::gainGold(int amount)
{
    gold += amount;
}