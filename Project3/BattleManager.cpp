// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3


#include <string>
#include <iostream>
#include <cmath>
#include "BattleManager.h"
#include "ValidInput.h"
#include "TextFormat.h"
using namespace std;


//default constructor
BattleManager::BattleManager()
{
    //do nothing
    /*
    Monster defaultMonster;
    
    enemies.push_back(defaultMonster); //fight one thief by default
    enemies.push_back(defaultMonster); //fight one thief by default
    enemies.push_back(defaultMonster); //fight one thief by default
    */
}


//private helper function: Player attacking
int BattleManager::playerDealDamage(Player& player, Monster& monster, int weaponDamage, double multiplier)
{
    //print "<Player name> jabbed <enemy name> with a <weapon name>!"
    cout << player.getName() << " jabbed " << monster.getName() << " with a " << player.getWeapon().getName() << "!" << endl;
    
    double baseDamage = weaponDamage * multiplier; //damage the player wants to deal
    
    int damageDealt; //how much damage the monster actually takes (take vulnerability into account)
    damageDealt = monster.takeDamage(baseDamage); //damageDealt = amount of damage the monster took
    
    return damageDealt; //return the amount of damage the monster took
}

//private helper function: Monster attacking
int BattleManager::monsterDealDamage(Player& player, Monster& monster, int weaponDamage, double multiplier)
{
    //print "<Monster name> jabbed <Player name> with a <weapon name>!"
    cout << "(" << monster.getName() << ") jabbed " << player.getName() << " with a " << monster.getWeapon().getName() << "!" << endl;
    
    double baseDamage = weaponDamage * multiplier; //damage the player wants to deal
    
    //damageDealt = how much damage the monster actually takes (take vulnerability into account)
    int damageDealt = player.takeDamage(baseDamage);
    
    return damageDealt; //return the amount of damage the monster took
}


/**
 * Private helper function which clears the vector and adds live players to it.
 * This allows dead players to be removed and revived players to be added.
 */
void BattleManager::updateLivePlayerInd(vector<Player>& heroes)
{
    livePlayerInd.clear(); //get rid of everything in livePlayerInd
    
    //add the index of every living player to livePlayerInd
    for(int i = 0; i < heroes.size(); i++)
    {
        if(heroes[i].getIsAlive())
        {
            livePlayerInd.push_back(i);
        }
    }
}


void BattleManager::addMonster(Monster mon)
{
    if(enemies.size() < maxMonsters)
    {
        enemies.push_back(mon);
    }
    else
    {
        cout << "There are too many monsters already." << endl;
    }
}


//return maxMonsters (currently 4). This is the max size of enemies array.
int BattleManager::getMaxMonsters() const
{
    return maxMonsters;
}


bool BattleManager::battleToTheDeath(vector<Player>& heroes)
{
    ValidInput valid;
    TextFormat text;
    text.wait(); //FOR DEBUGGING, DELETE THIS LATER!
    
    text.clearScreen();
    cout << "You are under attack!" << endl << endl;
    text.wait(); //press enter to begin battle
    
    
    updateLivePlayerInd(heroes); //track the index of each living player
    bool stillFighting = true; //true if the battle isn't over yet
    bool win = false; //return true if the heroes won the battle
    
    
    while(stillFighting)
    {
        text.clearScreen();
        
        //before the heroes' turn, print out each combatant's health
        cout << "Current state of the battle:" << endl << endl;
        showAllPlayerHitpoints(heroes); //show the hitpoints of each hero/player
        cout << endl;
        showAllEnemyHitpoints(); //show the hitpoints of each enemy
        cout << endl;
        text.wait();
        
        /**before the heroes' turn, check to see if either team has been defeated*/
        //if all players died, lose and stop fighting.
        if(allPlayersDead(heroes))
        {
            cout << endl << endl << "Heroes lose!" << endl << endl << endl;
            stillFighting = false;
            win = false;
        }
        //if all the enemies are dead, win and stop fighting.
        else if(allEnemiesDead())
        {
            stillFighting = false;
            win = true;
            cout << endl << endl << "Heroes win!" << endl;
            cout << endl << "Looting time!" << endl << endl;
            loot(heroes); //after winning, attempt to find loot from enemies
            cout << endl << endl << endl;
        }
        
        
        //if the fight is still going on, have your heroes take their turns
        if(stillFighting)
        {
            //have the heroes take their turns
            battleMenu(heroes); //show the menu at the start of your turn
            updateLivePlayerInd(heroes); //update this in case any player was revived or somehow killed during player turn
            
            /**before the enemies' turn, check to see if either team has been defeated*/
            //if all players died, lose and stop fighting.
            if(allPlayersDead(heroes))
            {
                cout << endl << endl << "Heroes lose!" << endl << endl << endl;
                stillFighting = false;
                win = false;
            }
            //if all the enemies are dead, win and stop fighting.
            else if(allEnemiesDead())
            {
                stillFighting = false;
                win = true;
                cout << endl << endl << "Heroes win!" << endl;
                cout << endl << "Looting time!" << endl << endl;
                loot(heroes); //after winning, attempt to find loot from enemies
                cout << endl << endl << endl;
            }
            
            //if the battle is still going on, have the enemies take their turns
            if(stillFighting)
            {
                //make each living enemy attack.
                for(int i = 0; i < enemies.size(); i++)
                {
                    //if there are living player left to attack, try to attack a random player.
                    if(livePlayerInd.size() > 0)
                    {
                        //if the enemy is alive, attack a random living player
                        if(enemies[i].getIsAlive())
                        {
                            text.clearScreen();
                            cout << endl << endl; //create space above this.
                            
                            //combined with the attack method, this will print "Enemy <index + 1> (name) jabbed <player> with a <weapon>!"
                            cout << "Enemy " << i+1 << " ";
                            int weaponDamage = enemies[i].getWeapon().getDamage(); //get base damage of weapon
                            
                            //get the index of a random living player. That player will be the target of the attack.
                            int playerTargetIndex = livePlayerInd[rand() % livePlayerInd.size()];
                            monsterNormalAttack(heroes, playerTargetIndex, i, weaponDamage); //attack
                            
                            //after attacking, if the target died, update livePlayerInd
                            if(!heroes[playerTargetIndex].getIsAlive())
                            {
                                updateLivePlayerInd(heroes);
                            }
                            text.wait(); //press enter to continue
                        }
                    } //end of condition checking if any players are alive
                }
            } //end of second if(stillFighting)
        } //end of first if(stillFighting)
        
    } //end of while(stillFighting)
    
    return win; //return true if the heroes won, false if the heroes lost
}


//returns true if all enemies are dead
bool BattleManager::allEnemiesDead() const
{
    bool allDead = true; //start as true, change to false if a living enemy is found.
    for(int i = 0; i < enemies.size(); i++)
    {
        //if at least one enemy is alive, return false
        if(enemies[i].getIsAlive())
        {
            allDead = false;
        }
    }
    return allDead;
}


bool BattleManager::allPlayersDead(const vector<Player> heroes) const
{
    bool allDead = true; //start at true, change to false if a living player is found.
    for(int i = 0; i < heroes.size(); i++)
    {
        //if at least one hero is alive, return false
        if(heroes[i].getIsAlive())
        {
            allDead = false;
        }
    }
    return allDead;
}


void BattleManager::loot(vector<Player>& heroes)
{
    //Before attempting to loot, have the user press enter to continue when ready.
    TextFormat text;
    text.wait(); //let the user clear the screen when ready to begin looting
    text.clearScreen();
    
    //make sure the vector tracking living player indexes is up to date
    updateLivePlayerInd(heroes);
    
    ///higher loot chance if enemies outnumber living players
    double lootChance = 0.5 * enemies.size() / livePlayerInd.size();
    
    //give living / conscious hero a chance to loot an enemy
    for(int i = 0; i < livePlayerInd.size(); i++)
    {
        int playerIndex = livePlayerInd[i]; //get the living player's index in the heroes vector
        
        int d100 = (rand() % 100) + 1; //roll a random number from 1 to 100
        
        //if the roll is <= lootChance, player decides to look for loot
        if(d100 <= lootChance * 100)
        {
            //player chooses a random monster to loot
            int monIndex = rand() % enemies.size();
            cout << heroes[playerIndex].getName() << " is searching " << enemies[monIndex].getName() << "." << endl;
            
            //50/50 chance to decide whether the player looks for weapons or gold.
            int lootType = rand() % 2;
            
            
            bool success; //will be true if the player successfully finds loot
            
            //lootType is 0: look for gold
            if(lootType == 0)
            {
                //try to loot coins; success = true if it works
                success = lootGold(heroes[playerIndex], enemies[monIndex]);
                
                //if the monster had no coins, try to loot a weapon; success = true if it works.
                if(!success)
                {
                    success = lootWeapon(heroes[playerIndex], enemies[monIndex]);
                }
            }
            else //lootType is 1: try to loot weapon
            {
                //try to loot a weapon; success = true if it works.
                success = lootWeapon(heroes[playerIndex], enemies[monIndex]);
                
                //if the player could not find a weapon, try to loot coins; success = true if it works.
                if(!success)
                {
                    success = lootGold(heroes[playerIndex], enemies[monIndex]);
                }
            }
            
            //if the player did not find weapons or coins, remove the monster from the vector.
            if(!success)
            {
                enemies.erase(enemies.begin() + monIndex);
            }
            
        } //end of code for player who decides to loot
        else
        {
            cout << heroes[playerIndex].getName() << " does not want to look for loot." << endl;
        }
        
        //After looting with this person, have the user press enter to continue when ready.
        text.wait(); //press enter to continue
        text.clearScreen(); //clear the screen to show only one player's looting text at a time.
        
    } //end of for loop for each player
    
    //after the looting stage is over, remove every monster from the vector to end the battle
    while(enemies.size() > 0)
    {
        enemies.erase(enemies.begin()); //erase the enemy at the first index until there are none
    }
}


//return true if it succeeded
bool BattleManager::lootGold(Player& looter, Monster& monster)
{
    cout << "... looking for gold" << endl;
    if(monster.getGold() > 0)
    {
        cout << "... found some coins!" << endl;
        
        //loot at least one coin, up to <gold> coins from monster
        int amount = (rand() % monster.getGold()) + 1;
        monster.gainGold(-1 * amount); //the monster loses the amount of gold that you took
        looter.gainGold(amount); //gain coins and print "<name> gained X coins.""
        return true;
    }
    else //monster had no gold
    {
        cout << "... found nothing." << endl;
        return false;
    }
}

//return true if it succeeded
bool BattleManager::lootWeapon(Player& looter, Monster& monster)
{
    cout << "... looking for weapons" << endl;
    
    //if the monster's weapon is "fist", there is no weapon to loot, so return false
    if(monster.getWeapon().getName() == "fist")
    {
        cout << "... found nothing." << endl;
        return false;
    }
    else //take the monster's weapon
    {
        Weapon w = monster.getWeapon();
        
        cout << "... found a " << w.getName() << "." << endl;
        looter.addWeapon(w); //take the weapon
        monster.setWeapon("fist", 1); //empty the monster's hands when you take the weapon
        return true;
    }
}


/**
 * void battleMenu
 * This function is used inside battleToTheDeath()
 * Handles everything a player can do in combat.
 * 0. Flee? (I don't know if I'll put this in the game)
 * 1. View battlefield (displays heach player and enemy's health, does not end turn)
 * 2. Switch weapons (does not end turn)
 * 3. Use item --> choose item --> choose target (ends turn)
 * 4. Attack (then in battleToTheDeath(), choose an attack style and a target, then end turn)
 * 5. Display player stats (does not end turn)
 * 6. Display monster stats (then in battleToTheDeath(), choose enemy 1, 2, 3, or 4)
 * 7. Pass. (skip your turn)
 * 8. More info
 */
void BattleManager::battleMenu(vector<Player>& heroes)
{
    ValidInput valid; //handles validation of input in the terminal
    bool endOfTurn = false; //true if every player has taken a turn
    
    //while it is still the player's turn, allow them to make choices
    while(!endOfTurn)
    {
        TextFormat text;
        text.clearScreen();
        cout << "It's your turn." << endl;
        string choice;
        
        //have the player choose an option
        cout << "1. View battlefield" << endl;
        cout << "2. Switch Weapons" << endl;
        cout << "3. Use Item (ends turn)" << endl;
        cout << "4. Attack or Defend (ends turn)" << endl;
        cout << "5. Spy on Player" << endl;
        cout << "6. Spy on Monster" << endl;
        cout << "7. Pass (skip your turn)" << endl;
        cout << "8. More info" << endl;
        
        getline(cin, choice); //take user input
        
        //if user input is valid, proceed to choose the correct function.
        if(valid.stringValidInt(choice, 1, 8))
        {
            //if the user input is a valid int, use stoi and put it in the switch statement
            switch(stoi(choice))
            {
                case 1:
                    //view battlefield (show hitpoints of all players and enemies)
                    text.clearScreen();
                    cout << endl << endl << "Your party:" << endl;
                    showAllPlayerHitpoints(heroes);
                    cout << endl << endl << "Enemies:" << endl;
                    showAllEnemyHitpoints();
                    cout << endl << endl;
                    text.wait(); //press enter to continue
                    break;
                case 2:
                    switchWeapons(heroes);
                    break;
                case 3:
                    //call useItem function. If an item is used successfully, end the turn.
                    endOfTurn = useItem(heroes);
                    break;
                case 4:
                    endOfTurn = attack(heroes); //turn ends if attack succeeded
                    break;
                case 5:
                    //have user choose a player; show that player's stats and weapon info
                    showPlayerInfo(heroes);
                    break;
                case 6:
                    //have the user choose a monster; show that monster's stats and weapon info
                    spyOnEnemy();
                    break;
                case 7:
                    text.clearScreen();
                    cout << "Passed the turn." << endl;
                    endOfTurn = true;
                    text.wait();
                    break;
                case 8:
                    text.clearScreen();
                    cout << "1. View Battlefield: See health and weapon info of each player and monster." << endl << endl;
                    cout << "2. Switch Weapons: Choose a player and have them hold a different weapon from their inventory." << endl << endl;
                    cout << "3. Use Item: Choose a player and choose an item from their inventory, then choose a target." << endl;
                    cout << "      Using an item ends your turn." << endl << endl;
                    cout << "4. Attack: Choose a player to attack with, then choose an attack style, then choose a monster to attack." << endl;
                    cout << "      The chosen player also has the option to block instead of attacking." << endl;
                    cout << "      Attacking or blocking ends the turn." << endl << endl;
                    cout << "5. Spy on Player: Choose a player to view their stats and weapon info." << endl << endl;
                    cout << "6. Spy on Monster: Choose an enemy to view their stats and weapon info." << endl << endl;
                    cout << "7. Pass: Skip your turn. This is the only way for a player to end a turn if he can't move." << endl << endl;
                    text.wait();
                    break;
                default:
                    cout << "This should never print because only choices 1 through 8 are allowed." << endl;
                    text.wait(); //press enter to continue
            } //end of switch
            
        }
        else //input is invalid
        {
            cout << "Please choose a valid number from the menu." << endl;
            text.wait(); //press enter to continue
        }
        
    } //end of while(!endOfTurn)
    
} //end of battleMenu


//option 1 in battleMenu
void BattleManager::switchWeapons(vector<Player>& heroes)
{
    TextFormat text;
    text.clearScreen();
    
    ValidInput valid; //use this object's methods to test validity of input
    string player;
    int playerIndex;
    bool validPlayer;
    
    //have the user choose a player until they choose a valid player or quit
    do{
        //for each player, print option #, player name, and the weapon they are using
        cout << "Choose a player:" << endl;
        cout << "0: No Player (return to battle menu)" << endl;
        for(int i = 0; i < heroes.size(); i++)
        {
            cout << i+1 << ": " << heroes[i].getName() << " (using " << heroes[i].getWeapon().getName() << ")" << endl;
        }
        getline(cin, player); //get user input
        text.clearScreen();
        
        //if the input matches some number in the list of choices, validPlayer is true; else, validPlayer is false.
        validPlayer = valid.stringValidInt(player, 0, heroes.size());
        
        
        //if the input is valid, store the index of the player as choice - 1.
        //if the input was 0, quit.
        if(validPlayer)
        {
            playerIndex = stoi(player) - 1;
            
            //if the user entered 0, quit.
            if(playerIndex == -1)
            {
                cout << "No player chosen. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return;
            }
        }
    } while(!validPlayer);
    
    text.clearScreen();
    
    //now that a player is chosen, show that player's inventory and have the user chose a weapon to switch to
    string weaponInput; //user input
    int weaponIndex; //weaponInput converted to the corresponding index in the weapons array
    bool validWeapon;
    
    //have the user enter input until it is 0 or a valid weapon number
    do {
        //print "<Player name> is using <weapon name>."
        cout << heroes[playerIndex].getName() << " is using " << heroes[playerIndex].getWeapon().getName() << "." << endl;
        
        cout << endl << "Choices:" << endl;
        cout << "0: Don't switch weapons; return to battle menu." << endl;
        //display other weapons the player can switch to
        heroes[playerIndex].showWeaponInventory();
        
        getline(cin, weaponInput); //get user input
        text.clearScreen(); //clear the screen after getting input
        
        //if the input matches some number in the list of choices, validPlayer is true; else, validPlayer is false.
        validWeapon = valid.stringValidInt(weaponInput, 0, heroes[playerIndex].getNumWeapons());
        
        //if the choice was valid, store the index as choice - 1.
        //if the choice was 0, quit.
        if(validWeapon)
        {
            weaponIndex = stoi(weaponInput) - 1;
            
            //if the user entered 0, quit.
            if(weaponIndex == -1)
            {
                text.clearScreen();
                cout << endl << endl << "No weapon chosen. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return;
            }
        }
    } while(!validWeapon);
    
    //now that player and weapon have both been chosen, make the player switch weapons.
    heroes[playerIndex].switchWeapons(weaponIndex);
}


//option 2 in battleMenu
bool BattleManager::useItem(vector<Player>& heroes)
{
    TextFormat text;
    text.clearScreen();
    ValidInput valid; //something to check if input is valid
    
    for(int i = 0; i < heroes.size(); i++)
    {
        heroes[i].showInventory();
    }
    
    string user; //stores input
    int userIndex;
    bool validUser; //true if user input is valid, false if user input is invalid.
    
    //loop while user is invalid. If the input was a 0, return false and exit the loop.
    do {
        
        cout << endl << "CHOOSE WHICH PLAYER WILL USE THE ITEM:" << endl;
        
        cout << "0: Nobody" << endl;
        for(int i = 0; i < heroes.size(); i++)
        {
            cout << i+1 << ": " << heroes[i].getName() << endl;
        }
        getline(cin, user); //take user input
        text.clearScreen();
        
        //if the user input was a valid number from the list, validUser = true; else, validUser = false;
        validUser = valid.stringValidInt(user, 0, heroes.size());
        
        //if the user is valid, handle the cases of 0 input (quit) and dead players
        if(validUser)
        {
            userIndex = stoi(user) - 1;
            
            //if the user entered 0, quit and return to battleMenu.
            if(userIndex == -1)
            {
                cout << "No item used. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return false;
            }
            //if the chosen player is knocked out, print a message saying he can't use any items.
            else if(!heroes[userIndex].getIsAlive())
            {
                text.clearScreen();
                cout << endl << endl;
                cout << heroes[userIndex].getName() << " is unconscious. Please choose a different player." << endl;
                text.wait();
                text.clearScreen();
                validUser = false;
            }
        } //end of if(validUser)
        
    } while(!validUser);
    
    text.clearScreen();
    //now we have userIndex. Now ask for the index of the item.
    
    string item; //stores input
    int itemIndex;
    bool validItem; //true if item input is valid, false if input is invalid
    
    //loop while item input is invalid. If the input was 0, return false and exit the loop.
    do{
        cout << endl << endl;
        heroes[userIndex].showInventory();
        cout << endl << "Choose an item to use (Press 0 if you do not want to use an item)" << endl << endl << endl;
        
        getline(cin, item); //take user input for item number
        text.clearScreen();
        
        
        //if the input is a valid number from the list, validItem = true; else, validItem = false;
        validItem = valid.stringValidInt(item, 0, 5);
        
        //if input was valid, store the index of the item from the list as choice - 1.
        //if the input was 0, quit.
        if(validItem)
        {
            itemIndex = stoi(item) - 1;
            
            //if the choice was 0, quit and return to battleMenu.
            if(itemIndex == -1)
            {
                text.clearScreen();
                cout << "No item used. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return false;
            }
        } //end of if(validItem)
        
    } while(!validItem);
    
    
    text.clearScreen();
    //Now we have a valid item (or we have quit by now).
    
    
    //BASED ON THE ITEM NAME, ASK THE USER TO CHOOSE A TARGET
    Item chosenItem = heroes[userIndex].getItemAt(itemIndex);
    
    bool returnValue = false; //will become true if an item is used correctly
    
    
    //TRY TO USE A POTION
    if(chosenItem.getName() == "Potion" || chosenItem.getName() == "Super Potion")
    {
        cout << heroes[userIndex].getName() << " wants to use a " << chosenItem.getName() << "." << endl;
        
        //if the player has at least one [super] potion, have the player choose a target and then use it
        if(chosenItem.getQuantity() > 0)
        {
            string target;
            int targetIndex;
            bool validTarget = false;
            
            //loop while input is invalid. If the input was 0, return false and exit the loop.
            do {
                cout << endl << endl << endl << "Who do you want to heal?" << endl << endl;
                cout << endl << "0: Nobody (go back to main menu)" << endl;
                showAllPlayerHitpoints(heroes);
                getline(cin, target);
                text.clearScreen();
                
                
                //if input is a valid number from the list, validTarget = true; else, validTarget = false;
                validTarget = valid.stringValidInt(target, 0, heroes.size()); 
                
                
                //if the target is valid, store its index from the heroes vector.
                //if the chosen player is at full health, don't heal him; set validTarget to false.
                //If the input was 0, quit.
                if(validTarget)
                {
                    targetIndex = stoi(target) - 1;
                    
                    //if the choice was 0, quit and return to battleMenu.
                    if(targetIndex == -1)
                    {
                        //quit
                        cout << "No item used. Press enter to return to the menu." << endl;
                        text.wait(); //press enter to continue
                        return false;
                    }
                    //if the player is dead, don't heal them.
                    else if(!heroes[targetIndex].getIsAlive())
                    {
                        validTarget = false;
                        cout << "You cannot heal a fainted player." << endl;
                        cout << "Press enter to choose a different target." << endl;
                        text.wait(); //press enter to continue
                    }
                    //if the target is valid but at full health, they are an invalid target; don't heal them.
                    else if(heroes[targetIndex].getHp() == heroes[targetIndex].getMaxHp())
                    {
                        validTarget = false;
                        cout << heroes[targetIndex].getName() << " is already at full health. ";
                        cout << "Healing them would be a waste." << endl;
                        cout << "Choose a different player to heal." << endl;
                    }
                } //end of if(validTarget)
                
            } while(!validTarget);
            
            //if you have at least 1 potion and a valid target, heal them
            if(chosenItem.getName() == "Potion")
            {
                heroes[targetIndex].heal(10);
            }
            else if(chosenItem.getName() == "Super Potion")
            {
                heroes[targetIndex].heal(15);
            }
            heroes[userIndex].changeItemQuantity(itemIndex, -1);
            returnValue = true; //because this is true, the turn ends after a successful heal
        }
        else //you have 0 potions
        {
            cout << "You do not have any potions to use." << endl;
            returnValue = false;
            //returnValue is already false by default, but I will put this just in case
            //now, the funciton will end and return false, so the turn will not end
        }
    } //end of if(chosenItem.getName() == "Potion" || chosenItem.getName() == "Super Potion")
    else if(chosenItem.getName() == "Revive")
    {
        //if they chose a revive and they have a revive to use, revive a dead player
        if(chosenItem.getQuantity() > 0)
        {
            string target; //number from the list of players (or 0 if you want to quit)
            int targetIndex; //index of the target in the heroes vector
            bool validTarget = false;
            
            //repeatedly ask which player they want to revive until they choose someone valid or quit.
            do {
                //I recycled code from the Potion if statement
                cout << endl << endl << endl << "Who do you want to revive?" << endl << endl;
                cout << endl << "0: Nobody (go back to main menu)" << endl;
                showAllPlayerHitpoints(heroes);
                getline(cin, target);
                text.clearScreen();
                
                
                //if input is a valid number from the list, validTarget = true; else, validTarget = false;
                validTarget = valid.stringValidInt(target, 0, heroes.size()); 
                
                
                //if the target is valid, store its index from the heroes vector.
                //if the chosen player is at full health, don't heal him; set validTarget to false.
                //If the input was 0, quit.
                if(validTarget)
                {
                    targetIndex = stoi(target) - 1;
                    
                    //if the choice was 0, quit and return to battleMenu.
                    if(targetIndex == -1)
                    {
                        //quit
                        cout << "No item used. Press enter to return to the menu." << endl;
                        text.wait(); //press enter to continue
                        return false;
                    }
                    //if the player is alive, don't revive them.
                    else if(heroes[targetIndex].getIsAlive())
                    {
                        validTarget = false;
                        cout << "You cannot revive a player unless they're unconscious." << endl;
                        cout << "Press enter to choose a different target." << endl;
                        text.wait(); //press enter to continue
                    }
                } //end of if(validTarget)
                
            } while(!validTarget);
            
            //at this point, a valid target has been chosen.
            heroes[targetIndex].setIsAlive(true); //make the player alive
            heroes[targetIndex].setHp(0.5*heroes[targetIndex].getMaxHp()); //set player at 50% health
            heroes[userIndex].changeItemQuantity(itemIndex, -1); //use the item from inventory
            returnValue = true; //because this is true, the turn ends after a successful heal
        }
        else //player tried to use a revive when he had none to use
        {
            cout << "You do not have any revives to use." << endl;
            returnValue = false;
            //returnValue is already false by default, but I will put this just in case
            //now, the funciton will end and return false, so the turn will not end
        }
    }
    
    text.wait(); //press enter to continue after finishing using items
    return returnValue;
}


/**
 * Option 4 in battleMenu
 * Have the user choose a player to attack with and an enemy to attack.
 * Return true if the attack was successful, false if the attack was stopped short.
 */
bool BattleManager::attack(vector<Player>& heroes)
{
    TextFormat text;
    ValidInput valid;
    text.clearScreen();
    
    
    //first, have the user choose which player to attack with.
    string playerNum; //user input: which player will attack
    int playerIndex; //the index of the chosen player in the heroes vector
    bool validPlayer; //true if playerNum is a valid number from the list and player is alive; false otherwise.
    
    //loop while input is invalid. If the input was a 0, return false and exit the loop.
    do {
        cout << "Choose which player will attack: " << endl << endl;
        
        cout << "0: Nobody" << endl;
        showAllPlayerHitpoints(heroes); //show the options for the players and their HP
        getline(cin, playerNum);
        text.clearScreen();
        
        
        //if input is a valid number from the list, validPlayer = true; else, validPlayer = false;
        validPlayer = valid.stringValidInt(playerNum, 0, heroes.size());
        
        //if the choice was valid, store the index of the player from heroes.
        //if the chosen player is dead, validPlayer = false; tell the user to choose someone else.
        //If the choice was 0, quit.
        if(validPlayer)
        {
            playerIndex = stoi(playerNum) - 1;
            
            //if the choice was 0, quit and return to battleMenu.
            if(playerIndex == -1)
            {
                cout << "Nobody stepped forward to attack. Press enter to return to the combat menu." << endl;
                text.wait(); //press enter to continue
                return false; //return false because no attack was made.
            }
            //otherwise, if the index is valid but the player is dead, have the user choose someone else.
            else if(!heroes[playerIndex].getIsAlive())
            {
                validPlayer = false;
                cout << "This player is unconscious. Choose someone else." << endl;
                text.wait();
            }
        } //end of if(validPlayer)
        
    } while(!validPlayer); //end of do while loop
    
    
    //now that a player has been chosen, have the user choose a monster to attack.
    
    bool validOption; //true if user input is valid number from monster list; false otherwise.
    string option; //which monster the player wants to attack
    int monsterIndex;
    
    //have the user choose a target until he/she chooses a valid one
    do {
        cout << endl << endl;
        cout << "Player " << playerNum << " (" << heroes[playerIndex].getName() << ") attacking." << endl;
        cout << endl << endl;
        
        cout << "0: Attack nobody. Return to battle menu." << endl;
        showAllEnemyHitpoints();
        cout << endl << "Choose which enemy to attack." << endl;
        getline(cin, option);
        text.clearScreen(); //after choosing a monster to attack, clear the screen to show resulting text.
        
        //if the option is between 1 and enemies.size(), set validOption to true.
        //if the option is not between 1 and enemies.size(), set validOption to false and tell the player it is invalid.
        validOption = valid.stringValidInt(option, 0, enemies.size());
        
        
        //if user input is valid, store the index of the Monster.
        //if the chosen monster is dead, set validOption to false; ask the user to pick a different monster to attack.
        //if user input was 0, quit.
        if(validOption)
        {
            //store the index of the choice from enemies array
            monsterIndex = stoi(option) - 1;
            
            //if the user chose 0, quit.
            if(monsterIndex == -1)
            {
                cout << "No target chosen. Press enter to return to battle menu." << endl;
                text.wait(); //press enter to continue
                return false;
            }
            //if the option is valid but the monster is dead, tell the user. Set validOption to false.
            else if(!enemies[monsterIndex].getIsAlive())
            {
                validOption = false;
                cout << "You can't attack Monster " << option;
                cout << ", that monster is already dead!" << endl;
                text.wait();
                text.clearScreen();
            }
        }
        
    } while(!validOption);
    
    //at this point, a valid monster has been chosen, so attack it.
    int weaponDamage = heroes[playerIndex].getWeapon().getDamage();
    playerNormalAttack(heroes, playerIndex, monsterIndex, weaponDamage); //have player 0 attack the monster for 1 damage
    
    text.wait(); //after the results of your attack are shown, press enter to continue.
    return true; //return true if an attack was made
    //end of player turn
}



/** option 5 in battleMenu */
void BattleManager::showPlayerInfo(vector<Player>& heroes) const
{
    TextFormat text;
    text.clearScreen();
    
    ValidInput valid;
    string playerNum; //input: which number the user chose from the list
    bool validPlayer; //true if playerNum is a valid number from the list of players; false otherwise.
    
    
    //have the user choose which player they want to list stats for.
    //a choice of 0 will go back to the battleMenu.
    //a choice between 1 and heroes.size() (party size) will list that player's stats.
    //any other input will prompt the user to input a valid number.
    do {
        cout << "0: Nobody" << endl;
        showAllPlayerHitpoints(heroes);
        cout << endl << "Choose which player to show stats for: " << endl;
        getline(cin, playerNum); //get user input
        text.clearScreen();
        
        //validPlayer is true if playerNum is between 0 and party size.
        //stringValidInt will print an error message if any other input is given
        validPlayer = valid.stringValidInt(playerNum, 0, heroes.size());
        
        
        if(validPlayer)
        {
            int playerIndex = stoi(playerNum) - 1;
            
            //if the user chose 0, quit.
            if(playerIndex == -1)
            {
                //quit
                cout << "No player chosen. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return;
            }
            else //if the user chose a valid non-zero option, print that player's stats.
            {
                heroes[playerIndex].printDetails();
            }
        } //end of if(validPlayer)
        
    } while(!validPlayer); //end of choosing player to show stats for
    
    text.wait(); //press enter to continue
}



void BattleManager::spyOnEnemy() const
{
    TextFormat text;
    text.clearScreen();
    
    ValidInput valid; //has methods for checking if input is valid
    string enemyNum; //which number the user chose from the list
    bool validMonster; //true if enemyNum is a valid number from the list; false otherwise.
    
    //have the user choose which Monster they want to list stats for.
    //a choice of 0 will go back to the battleMenu.
    //a choice between 1 and enemies.size() will list that enemy's stats.
    //any other input will prompt the user to input a valid number.
    do {
        cout << endl << endl;
        cout << endl << "Choose which enemy to spy on: " << endl;
        cout << "0: Nobody" << endl;
        showAllEnemyHitpoints();
        
        getline(cin, enemyNum);
        text.clearScreen(); //clear screen after choosing an option
        
        //validMonster is true if playerNum is between 0 and enemies.size().
        //stringValidInt will print an error message if any other input is given
        validMonster = valid.stringValidInt(enemyNum, 0, enemies.size());
        
        
        //if the input is valid, store the index of the monster as enemyNum - 1;
        //if the input was 0, quit. Else, print the stats of the chosen monster.
        if(validMonster)
        {
            int monsterIndex = stoi(enemyNum) - 1;
            
            //if the player entered 0, quit.
            if(monsterIndex == -1)
            {
                //quit
                cout << "No enemy chosen. Press enter to return to the battle menu." << endl;
                text.wait(); //press enter to continue
                return; //return to the battleMenu
            }
            else //if the user typed a valid non-zero number, show monster stats
            {
                enemies[monsterIndex].printDetails();
            }
        }
    } while(!validMonster);
    
    text.wait(); //after printing details about the enemy, press enter to continue
    
} //end of spyOnEnemy()


void BattleManager::showAllEnemyHitpoints() const
{
    for(int i = 0; i < enemies.size(); i++)
    {
        //print enemy number and name
        cout << "Enemy " << i+1 << " (" << enemies[i].getName() << ")";
        
        //if the monster is not alive, print that it is dead."
        if(!enemies[i].getIsAlive())
        {
            cout << ": down for the count." << endl;
        }
        else
        {
            //print the hp value of the monster
            cout << ": " << enemies[i].getHp() << " HP." << endl;
        }
    }
}


void BattleManager::showAllPlayerHitpoints(const vector<Player> heroes) const
{
    for(int i = 0; i < heroes.size(); i++)
    {
        //print enemy number and name
        cout << "Player " << i+1 << " (" << heroes[i].getName() << ")";
        
        //if the player is not alive, print that it is dead."
        if(!heroes[i].getIsAlive())
        {
            cout << " is unconscious." << endl;
        }
        else
        {
            //print the hp value of the player
            cout << ": " << heroes[i].getHp() << "/" << heroes[i].getMaxHp() << " HP." << endl;
        }
    }
}


//Player attacking
void BattleManager::playerNormalAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage)
{
    Player player = heroes[playerIndex];
    
    if(player.getIsAlive())
    {
        heroes[playerIndex].setVulnerability(1);
        double skill = player.getAttack() * player.getAttack() + player.getAgility();
        double multi = sqrt(skill); //multiplier is sqrt(attack^2 + agility)
        //cout << multi << endl;
        
        //deal damage to the Monster and record how much damage the Monster took.
        int damageDealt = playerDealDamage(heroes[playerIndex], enemies[monsterIndex], weaponDamage, multi);
        
        //give experience
        double at = player.getAttack();
        double ag = player.getAgility();
        
        //give the player experience for attack and agility
        //I have to use heroes[playerIndex] instead of player to modify the Player in the array.
        heroes[playerIndex].gainAttack(damageDealt / multi / weaponDamage / at);
        heroes[playerIndex].gainAgility(damageDealt / multi / weaponDamage / ag);
    }
    else
    {
        cout << "Silly player, you're too dead to attack!" << endl;
    }
}

//Monster attacking
void BattleManager::monsterNormalAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage)
{
    Monster attacker = enemies[monsterIndex];
    
    if(attacker.getIsAlive())
    {
        //change the monster's vulnerability in the array
        enemies[monsterIndex].setVulnerability(1);
        
        double skill = attacker.getAttack() * attacker.getAttack() + attacker.getAgility();
        double multi = sqrt(skill); //multiplier is sqrt(attack^2 + agility)
        //cout << multi << endl;
        //int damageDealt = dealDamage(attacker, target, weaponDamage, multi);
        
        
        //call the deal damage method
        monsterDealDamage(heroes[playerIndex], enemies[monsterIndex], weaponDamage, multi);
    }
}