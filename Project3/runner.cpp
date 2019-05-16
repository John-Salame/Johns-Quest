// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <iostream>
#include <time.h>
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Story.h"
using namespace std;

/*
Classes:
1. Player
2. Monster
3. Weapon
4. BattleManager
5. Item?
6. Region? //an area of the world. It could be large like "Death Valley" or small like "Varrock Palace" and "Varrock Market"
           //just like Oregan Trail, it can take a few turns to reach a place.
           //Random encounters, battles, and random events may happen along the way.
7. Data? //contains data on weapons, monsters, and regions. Extracts them from files into arrays.
8. Story? //progress in the story. You are a messenger spreading word about an impending attack on your kingdom.
          //you have 3 days until the enemy kingdom's troops arrive. Gather elite forces to help you.
9. Shop? //a place to buy weapons or potions or other items

Files:
"weapon_info.txt" //info on attack and name of weapons
"regions.txt" //info on adjoining regions and which monsters can spawn and what treasure can be found
"monster_info.txt" //info on monster stats and which weapons they can spawn with
"save_data.txt" //info on progress in the story. Contains data about player and current location.
                //this is the file I will write to.
                
Main menu:
1. Check inventory --> Use item / quit (usually for healing or interacting with the environment)
2. Switch weapons --> choose a weapon from your backpack
3. Check my stats
4. Travel --> nearby options for your region, such as other places in town or nearby landmarks
5. (if in populated area): Talk to someone.
6. (if in a shop): Trade --> 1. Buy, 2. Sell, 3 Back --> 1. Weapon, 2. Item, 3. Back (shop menu goes 2 layers deep)
7. Sleep --> enter the number of hours
*/

int main()
{
    srand(time(NULL)); //set a random seed
    Story story;
    story.playTheGame();
    /*
    for(int i = 0; i < 10; i++)
    {
        cout << "Misfortune " << i << ":" << endl;
        story.createMisfortune();
        cout << endl << endl << endl;
    }
    */
}