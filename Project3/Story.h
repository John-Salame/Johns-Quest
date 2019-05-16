// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#ifndef STORY_H
#define STORY_H

#include <vector>
#include "Player.h"
#include "Region.h"
#include "BattleManager.h"
#include "Data.h"
using namespace std;

class Story
{
private:
    //stuff for your team of players
    const int maxHeroes = 4; //the number of players in the heroes array
    vector<Player> heroes; //an array of controllable players on your team. Max size: 4
    
    Region region; //your current region
    BattleManager battle;
    Data data; //holds data about all the classes. It reads all the files when constructed.
    
    //stuff for time
    int time;
    const int startingHour = 12; //first day starts at noon. This refers to the end of the intro.
    const int timeLimit = 48; //24 hours (1 day) until the final battle
    bool introCompleted; //true if you have already completed the intro in this save file.
    bool armyRecruited; //true if you have been to Falador.
    bool finalHour; //this will be true when there is 1 hour until the final battle begins.
public:
    Story(); //default constructor, reads save data and sets player, region, and time based on that.
    
    void save(); //save the game
    
    void loadSave(); //load the save file at the beginning of the game.
    
    /*
    At the start of playTheGame(), call the intro function if 
    the hour and day are (startingHour - 4) and (0) and location is Gates of Entrana.
    By the end of the intro, the time will be startingHour (12:00 noon) on day 0.
    
    What happens:
    Time: Day 0, Hour 8
    You are a king travelling his kingdom after being informed that the past two shipments
    from your greatest port town, Entrana, have not shown up.
    Suspicious that something might be amiss, you decide to check out the situation yourself
    and punish any wrongdoing which might be at hand.
    --> Enter your name: King ____ (King John by default)
    When you arrive at the town, you are stopped at the gate. You notice a few thugs loitering there.
    "Oi! Don't you know the rules of this town? If you want to pass by us, you gotta pay up.
    If you refuse, we'll beat you so bad you'll wish you were dead."
    Without you noticing, one of the thugs quietly sneaks behind you and takes your sword.
    "You're unarmed. You better pay up if you want to live! And you won't be getting this back either!
    No weapons in this town unless you're part of the Armani gang!"
    You don't believe it. Your richest port town has been infiltrated and taken over by mere thugs!
    
    Finally, one of the thugs recognizes you.
    "HEY! That's King ____! If we get rid of him, big boss will reward us with all the riches we can dream of!
    We're not letting this one get away, boys!"
    THREE THUGS ATTACK YOU, ONE ARMED WITH YOUR SWORD. All you have to fight with are your fists.
       (Whether you win or lose, you collapse from exhaustion after the battle ends.
       A traveling adventurer finds you on the ground, fends of any remaining attackers, 
       and escorts you to the doctor. You wake up fully healed. 
       Pass the time by two hours with fortune .50 and misfortune 0).
    When you wake up, the traveler is still there. He tells you, 
    */
    void intro();
    
    void recruitArmy(); //make armyRecruited true when you enter Falador for the first time.
    
    //commence the final battle against King Rolf.
    //if you have not been to Falador and recruited an army, you automatically lose.
    void finalBattle();
    
    /**
     * Load the latest save by calling loadSave().
     * Call the intro function if the hour and day are (startingHour - 4) and (0) and location is Entrana Gates.
     * After the intro, time starts at 12:00 (noon) on day 0. Save the game.
     * Then, while the player is alive and it is not the final hour, bring up the action menu.
     *     If the player chooses to travel, pass the time by one hour.
     *     If the player chooses to sleep, pass the time by however many hours the user enters.
     *         The fortune rate for the player is 0 while sleeping, and the misfortune rate is 0.2.
     *         Each player heals by 1HP each hour.
     * If it is the final hour, begin the plotline for the final battle.
     */
    void playTheGame();
    
    
    //creates 1-4 random monsters from the region and adds them to battle (the BattleManager member variable of Story)
    void startBattle();
    
    
    /*
    RETURN TRUE IF STILL PLAYING, FALSE IF YOU LOST / QUIT THE GAME
    If all players are at the beginning of the loop for choosing options, return false immediately.
    1. Check inventory or use item --> Use item / quit (usually for healing or interacting with the environment)
    2. Check player stats
    3. Switch weapons --> choose a weapon from your backpack
    4. Travel --> nearby options for your region, such as other places in town or nearby landmarks
    5. (if in a shop): Shop --> 0. Exit, 1. Buy, 2. Sell --> 0. Exit, 1. Weapon, 2. Item (shop menu goes 2 layers deep)
    6. Sleep --> enter the number of hours
    7. Save.
    8. Quit.
    9. Move onto the final battle (only appears in the menu if it is the final hour).
    */
    bool actionMenu();
    
    
    /**
     * bool travel(string destination);
     * Called from the actionMenu() function in Story.
     * 
     * Algorithm:
     * If the function does not return false, do X one hour cycles of gameplay,
     * where X is the distance to the chosen region. At the beginning of each
     * time cycle, display the time and destination and the number of hours until you will reach it.
     * When the loop ends, change the member variable "location" and
     * print "You have reached <destination name>."
     * 
     * @return true if at least one player is still alive after travelling.
     * @return false if all the players are dead.
     */
    bool travel();
    
    /**Shop at this region's shop.
     * Since this uses a copy of the Region's shop, the shop will reset once you are done shopping.
     * If this function returns true, increment the time by one hour (in actionMenu).
     * 
     * @param traded: true if you already bought or sold something in the shop. This is false when called from actionMenu.
     * @param store: a copy of the shop you are shopping at
     * @return true if a player bought or sold something.
     * @return false if no trade took place.
     */
    bool shop(bool traded, Shop store);
    
    
    //ask the user how long they want to sleep. Pass time each hour.
    //each hour, there is a chance that hurt players will heal 1 HP and fainted players will recover.
    //return true if at least one player is alive after this function runs.
    //cut the function short and return false if all the players die due to some misfortune.
    bool sleep();
    
    //ask the user if they want to quit playing. Return true if they say yes.
    bool quit();
    
    
    //this has a chance to happen during passTime function.
    //33% chance for a random player to get weapon, item, or gold.
    //weapon will be a random weapon carried by a random monster in the region.
    void createFortune();
    
    /**
     * Roll for misfortune. If misfortune strikes, roll a die for a value 1 through 6.
     *    Rolling a 1 or 2 results in minor damage like tripping over something. player.takeDamage(amount);
     *    Rolling a 3 results in losing an item, weapon, or coins.
     *    Rollin a 4, 5, or 6 results in a battle. Trigger battleToTheDeath().
     * @return true if the misfortune was a damaging one (1, 2, 4, 5, or 6).
     */
    bool createMisfortune();
    
    void minorDamageMisfortune(); //happens when misfortune rolls a 1 or a 2.
    
    bool loseRandomLoot(); //happens when misfortune rolls a 3.
    
    /**
     * Complete a one hour time cycle.
     * This will be called repeatedly during playTheGame() while it is not the final hour and while the player is not dead.
     * 
     * @param fortune: The chance that you will have something good happen to you. Decimal percent.
     * @param misfortune: The chance that something bad will happen to you. Decimal percent.
     * @return true if a battle or injury misfortune occurred. This will be used to determine if sleep is interrupted.
     * 
     * Algorithm:
     * 1. Display the time. displayTime();
     * 2. Roll for fortune. If you encounter a fortune, decrease the chances of misfortune by 20%.
     * 3. Roll for misfortune. If misfortune strikes, roll a die for a value 1 through 6.
     *    Rolling a 1 or 2 results in minor damage like tripping over something. player.takeDamage(amount);
     *    Rolling a 3 results in losing an item, weapon, or coins.
     *    Rollin a 4, 5, or 6 results in a battle. Trigger battleToTheDeath().
     */
    bool passTime(double fortune, double misfortune);
    
    
    //display time in "Day X, Hour Y" format.
    void displayTime();
    
    
    /**
     * The final hour represents the hour before the final battle begins.
     * If the finalHour variable is false but the time indicates that it should be true,
     * print a warning message telling the player to prepare for the final battle, and do not increment time.
     * In any other situation, increment the time by one hour.
     */
    void incrementTime();
    
    
    //print the number of hours until the final battle begins, then return that number.
    int hoursUntilEnd();
};

#endif