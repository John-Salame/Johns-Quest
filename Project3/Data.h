// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef DATA_H
#define DATA_H

#include <string>
#include "Weapon.h"
#include "Monster.h"
#include "Region.h"
using namespace std;

/*
The Data class handles everything file related except for saving and loading saves, both of which are in Story.
Information about every possible Weapon, Monster, and Region is held here.
*/
class Data
{
private:
    //stuff for creating array to hold every possible weapon
    const int sizeWeapons = 30; //max number of weapons the weapons array can hold
    Weapon weapons[30]; //an array of every possible weapon in the game. Read from weapon_info.txt
    int numWeapons; //how many weapons are actually in the array
    
    
    //stuff for creating a list of Monster objects that can exist in the game
    const int sizeMonsters = 30;
    Monster monsters[30];
    int numMonsters; //the number of monsters added from the file
    
    
    //stuff for creating every possible Region object that exist in the game
    const int sizeRegions = 20; //capacity of regions array
    Region regions[20]; //an array of regions created by reading regions.txt
    int numRegions; //the number of regions added from the file
    
    
    //stuff for weapons each monster can randomly hold
    const int sizeRandWeapons = 5; //the max number of weapons a monster can choose from at random
    string monsterWeapons[30][5]; //2d array of names of weapons each monster can hold. Size = numMonsters
    
    
public:
    Data();//default constructor, set numMonsters and numRegions to 0 for now. Later, read everything.
    
    //return the number of elements in the new array
    int split(string str, char delim, string arr[], int capacity);
    
    /**
     * read the weapon_info.txt file and fill weapons array
     * 
     * weapon_info.txt format:
     *    name
     *    damage
     *    buyPrice sellPrice
     */
    void readWeapons();
    
    
    /**
     * Return a Weapon from the weapons array
     * If there is no Weapon in the array with a matching name, return a fist.
     */
    Weapon getWeaponByName(string name) const;
    
    
    /**
     * monster_info.txt format
     *    name
     *    maxHp (int)
     *    gold (int) //the amount of gold this monster normally carries
     *    strength attack agility defense
     *    Weapon1 name~Weapon2 name~Weapon3 name~Weapon4 name~Weapon5 name
     *    (can have less than 5 weapons, but 5 is the max)
     * 
     * read the monster_info.txt file
     * fill the monsters arrays
     * also fill the monsterWeapons 2d array
     */
    void readMonsters();
    
    /**
     * Find a Monster by its name and return its index in the monsters array.
     * IF THE MONSTER IS NOT IN THE MONSTERS ARRAY, RETURN -1.
     * This will be used in getRandomWeapon to return the name of a random weapon the monster can hold
     * This will be used in creating Region objects
     * since regions.txt has a list of names of monsters that can spawn in each region.
     */
    int getMonsterIndexByName(string name) const;
    
    
    //return the monster at the given index of the monsters array
    //if the index is invalid, return the default monster (thief)
    Monster getMonsterByIndex(int monsterIndex) const;
    
    
    //return a random weapon which the monster stored at the given index of monsters can hold
    //if monsterIndex is invalid or every weapon for that monster index is an empty string, return a fist (default weapon)
    Weapon getRandomWeapon(int monsterIndex) const;
    
    
    /**
     * Read from regions.txt and store data in regions array.
     * Format of regions.txt:
     *     Region name
     *     Monster names (up to 5)
     *     Adjacent Region names (up to 5)
     *     Distances for adjacent regions (number of elements should match the line above)
     *     bool hasShop (1 for true, 0 for false)
     *     Quantities for the 5 items in the shop (blank if hasShop is false)
     *     Names of weapons the shop has (blank if hasShop is false)
     * 
     * Monsters are added using Region::addMonster function, so numMonsters should stay up to date.
     * Number of adjacent regions is passed into the Region constructor 
     * along with the distances array and adjacent regions array.
     * If the region has a shop, use the Shopt(quantities, size) constructor,
     * then add in weapons using Shop::addWeapon function.
     */
    void readRegions();
    
    /**
     * This function will be called in Story's travel method when you arrive at a new region.
     * That way, you can update your location when you reach a new region.
     * @return the Region with the given name.
     * @return default region with some added details if the region does not exist.
     */
    Region getRegionByName(string name) const;
    
    
    int getSizeWeapons() const; //return sizeWeapons
    
    int getSizeRegions() const; //return sizeRegions
    
    int getSizeMonsters() const; //return sizeMonsters
    
    int getSizeRandWeapons() const; //return sizeRandWeapons
    
};

#endif