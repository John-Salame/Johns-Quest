// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include "Region.h"
#include <string>
#include <iostream>
using namespace std;

//default constructor
Region::Region()
{
    name = "Gates of Entrana";
    numMonsters = 0; //number of monsters in possibleMonsters array
    numAdjRegions = 0; //number of region names in adjacentRegions array
    hasShop = false;
}


Region::Region(string newName, string nearby[], int dist[], int numReg, bool hasStore, Shop store)
{
    name = newName;
    //add stuff related to adjacent regions
    for(int i = 0; i < numReg; i++)
    {
        //prevent overfilling of the arrays
        if(i < sizeRegions)
        {
            adjacentRegions[i] = nearby[i];
            distances[i] = dist[i];
        }
    }
    numAdjRegions = numReg;
    numMonsters = 0;
    hasShop = hasStore;
    shop = store;
}


/** 
 * add a monster to possibleMonsters and increment numMonsters
 * if there is no room to add more monsters, print "<regionName> already has max monsters."
 */
void Region::addMonster(Monster mon)
{
    //if there is room to add more monsters, do it.
    if(numMonsters < sizeMonsters)
    {
        possibleMonsters[numMonsters] = mon;
        numMonsters++;
    }
    else
    {
        cout << name << " already has max monsters." << endl;
    }
}


/**
 * This function will be used in travel to find the number of hours which must pass
 * to travel to the nearby region with index i.
 * @return the distance to the region at index i of distances[]
 * @return -1 if index is not between 0 and numAdjRegions.
 */
int Region::getDistance(int index)
{
    //valid index
    if(index >= 0 && index < numAdjRegions)
    {
        return distances[index];
    }
    else
    {
        cout << "That is not a valid index of the distances / adjacent regions arrays." << endl;
        return -1;
    }
}


//return a random monster that can spawn in this region.
//If there are no monsters in the possibleMonsters vector, return the default thief.
Monster Region::getRandomMonster()
{
    //if there are no monsters in possibleMonsters, return a default thief.
    if(numMonsters == 0)
    {
        //cout << "There are no possible monsters in the region" << name << "." << endl;
        Monster thief;
        return thief;
    }
    else //possibleMonsters has things inside it
    {
        int randIndex = rand() % numMonsters;
        return possibleMonsters[randIndex];
    }
}


//get the name of the region at index i of adjacentRegions
string Region::getRegionNameAt(int index)
{
    //if the index is invalid, return "Gates of Entrana" since it is the name of the default Region.
    if(index < 0 || index >= numAdjRegions)
    {
        cout << "The index " << index << " does not exist in adjacent regions for " << name << "." << endl;
        return "Gates of Entrana";
    }
    //if the function makes it this far, the index is valid. Return the name of the adjacent Region.
    return adjacentRegions[index];
}

void Region::displayAdjacentRegions()
{
    cout << "0: Stay put." << endl;
    for(int i = 0; i < numAdjRegions; i++)
    {
        cout << i+1 << ": " << adjacentRegions[i];
        cout << " (" << distances[i] << " hours away)." << endl;
    }
}

//GETTERS
string Region::getName() const
{
    return name;
}
int Region::getSizeMonsters() const
{
    return sizeMonsters;
}
int Region::getSizeRegions() const
{
    return sizeRegions;
}
int Region::getNumAdjRegions() const
{
    return numAdjRegions; //return the number of adjacent regions
}
bool Region::getHasShop() const
{
    return hasShop;
}
Shop Region::getShop() const
{
    return shop;
}