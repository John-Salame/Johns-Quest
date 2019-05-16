// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef REGION_H
#define REGION_H

#include <string>
#include "Monster.h"
#include "Shop.h"
using namespace std;

class Region
{
private:
    string name; //the name of this region
    static const int sizeMonsters = 5; //size of possibleMonsters array
    Monster possibleMonsters[5];
    int numMonsters; //how many unique monsters are in possibleMonsters
    
    static const int sizeRegions = 5; //max number of adjacent regions
    string adjacentRegions[5]; //names of regions you can reach from here.
    int numAdjRegions; //how many regions are adjacent to this.
    
    int distances[5]; //how far away [timewise] the corresponding region is
    //size is the same as sizeRegions
    //number of useful elements is the same as numAdjRegions
    
    
    bool hasShop; //true if this region has a shop
    Shop shop; //variable to hold the shop
public:
    Region(); //default constructor
    
    /**
     * Parameterized constructor
     * @param name: the name of the region
     * @param nearby[]: the names of the nearby regions
     * @param dist[]: how far away the nearby regions are
     * @param numReg: how many elements are in nearby[] and dist[]
     * @param hasStore: the value which will be given to hasShop
     * @param store: the shop in this region (will be a default store if there is no shop)
     */
    Region(string newName, string nearby[], int dist[], int numReg, bool hasStore, Shop store);
    
    
    /** 
     * add a monster to possibleMonsters and increment numMonsters
     * if there is no room to add more monsters, print "<regionName> already has max monsters."
     */
    void addMonster(Monster mon);
    
    
    /**
     * This function will be used in travel to find the number of hours which must pass
     * to travel to the nearby region with index i.
     * @return the distance to the region at index i of distances[]
     * @return -1 if index is not between 0 and numAdjRegions.
     */
    int getDistance(int index);
    
    
    //return a random monster that can spawn in this region.
    //If there are no monsters in the possibleMonsters vector, return the default thief.
    Monster getRandomMonster();
    
    
    //get the name of the region at index i of adjacentRegions
    string getRegionNameAt(int index);
    
    void displayAdjacentRegions();
    
    
    string getName() const; //return the name of this region
    int getSizeMonsters() const; //return sizeMonsters (capacity of possibleMonsters)
    int getSizeRegions() const; //return sizeRegions (capacity of arrays)
    int getNumAdjRegions() const; //return the number of adjacent regions.
    bool getHasShop() const; //return hasShop (true if the region has a shop)
    Shop getShop() const; //return the Shop in the region so we can access it
};

#endif