// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Monster.h"
using namespace std;


/**
 * This class has all the information on attacks. 
 * For each attack function, there is a version with the Monster attacking
 * and a version with the Player attacking.
 */
class BattleManager
{
private:
    static const int maxMonsters = 4; //maximum number of monsters that can battle you
    vector<Monster> enemies; //a vector of Monster enemies in a battle
    vector<int> livePlayerInd;
    //livePlayerInd is a vector which tracks the index of every living player in heroes vector.
    //Useful for making only live players loot enemies or be targeted by enemy attacks.
    
    
    /**
     * int dealDamage (Player attacking)
     * private helper function (Not a selectable attack option)
     * @param player, the person attacking the monster
     * @param mon, the Monster which the player is attacking
     * @param weaponDamage: how much damage the attack deals without multipliers.
     * @param multiplier: double which dictates how the weapon base damage is multiplied by.
     *        Multiplier allows for more intricate combat interactions, like
     *        extra aggressive plays or extra defensive plays.
     * @return the amount of damage the player dealt to the monster
     * @output "Player dealt <damageDealt> damage to <monster name>"
     */
    int playerDealDamage(Player& player, Monster& monster, int weaponDamage, double multiplier);
    
    
    /**
     * int dealDamage (Monster attacking)
     * private helper function (Not a selectable attack option)
     * Works the same as the player version, but with the roles switched.
     */
    int monsterDealDamage(Player& player, Monster& monster, int weaponDamage, double multiplier);
    
    
    /**
     * Private helper function which clears the vector and adds live players to it.
     * This allows dead players to be removed and revived players to be added.
     */
    void updateLivePlayerInd(vector<Player>& heroes);
    
public:
    /**
     * Default constructor
     * does nothing right now
     */
    BattleManager();
    
    
    //Add a Monster to the enemies array.
    void addMonster(Monster mon);
    
    //return maxMonsters (currently 4). This is the max size of enemies array.
    int getMaxMonsters() const;
    
    /**
     * Handles the menu and progress of the current battle.
     * Return true if the heroes won.
     */
    bool battleToTheDeath(vector<Player>& heroes);
    
    //return true if every enemy (monster) is dead, false otherwise.
    bool allEnemiesDead() const;
    
    //return true if all players are dead, false otherwise
    bool allPlayersDead(const vector<Player> heroes) const;
    
    
    /**
     * At the end of the battle, attempt to take loot from the enemies.
     * Each (living) person in your party has a chance to find loot from an enemy.
     * If they succeed, do rand() % 2 to see if they find a weapon or gold
     * (0 for gold, 1 for weapon).
     * If the Player already has the maximum number of weapons, ask the user
     * if they want to replace a weapon with the new one (not implemented). 
     * If the player says no, loot coins instead.
     * When looting gold, chances are you won't find every coin the monster is carrying.
     * Take a random number between 1 and the number of gold the monster has.
     * If a player searches a monster and doesn't take any weapons or coins,
     * no player after that will search that monster.
     */
    void loot(vector<Player>& heroes);
    
    bool lootGold(Player& looter, Monster& monster); //return true if it successful
    
    bool lootWeapon(Player& looter, Monster& monster); //return true if it successful
    
    
    /**
     * void battleMenu
     * This function is used inside battleToTheDeath()
     * Handles everything a player can do in combat.
     * 0. Flee? (I don't know if I'll put this in the game)
     * 1. View Battlefield (does not end turn)
     * 2. Switch Weapons (does not end turn)
     * 3. Use Item --> choose item --> choose target (ends turn)
     * 4. Attack or Defend (choose a player, attack style, and a target, then end turn)
     * 5. Spy on Player (shows stats and weapon info of the chosen Player)
     * 6. Spy on Monster (shows stats and weapon info of the chosen Monster)
     * 7. Pass (skip your turn)
     * 8. More info
     */
    void battleMenu(vector<Player>& heroes);
    
    //option 2 in battleMenu; prompt user to choose a player and a weapon to switch to
    void switchWeapons(vector<Player>& heroes);
    
    /**
     * Option 3 in battleMenu
     * Display each player's inventory, then prompt the user to choose an item from a player and a target.
     * This can also be called from the Story class outside of battle. To check if this is
     * being used in battle, check if enemies.size() > 0
     * @param index: the index of the item in the player's items array
     * @return true if the player used an item, false otherwise. This ensures no player's turn is skipped.
     */
    bool useItem(vector<Player>& heroes); //prompt the player for a target or go back. return true if it worked.
    
    
    /**
     * Option 4 of battleMenu
     * choose a player to attack with and a target to attack.
     * Return true if a player attacked a monster.
     * Return false if no attack was completed.
     */
    bool attack(vector<Player>& heroes);
    
    /**
     * Option 5 in battleMenu
     * Display each player's health, then prompt the user to choose a player to to show stats for.
     */
    void showPlayerInfo(vector<Player>& heroes) const;
    
    /**
     * Option 6 in battleMenu
     * Show enemy stats and weapon info
     */
    void spyOnEnemy() const;
    
    //show each enemy's hp or print "dead"
    void showAllEnemyHitpoints() const;
    
    //display the hitpoints of every player in the array
    void showAllPlayerHitpoints(const vector<Player> heroes) const;
    
    /**
     * Use a regular attack. (Player attacking)
     * Set the attacker's vulnerability to 1.
     * Calls dealDamage with a multiplier of sqrt(attack^2 + agility)
     * Increase attack and agility exp based on the damage dealt
     * 
     * @param attacker, the person attacking the monster
     * @param target, the Monster which the player is attacking
     * @param weaponDamage: base damage of the attacker's weapon
     */
    void playerNormalAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage);
    
    /**
     * Use a regular attack. (Monster attacking)
     * Works the same as the player version, but with the roles switched.
     * Does not give monsters any experience.
     */
    void monsterNormalAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage);
    
    
    /**
     * Use a strong attack. (Player attacking)
     * Set the attacker's vulnerability to 2 + 1/agility.
     * This is the only close-range attack that can miss when the opponent is not on guard.
     * Chances of missing the attack are 1/agility. Higher agility = lower chance to miss.
     * If the attack hits, call dealDamage with a multiplier equal to 2 * strength.
     * If the attack hits, increase strength exp based on the amount of damage dealt.
     * THE ATTACKER CANNOT MOVE (attack, block, or use item) ON THE NEXT TURN IF THEY MISS.
     * @param heroes: vector of Player objects, passed in from Story.cpp
     * @param playerIndex: the index of the Player in heroes who is attacking
     * @param monsterIndex: the index of the Monster in enemies who is being attacked
     * @param weaponDamage: base damage of the player's weapon
     */
    void playerStrongAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage);
    
    
    /**
     * Use a strong attack. (Monster attacking)
     * Works the same as the player version, but with the roles switched. Player is attacked by Monster.
     * Does not give monsters any experience.
     */
    void monsterStrongAttack(vector<Player>& heroes, int playerIndex, int monsterIndex, int weaponDamage);
    
    
    /**
     * Instead of attacking, take a defensive stance.
     * Set the player's vulnerability to 1/defense.
     * The probability that the enemy will hit you is 1/sqrt(agility).
     * If the enemy hits you, gain defense exp based on the amount of damage blocked.
     *     Less damage = more defense gain. 0.1/damage?
     * If the enemy misses, gain agility exp based on the amount of damage avoided.
     */
    void playerGuard(vector<Player>& heroes, int playerIndex);
    
    
    /**
     * Instead of attacking, take a defensive stance.
     * Set the player's vulnerability to 1/defense.
     * The chance that the enemy will hit you is 1/sqrt(agility).
     * If the enemy hits you, gain defense exp based on the amount of damage blocked.
     *     Less damage = more defense gain. 0.1/damage?
     * If the enemy misses, gain agility exp based on the amount of damage avoided.
     */
    void monsterGuard(int monsterIndex);
};
#endif