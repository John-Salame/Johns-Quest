// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
using namespace std;


//DEFAULT CONSTRUCTOR
Data::Data()
{
    numWeapons = 0;
    numMonsters = 0;
    numRegions = 0;
    readWeapons();
    readMonsters();
    readRegions();
}


//split a string into an array at the delimiters. Return the number of elements added to the array.
//make this a public member variable so it can be accessed from the Story class for loading saves.
int Data::split(string str, char delim, string arr[], int capacity)
{
    int start = 0; //start of the next word we want to separate
    int end; //index after the end of the next word; usually marks the next delimiter.
    int count = 0; //how many words are already in the array
    
    //loop until there are no more words to add or the array is full.
    while(start < str.length() && count < capacity)
    {
        end = start;
        //increment end until it hits the index str.length() or it hits a delimiter
        while(str[end] != delim && end < str.length())
        {
            end++;
        }
        //after this loop, end marks the end of the whole string or the next delimiter
        
        //add the word to the array
        arr[count] = str.substr(start, end - start);
        start = end + 1; //bring the start of the next word to the index past the delimiter
        count++;
    }
    return count;
}



/**
 * read the weapon_info.txt file and fill weapons array
 * 
 * weapon_info.txt format:
 *    name
 *    damage
 *    buyPrice sellPrice
 */
void Data::readWeapons()
{
    ifstream reader;
    reader.open("weapon_info.txt");
    
    string name;
    int damage;
    int buyPrice;
    int sellPrice;
    string empty = "";
    
    //while there is space in the weapons array and there are more weapons to read,
    //read everything about the weapon
    while(numWeapons < sizeWeapons && getline(reader, empty))
    {
        //look for the beginning of the info for the next weapon
        if(empty != "")
        {
            name = empty;
            reader >> damage;
            reader >> buyPrice;
            reader >> sellPrice;
            
            //now we are done reading this weapon
            Weapon newWeapon(name, damage, buyPrice, sellPrice);
            weapons[numWeapons] = newWeapon;
            //weapons[numWeapons].printDetails(); //for debugging
            numWeapons++;
        }
    }
    
    reader.close();
    //return numWeapons;
}



Weapon Data::getWeaponByName(string name) const
{
    for(int i = 0; i < sizeWeapons; i++)
    {
        if(weapons[i].getName() == name)
        {
            return weapons[i];
        }
    }
    //if no matching weapon was found by this point, the weapon does not exist
    cout << "The weapon " << name << " does not exist in the file. Returning fist instead." << endl;
    Weapon fist;
    return fist; //return the default weapon if no matching weapon is found
}


/**
 * readMonsters() function
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
void Data::readMonsters()
{
    ifstream reader;
    reader.open("monster_info.txt");
    string empty = "";
    
    string name;
    int maxHp;
    int gold;
    int str; //strength
    int att; //attack
    int ag; //agility
    int def; //defense
    string wepStr; //string of all the weapon names
    string wepNames[sizeRandWeapons]; //array which holds the names of each weapon a monster can carry
    int numWepNames; //the number of actual elements in weapon names array
    
    
    //go through each line of the file to add monsters to the array if there is space.
    //ignore blank lines between weapons.
    while(numMonsters < sizeMonsters && getline(reader, empty))
    {
        //look for the beginning of the data for the next Monster.
        if(empty != "") //this marks the start of a new Monster
        {
            name = empty; //set name to the first non-empty string the program encounters
            reader >> maxHp;
            reader >> gold;
            
            reader >> str;
            reader >> att;
            reader >> ag;
            reader >> def;
            
            //get rid of the "" at the end of the defense line so we can read the next line
            getline(reader, empty);
            
            //read the weapon names
            getline(reader, wepStr);
            
            //now, split wepStr and store the number of elements in numWepNames
            numWepNames = split(wepStr, '~', wepNames, sizeRandWeapons);
            //now, wepNames contains up to 5 weapons, and empty strings in all the unfilled slots
            
            
            //add the weapon names to the 2d array
            for(int i = 0; i < numWepNames; i++)
            {
                monsterWeapons[numMonsters][i] = wepNames[i];
            }
            
            //Now, create a Monster using all the information read from the file
            Monster newMon(name, maxHp, str, att, ag, def, getRandomWeapon(numMonsters), gold);
            monsters[numMonsters] = newMon; //add the Monster to the array
            
            numMonsters++; //increase the position in the monsters array after a monster is added
        }
    }
    //at this point, every line in the file has been read.
    
    reader.close();
    //return numMonsters;
}


/**
 * Find a Monster by its name and return its index in the monsters array.
 * IF THE MONSTER IS NOT IN THE MONSTERS ARRAY, RETURN -1.
 * This will be used in getRandomWeapon to return the name of a random weapon the monster can hold
 * This will be used in creating Region objects
 * since regions.txt has a list of names of monsters that can spawn in each region.
 */
int Data::getMonsterIndexByName(string name) const
{
    for(int i = 0; i < sizeMonsters; i++)
    {
        if(monsters[i].getName() == name)
        {
            return i;
        }
    }
    //At this point, if the function has not returned anything, the monster does not exist
    cout << name << " does not exist in the monsters array. Returning -1 as the index." << endl;
    return -1;
}



Monster Data::getMonsterByIndex(int monsterIndex) const
{
    //if the index is valid, return the monster at that index of the monsters array
    if(monsterIndex >= 0 && monsterIndex < sizeMonsters)
    {
        return monsters[monsterIndex];
    }
    else //if the index is invalid, say so, and return a fist
    {
        cout << "The index you are trying to access does not exist in the monsters array." << endl;
        cout << "Returning thief instead." << endl;
        Monster thief; //default Monster
        return thief;
    }
}


//create a vector with every Weapon the monster can use which is not a fist
//if the size of the vector is 0, return the Weapon "fist"
//else, return a random Weapon in the vector
Weapon Data::getRandomWeapon(int monsterIndex) const
{
    //if the index is invalid, say so and return a fist
    if(monsterIndex < 0 || monsterIndex >= sizeMonsters)
    {
        cout << "The index you are trying to access does not exist in the monsters array. Returning fist." << endl;
        Weapon fist; //default Weapon
        return fist;
    }
    else //index is valid
    {
        vector<string> choices; //will hold all non-empty strings from the 2d weapons array for this monster
        for(int i = 0; i < sizeRandWeapons; i++)
        {
            //add every weapon to the vector that was intentionally added to the 2d array
            string wepName = monsterWeapons[monsterIndex][i];
            if(wepName != "")
            {
                choices.push_back(wepName);
            }
        }
        //if the 2d array had no weapons, return fist (the default weapon)
        if(choices.size() == 0)
        {
            Weapon fist; //default Weapon
            return fist;
        }
        else
        {
            int index = rand() % choices.size();
            string newName = choices[index]; //take a random weapon name from the vector
            Weapon newWeapon = getWeaponByName(newName);
            return newWeapon;
        }
    }
}


/**
 * Algorithm:
 * While there are more lines to read in the file, look for the start of the next region's information.
 * The start of the next region is marked by the first non-empty line you come across.
 * Then, read in all the data and store it in the appropriate variables.
 * Then, create a Shop if hasShop is true, or create a default Shop otherwise.
 * Then, construct the region using the second constructor in Region.cpp
 * Then, use Region::addMonster to add the appropriate monsters to the region.
 * Finally, place the newly created Region into the regions array of the Data class.
 */
void Data::readRegions()
{
    ifstream reader;
    reader.open("regions.txt");
    Region reg; //default region. Used to get the values of sizeMonsters and sizeRegions.
    Inventory inv; //default inventory. Used to get sizeItems (the number of Items in the inventory, which is 5)
    string empty; //I use this in getline(reader, empty) to get rid of empty strings at the end of a line after using >>
    
    //variables that will hold region information
    string name;
    string monStr; //string of names of monsters that can spawn
    string monNames[reg.getSizeMonsters()]; //array of names of monsters that can spawn. This comes from splitting monStr.
    int numMon = 0; //how many monster names are in monNames
    string regStr; //string of names of adjacent regions
    string regNames[reg.getSizeRegions()]; //array of names of adjacent regions. This comes from splitting regStr.
    int numReg = 0; //how many region names are in regNames
    int distArr[reg.getSizeRegions()]; //array of distances. This will only work if number of distances matches number of regions.
    //numDist is the same as numReg, so we don't need it.
    bool hasShop; //holds a value of 0 (no shop in region) or 1 (region has a shop)
    Shop shop; //will be used to construct a shop to put into the region
    
    
    //TIME TO READ IN DATA!
    //while there is space in the regions array and there are more lines to read in the file,
    //read them.
    while(numRegions < sizeRegions && getline(reader, empty))
    {
        if(empty != "")
        {
            name = empty; //name is the first non-empty string
            getline(reader, monStr); //get line of monster names
            numMon = split(monStr, '~', monNames, reg.getSizeMonsters());
            //split into array of monster names and record the number of useful elements.
            
            getline(reader, regStr); //get line of region names
            numReg = split(regStr, '~', regNames, reg.getSizeRegions());
            //split into array of region names and record the number of useful elements.
            
            //fill distArr with distances
            for(int i = 0; i < numReg; i++)
            {
                int dist;
                reader >> dist;
                distArr[i] = dist;
            }
            getline(reader, empty); //get rid of the empty string at the end of the distances line
            
            reader >> hasShop; //read hasShop as a bool
            getline(reader, empty); //get rid of the empty string at the end of the current line
            
            //if the area has a shop, change shop from default to custom shop.
            if(hasShop)
            {
                //the following four variables will only be filled if the region has a shop:
                int quantArr[inv.getSizeItems()]; //array of quantities of the items in the store
                string wepStr; //string of weapon names the store has to offer
                string wepNames[sizeWeapons]; //array of weapon names the store has to offer. 30 length is more than enough.
                int numWeps = 0; //number of useful weapons in the array
                
                //fill the array of quantities
                for(int i = 0; i < inv.getSizeItems(); i++)
                {
                    int quant;
                    reader >> quant;
                    quantArr[i] = quant;
                }
                getline(reader, empty); //get rid of the empty string at the end of the quantities line.
                
                getline(reader, wepStr);
                numWeps = split(wepStr, '~', wepNames, sizeWeapons);
                //split the line of weapon names into an array and store the number of useful elements.
                
                Shop customShop(quantArr, inv.getSizeItems());
                //add the weapons
                for(int i = 0; i < sizeWeapons; i++)
                {
                    //if the weapon name is not an empty string, find the weapon with that name and add it to customShop.
                    if(wepNames[i] != "")
                    {
                        Weapon newWeapon = getWeaponByName(wepNames[i]);
                        customShop.addWeapon(newWeapon);
                    }
                }
                shop = customShop; //change the shop from default to custom
            }
            else //if the region does not have a shop, read in empty lines twice.
            {
                getline(reader, empty);
                getline(reader, empty);
            }
            
            //NOW, WE HAVE ALL THE INFORMATION WE NEED TO CREATE A REGION
            Region newRegion(name, regNames, distArr, numReg, hasShop, shop); //construct a region
            //time to add possible monsters to newRegion
            for(int i = 0; i < numMon; i++)
            {
                int monIndex = getMonsterIndexByName(monNames[i]); //get the index of the monster in monsters data
                Monster mon = getMonsterByIndex(monIndex); //get a Monster object from that index of the array
                newRegion.addMonster(mon); //add the Monster object to newRegion.
            }
            regions[numRegions] = newRegion; //add the new Region to the regions member variable of Data.
            numRegions++;
            
            /*
            //DEBUGGING
            cout << endl << endl;
            cout << "Region " << numRegions - 1 << ":" << endl;
            cout << "Name: " << name << endl;
            for(int i = 0; i < numMon; i++)
            {
                cout << monNames[i] << "~";
            }
            cout << endl;
            for(int i = 0; i < numReg; i++)
            {
                cout << regNames[i] << "~";
            }
            cout << endl;
            for(int i = 0; i < numReg; i++)
            {
                cout << distArr[i] << " ";
            }
            cout << endl;
            cout << hasShop;
            if(hasShop)
            {
                newRegion.getShop().printItemOptions();
                newRegion.getShop().printWeaponOptions();
            }
            else
            {
                cout << endl << "~" << endl << "~" << endl;
            }
            //END OF DEBUGGING TEXT
            */
            //cout << newRegion.getRandomMonster().getName() << endl;
        } //end of if(empty != "" for finding the start of the next region's data)
    } //end of while(getline(reader, empty)) for reading until end of file
    
    
    reader.close(); //close the filestream before exiting the function.
} //end of readRegions()


/**
 * This function will be called in Story's travel method when you arrive at a new region.
 * That way, you can update your location when you reach a new region.
 * @return the Region with the given name.
 * @return default region with some added details if the region does not exist.
 */
Region Data::getRegionByName(string name) const
{
    for(int i = 0; i < numRegions; i++)
    {
        if(regions[i].getName() == name)
        {
            return regions[i];
        }
    }
    //at this point, if the function didn't return anything, the Region doesn't exist in the array.
    cout << name << " does not exist in the regions array." << endl;
    Region defaultRegion;
    return defaultRegion;
}


int Data::getSizeWeapons() const
{
    return sizeWeapons;
}
int Data::getSizeRegions() const
{
    return sizeRegions;
}
int Data::getSizeMonsters() const
{
    return sizeMonsters;
}
int Data::getSizeRandWeapons() const
{
    return sizeRandWeapons;
}