// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include <fstream>
#include "ValidInput.h"
#include "TextFormat.h"
#include "Story.h"
using namespace std;


//default constructor
//this should actually read the save data in the final game
Story::Story()
{
    time = startingHour - 4; //intro segment starts at 8:00 (4 hours before noon)
    introCompleted = false;
    armyRecruited = false;
    finalHour = false; //I don't really need this since false is the default value already
    
    //Player player2;
    //heroes.push_back(player2);
    
    region = data.getRegionByName("Gates of Entrana");
}


/**
 * save() function
 * 
 * save_data.txt format:
 *     region name
 *     time
 *     introCompleted armyRecruited finalHour (3 bools separated by spaces)
 *     
 *     Player Name
 *     hp maxHp
 *     str att ag def
 *     gold
 *     item quantities (5 numbers)
 *     weapon names~
 */
void Story::save()
{
    if(!introCompleted)
    {
        cout << "You can't save during the intro." << endl;
    }
    else
    {
        cout << "Saving . . ." << endl;
        ofstream writer;
        writer.open("save_file.txt");
        writer << region.getName() << endl;
        writer << time << endl;
        writer << introCompleted << " " << armyRecruited << " " << finalHour << endl;
        //now add stuff about players
        for(int i = 0; i < heroes.size(); i++)
        {
            Player player = heroes[i];
            writer << endl;
            writer << player.getName() << endl;
            writer << player.getHp() << " " << player.getMaxHp() << endl;
            writer << player.getStrength() << " " << player.getAttack() << " ";
            writer << player.getAgility() << " " << player.getDefense() << endl;
            writer << player.getGold() << endl;
            //write the item quantities separated by spaces
            Inventory inv; //use this to get sizeItems (which is 5)
            for(int j = 0; j < inv.getSizeItems(); j++)
            {
                //add a space before each quantity except the first.
                if(j > 0)
                {
                    writer << " ";
                }
                writer << player.getItemAt(j).getQuantity();
            }
            writer << endl;
            //now, do the weapons
            for(int k = 0; k < player.getNumWeapons(); k++)
            {
                writer << player.getWeaponAt(k).getName() << "~";
            }
            writer << endl;
        } //end of adding save data for each hero
        
        writer.close();
        cout << "Done saving." << endl;
    } //end of code for after introduction is over
} //end of save()



/**
 * loadSave() function
 * * save_data.txt format:
 *     region name
 *     time
 *     introCompleted armyRecruited finalHour (3 bools separated by spaces)
 *     
 *     Player Name
 *     hp maxHp
 *     str att ag def
 *     gold
 *     item quantities (5 numbers)
 *     weapon names~
 * 
 * 
 * Algorithm:
 * getline --> regon = data.getRegionByName
 * time
 * ifstream >> introCompleted, finalHour
 * getline to remove empty string at the end
 * 
 * while there are more lines to read in the file, read each line.
 * read a player starting a the first empty line.
 * 
 * How to read a player:
 * getline(ifstream, name);
 * ifstream >> hp (do the same for maxHp and isAlive)
 * ifstream >> str (and att, ag, and def)
 * ifstream >> gold
 * getline for weapon names
 * split the weapons string into a string array of length 30.
 * 
 * Player parameterized constructor will set canMove to true.
 * It will also set isAlive to true if hp > 0.
 * 
 * Player player = (name, hp, maxHp, str, att, ag, def, gold);
 * Then, loop through the array of item quantities and use stoi, then player.changeItemQuantity(i, quant);
 * For weapons, do data.getWeaponByName and then player.addWeapon
 */
void Story::loadSave()
{
    ifstream reader;
    reader.open("save_file.txt");
    
    //if save_file.txt does not exist, proceed with the introduction as normal.
    if(reader.fail())
    {
        cout << "The file save_file.txt does not exist. Starting the game at the introduction instead." << endl << endl;
    }
    else if(heroes.size() > 0)
    {
        cout << "You cannot load the game while you are playing it." << endl;
    }
    else //save_file.txt opened
    {
        cout << "Loading . . ." << endl;
        string empty; //use this in getline to get rid of empty strings at the end of lines
        
        string regionName;
        getline(reader, regionName);
        region = data.getRegionByName(regionName); //set the region based on the name
        reader >> time;
        reader >> introCompleted;
        reader >> armyRecruited;
        reader >> finalHour;
        getline(reader, empty); //get rid of the empty line at the end of the line with the bools
        
        //now, do stuff for each player
        //read until the end of the file
        while(getline(reader, empty))
        {
            //if the program finds a non-empty string, it marks the start of the next player's info.
            if(empty != "")
            {
                string playerName = empty;
                int hp;
                reader >> hp;
                int maxHp;
                reader >> maxHp;
                double str; //strength
                reader >> str;
                double att; //attack
                reader >> att;
                double ag; //agility
                reader >> ag;
                double def; //defense
                reader >> def;
                int gold;
                reader >> gold;
                
                //CREATE THE PLAYER
                Player player(playerName, hp, maxHp, str, att, ag, def, gold);
                
                Inventory inv; //for getting the number of items you have to read
                for(int i = 0; i < inv.getSizeItems(); i++)
                {
                    int quant;
                    reader >> quant;
                    player.changeItemQuantity(i, quant); //change quantity from 0 to quant.
                }
                getline(reader, empty); //get rid of the empty string at the end of the quants line
                
                //now, read the weapons into an array of weapon names
                string wepStr;
                int numWeps = 0; //how many are in the array
                string wepNames[data.getSizeWeapons()]; //create an array of size 30
                
                getline(reader, wepStr);
                numWeps = data.split(wepStr, '~', wepNames, data.getSizeWeapons());
                
                //add the weapons to the player
                for(int i = 0; i < numWeps; i++)
                {
                    cout << endl << "Loading weapons for " << player.getName() << " . . ." << endl << endl;
                    Weapon w = data.getWeaponByName(wepNames[i]); //get the weapon by name
                    player.addWeapon(w); //add the weapon to the player's inventory.
                }
                
                heroes.push_back(player); //add the player to the heroes vector, which should start out empty.
            }
        } //end of code for loading players
        
    } //end of code for files that open
    reader.close();
}

//WRITE THIS LATER!
void Story::intro()
{
    TextFormat text; //for wait() and clearScreen();
    introCompleted = false;
    
    
    Player king; //create a player with randomized stats to be the king.
    king.setName("King John");
    
    //heroes starts with one hero: King John
    heroes.push_back(king);
    text.clearScreen(); //get rid of all the text from gaining stats in player constructor
    
    cout << "You are a king traveling through your kingdom after being informed that the past two shipments" << endl;
    cout << "from your greatest port town, Entrana, have not shown up." << endl;
    cout << "Suspicious that something might be amiss, you decide to check out the situation yourself" << endl;
    cout << "and punish any wrongdoing which might be at hand." << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "Enter your name: King ____" << endl;
    string playerName;
    getline(cin, playerName);
    //if the user entered a name for the player, update the name. Else, leave it at King John.
    if(playerName != "")
    {
        heroes[0].setName("King " + playerName);
    }
    cout << "Your name is " << heroes[0].getName() << "." << endl << endl;
    text.wait();
    text.clearScreen();
    
    displayTime();
    cout << "When you arrive at the town, you are stopped at the gate." << endl;
    cout << "You notice a few thugs loitering there." << endl;
    cout << "One of the thugs approaches." << endl;
    cout << "Nervous, you keep walking." << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "\"Oi! Don't you know the rules of this town? If you want to pass by us, you gotta pay up." << endl;
    cout << "If you refuse, we'll beat you so bad you'll wish you were dead.\"" << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "Without you noticing, one of the thugs quietly sneaks behind you and takes your sword." << endl;
    cout << "\"You're unarmed. You better pay up if you want to live! And you won't be getting this back either!" << endl;
    cout << "No weapons in this town unless you're part of the Armani gang!\"" << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "You don't believe it. Your richest port town has been infiltrated and taken over by mere thugs!" << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "Finally, one of the thugs recognizes you." << endl;
    cout << "\"HEY! That's " << heroes[0].getName() << "!" << endl;
    cout << "If we get rid of him, big boss will reward us with all the riches we can dream of!" << endl;
    cout << "We're not letting this one get away, boys!\"" << endl << endl;
    
    //get ready to start the battle
    Monster thief = region.getRandomMonster(); //the only monster at Gates of Entrana is the Theif.
    
    //get the weapons that will be used in the fight
    Weapon knife = data.getWeaponByName("knife");
    Weapon kingSword = data.getWeaponByName("King's Sword");
    
    //add the three thieves to the fight. Give the middle thief the King's Sword.
    thief.setWeapon(knife);
    battle.addMonster(thief);
    thief.setWeapon(kingSword);
    battle.addMonster(thief);
    thief.setWeapon(knife);
    battle.addMonster(thief);
    
    //start the battle. The restulting text depends on whether you won or lost
    if(battle.battleToTheDeath(heroes))
    {
        cout << "You won the battle, but you are too weak to move." << endl;
    }
    else
    {
        cout << "You lost the battle. The greedy thieves are standing over you." << endl;
        BattleManager newBattle; //a BattleManager with no monsters in it
        battle = newBattle; //clear the battlefield so the next battle won't have monsters that killed you.
    }
    cout << "Badly injured, you lie on the ground." << endl;
    cout << "More thieves swarm you. Everything you own is taken from you." << endl;
    
    //Regardless of whether the king wins or loses,
    //get rid of all coins, weapons, and items the king has.
    bool kingStillHasLoot;
    do {
        kingStillHasLoot = loseRandomLoot();
    } while(kingStillHasLoot);
    
    cout << "You've lost everything, and now you believe you will even lose your life." << endl << endl;
    cout << "Suddenly, a traveler appears and drives off the thieves with a fearsome attack." << endl;
    cout << "You black out ..." << endl << endl;
    text.wait();
    text.clearScreen();
    
    incrementTime();
    incrementTime();
    cout << "2 hours pass ..." << endl << endl;
    text.wait();
    text.clearScreen();
    
    //Wake up in the hospital at 10:00 A.M. fully healed
    heroes[0].setIsAlive(true); //this has to be up here because time does not pass if all players are dead.
    heroes[0].setCanMove(true); //this variable doesn't do anything yet, but it will be used in combat if I expand on the game.
    heroes[0].setHp(heroes[0].getMaxHp()); //give the king full health
    region = data.getRegionByName("Entrana Hospital");
    
    displayTime();
    cout << "You wake up in a hospital with the adventurer by your side." << endl;
    cout << "He tells you that he rescued you and brought you to the hospital to recover." << endl;
    cout << "\"3 Potions is all I can spare. Take these if you want to continue traveling through this town.\"" << endl;
    heroes[0].changeItemQuantity(0, 3); //give the king 3 potions.
    text.wait();
    
    /*
    Allow the king to pick options from the main menu twice, with the folliwing restrictions:
    1. He can't rest / sleep.
    2. He can only travel to Entrana Market or Entrana Barracks.
    3. He can still look at stats, use items, shop, or switch weapons as usual.
    4. Shopping won't pass time.
    5. The only way to exit the current action menu is to travel.
    */
    bool stillPlaying;
    stillPlaying = actionMenu();
    //we need this to prevent battle text from showing up if all players are dead
    if(stillPlaying)
    {
        startBattle(); //face a random number of thieves in Entrana Market.
    }
    
    //I don't need if(stillPlaying) here because the menu automatically exits without printing anything
    //if all players are dead
    stillPlaying = actionMenu();
    if(stillPlaying)
    {
        startBattle(); //face a random number of enemies in Entrana Barracks.
        if(battle.allPlayersDead(heroes))
        {
            stillPlaying = false;
        }
    }
    
    //we need this to prevent battle text from showing up if all players are dead
    if(stillPlaying)
    {
        displayTime();
        cout << "You are at " << region.getName() << "." << endl;
        cout << "A mysterious person appears." << endl;
        text.wait(); text.clearScreen();
        
        //introduce the boss of the introduction through text
        cout << "???: \"My, my! I didn't expect you to make it this far after all the trouble I went to in taking you down.\"" << endl << endl;
        text.wait(); text.clearScreen();
        cout << heroes[0].getName() << ": So you're the one responsible for sending all those hooligans!" << endl << endl;
        text.wait(); text.clearScreen();
        cout << "???: \"Yes, yes. My name is Armani. I'm the leader of this gang. If you know what's good for you, leave town.\"" << endl << endl;
        text.wait(); text.clearScreen();
        cout << "Armani: \"Better yet, why don't you be a good boy and bow your head to your executioner? I won't let you disrupt my plans!\"" << endl << endl;
        text.wait(); text.clearScreen();
        cout << "GANG LEADER ARMANI ATTACKS!" << endl;
        
        int bossIndex = data.getMonsterIndexByName("Gang Leader Armani");
        Monster armani = data.getMonsterByIndex(bossIndex);
        battle.addMonster(armani);
        //stillPlaying is true if you win. Loss will be handled inside playTheGame(), where intro() was called from.
        stillPlaying = battle.battleToTheDeath(heroes);
        if(stillPlaying)
        {
            cout << "You have beaten the leader of the Armani gang!" << endl;
            text.wait();
            text.clearScreen();
            cout << "Armani: \"You shouldn't have done that. You don't know who you're dealing with." << endl;
            cout << "Do you know why there are so many of us? Some of us are soldiers of King Rolf in disguise." << endl;
            cout << "That's right, that despicable tyrant wants to take over your country, starting with your richest port town," << endl;
            cout << "but he didn't want you to notice until it was too late. Now that you've gone and ruined his plans," << endl;
            cout << "I'm sure he'll be here promptly. I estimate it will only take his forces " << timeLimit << " hours ";
            cout << "to reach your country." << endl;
            cout << "In " << timeLimit << " hours, King Rolf will have your head!\"" << endl << endl;
            text.wait();
            text.clearScreen();
            
            cout << "With that shocking revelation, Armani throws down a smoke screen and escapes, despite his injuries." << endl << endl;
            text.wait();
            text.clearScreen();
            
            cout << "As you anguish over the thought of your kingdom falling to the hands of King Rolf," << endl;
            cout << "the traveler from earlier enters the barracks." << endl << endl;
            text.wait();
            text.clearScreen();
            
            cout << "\"I saw that wicked gang leader leaving the barracks and I ran him out of town,\" said the traveler." << endl;
            cout << "\"Most of the other gang members took flight too, but I'm sure some are still hanging around." << endl;
            cout << "You ought to be careful.\"" << endl << endl;
            
            cout << "You tell the traveler what the gang leader told you." << endl << endl;
            text.wait();
            text.clearScreen();
            
            cout << "Traveler: \"WHAT? REALLY?\"" << endl;
            cout << "\"You better find some people who are loyal to you and gather forces. I've heard King Rolf's army is terrifyingly strong." << endl;
            cout << "Maybe I'll help you too. I was getting bored and looking for an adventure anyway.\"" << endl << endl;
            text.wait();
            Player traveler; //create a new player to join your party.
            text.clearScreen(); //get rid of all text previous text, including text from player constructor
            traveler.setName("Traveling Adventurer");
            cout << "Traveling Adventurer joined your party!" << endl;
            cout << "What do you want to name him?" << endl;
            cout << "New Name: ______" << endl;
            string newName;
            getline(cin, newName); //allow the user to name their second player
            if(newName != "")
            {
                traveler.setName(newName); //change the traveler's name.
            }
            text.clearScreen();
            
            cout << traveler.getName() << ": \"Hey, the higher-ups here had some pretty nice weapons. I guess they really were members of King Rolf's army." << endl;
            cout << "In fact, this sword on the ground is even better than the one I'm using. I think I'll take it!\"" << endl;
            Weapon sword = data.getWeaponByName("sword");
            traveler.addWeapon(sword);
            traveler.setMaxHp(15); //give the traveler 15 max hp by default
            traveler.setHp(traveler.getMaxHp()); //give the traveler full health.
            traveler.addRandomStats(3); //give the traveler 3 more random stats than a starting player.
            
            heroes.push_back(traveler); //have the hero actually join your party.
            cout << traveler.getName() << ": \"I also found 2 potions on the ground for each of us." << endl;
            for(int i = 0; i < heroes.size(); i++)
            {
                heroes[i].changeItemQuantity(0, 2); //give each player 2 more potions.
            }
            
            text.clearScreen();
            cout << "IMPORTANT ADVICE INCOMING!" << endl;
            cout << heroes[1].getName() << ": ";
            cout << "\"We better head north through the Fields of Nesphos toward Falador. I bet you can recruit an army there." << endl;
            cout << "However, the Fields of Nesphos are very dangerous, with outlaws and mythical beasts roaming everywhere." << endl;
            cout << "Before we go there, we better train some more here.\"" << endl << endl;
            cout << heroes[1].getName() << ": \"I don't know why, but I get the feeling that we'll run into lots of enemies" << endl;
            cout << "if we travel back and forth between the barracks and the market." << endl;
            cout << "We should do that a few times before we move on to the Fields of Nesphos.\"" << endl << endl;
            
            introCompleted = true; //if you beat Armani, you have completed the intro.
            cout << "INTRODUCTION OVER!" << endl;
            text.wait();
            text.clearScreen();
            
            //automatically save once you finish the intro.
            save();
            text.wait();
        }
        else //this happens if you lose to Armani
        {
            cout << "Armani: Ha! That's all you got? You really are a weak king!" << endl;
        }
    }
} //end of intro()


void Story::recruitArmy()
{
    TextFormat text;
    cout << "You head straight toward the fort at the center of Falador and" << endl;
    cout << "alert your best general that King Rolf is coming. Upon hearing the message," << endl;
    cout << "your general tells you that he will raise an army at once and order them to wait ";
    cout << "at Entrana for King Rolf and his army." << endl << endl;
    text.wait();
    text.clearScreen();
    
    cout << "Your general joins you to make sure you can reach the Gates of Entrana alive to confront King Rolf." << endl;
    cout << endl;
    cout << "What do you want to name your newest party member?" << endl;
    cout << "General _____" << endl;
    string newName;
    getline(cin, newName); //let the user type the name
    Player general;
    text.clearScreen();
    if(newName != "")
    {
        newName = "General " + newName;
        general.setName(newName);
    }
    else
    {
        general.setName("General Kyran");
    }
    general.setMaxHp(15); //start with a base of 15 HP
    general.addRandomStats(6); //start the general with 8 more stats than a new player would have.
    general.setHp(general.getMaxHp()); //give the general full health
    Weapon sword = data.getWeaponByName("sword");
    general.addWeapon(sword); //give the general a sword
    heroes.push_back(general); //add the general to your party
    cout << endl << endl << heroes[2].getName() << " joined your party!" << endl << endl;
    cout << heroes[2].getName() << ": \"We should head over to Entrana to meet King Rolf's army before he can tear up the kingdom." << endl;
    cout << "We can fight him at the Gates of Entrana or at Entrana Market." << endl;
    cout << "Let's go!\"" << endl;
    text.wait();
    text.clearScreen();
}

//True if the heroes win, false if they lose.
void Story::finalBattle()
{
    TextFormat text;
    string location = region.getName();
    
    //if you never recruited an army, print this message of defeat.
    if(!armyRecruited)
    {
        cout << "You hear a loud crashing of hooves as a massive army appears." << endl;
        cout << "No matter how many soldiers there are, you are sure that" << endl;
        cout << "they will not fight if their king is defeated." << endl;
        cout << "You walk up toward King Rolf and his " << heroes.size() - 1 << " generals to challenge them to a fight." << endl;
        text.wait();
        cout << "The crooked king rejects your challenge and orders his troops to slaughter you. There is no way you can fight off this many." << endl;
        cout << "As you lie helpless in the midst of a sea of enemies, you wonder why you didn't go to Falador to recruit an army." << endl;
        cout << "YOU LOSE!" << endl;
        text.wait();
        text.clearScreen();
    }
    else //you have recruited an army
    {
        //if you raised an army but you are not anywhere in Entrana, print this defeat message.
        if(location != "Gates of Entrana" && location != "Entrana Market" && location != "Entrana Hospital" && location != "Entrana Barracks")
        {
            cout << "It is the final hour. King Rolf arrived at Entrana but you were not there." << endl;
            cout << "What kind of king are you, sitting behind while your army sacrifices itself for you?" << endl;
            cout << "You have brought dishonor to your name." << endl;
            cout << "YOU LOSE!" << endl;
        }
        else //you have raised an army and you are somewhere in Entrana.
        {
            cout << "You hear a loud crashing of hooves as a massive army appears." << endl;
            cout << "No matter how many soldiers there are, you are sure that" << endl;
            cout << "they will not fight if their king is defeated." << endl;
            cout << "You walk up toward King Rolf and his " << heroes.size() - 1 << " generals to challenge them to a fight." << endl;
            text.wait();
            text.clearScreen();
            if(armyRecruited)
            {
                cout << "With your army to hold off the enemy, you have the opportunity to challenge the king without being ambushed." << endl;
                cout << "The final battle begins ..." << endl << endl;
                text.wait();
                text.clearScreen();
                bool victory; //true if you won
                int kingIndex = data.getMonsterIndexByName("King Rolf");
                Monster king = data.getMonsterByIndex(kingIndex);
                int generalIndex = data.getMonsterIndexByName("Evil General");
                Monster general = data.getMonsterByIndex(generalIndex);
                
                battle.addMonster(king); //add King Rolf
                //add Evil General(s) until the number of enemies matches the number of players
                for(int i = 0; i < heroes.size() - 1; i++)
                {
                    battle.addMonster(general);
                }
                
                //FIGHT!
                victory = battle.battleToTheDeath(heroes);
                
                if(victory)
                {
                    cout << "OUTSTANDING! YOU'VE DEFEATED KING ROLF AND SAVED THE KINGDOM!" << endl;
                }
                else
                {
                    cout << "You lost the battle. Don't be hard on yourself, King Rolf is no joke." << endl;
                    cout << "If you want to give it another go, run the game again and it should pick up from your last save." << endl;
                }
            } //end of code for if you have recruited an army.
        } //end of code for at entrana
    }
} //end of finalBattle()

//this is called in the driver class.
void Story::playTheGame()
{
    TextFormat text; //for wait() and clearScreen();
    text.clearScreen();
    
    loadSave(); //load the data from save_data.txt
    
    //if you have not played the intro on that save file / playthrough, play the intro.
    if(!introCompleted)
    {
        intro();
    }
    
    bool stillPlaying = true; //use this for every part of the game after the intro to check if you won, quit, or died.
    
    while(stillPlaying)
    {
        //explore
        if(stillPlaying)
        {
            cout << "Time to explore!" << endl << endl;
            stillPlaying = actionMenu();
        }
    } //end of while(stillPlaying)
    
    if(battle.allPlayersDead(heroes))
    {
        cout << "Game Over!" << endl;
    }
    
    //at this point, the player has won, lost, or quit.
    cout << "Thanks for playing." << endl;
}



//creates 1-4 random monsters from the region and adds them to battle (the BattleManager member variable of Story)
void Story::startBattle()
{
    TextFormat text; //for wait() and clearScreen()
    
    //pick a random number between 1 and 4.
    int randNumMonsters = 1 + (rand() % battle.getMaxMonsters());
    cout << randNumMonsters << " monsters surround you!" << endl;
    
    for(int i = 0; i < randNumMonsters; i++)
    {
        //get a random monster that can spawn in this region.
        Monster mon = region.getRandomMonster();
        //mon.printDetails(); //for debugging
        
        //get the index of the monster in the monsters array in Data.
        int monIndex = data.getMonsterIndexByName(mon.getName());
        
        //get a random weapon that the monster can hold.
        Weapon randWeapon = data.getRandomWeapon(monIndex);
        
        //give the monster the weapon you randomly selected.
        mon.setWeapon(randWeapon);
        
        //add the monster to the BattleManager.
        battle.addMonster(mon);
    }
    
    //text.wait();
    //once you are done adding monsters, start the battle.
    battle.battleToTheDeath(heroes);
} //end of startBattle()


/*
RETURN TRUE IF STILL PLAYING, FALSE IF YOU LOST / QUIT THE GAME
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
bool Story::actionMenu()
{
    TextFormat text; //for wait() and clearScreen()
    ValidInput valid; //object with methods to check if input is valid
    bool stillPlaying = true; //true if the player has not won, lost, or quit.
    bool stillChoosing = true; //true if you can still choose actions from the menu
    
    while(stillChoosing && stillPlaying)
    {
        text.clearScreen(); //clear the screen at the start of each iteration of the menu.
        
        //if all players are dead at any point in the loop where you are about to choose,
        //cut the function short and return false to indicate that stillPlaying is false.
        if(battle.allPlayersDead(heroes))
        {
            return false;
        }
        
        
        cout << "You are at " << region.getName() << "." << endl;
        displayTime();
        
        //only display the number of hours until the final battle if you've completed the intro.
        if(introCompleted)
        {
            hoursUntilEnd(); //print how many hours until the final battle
        }
        cout << endl << endl;
        
        //display all the options
        cout << "Choose what you want to do:" << endl;
        cout << "1: Check inventory or use item." << endl;
        cout << "2: Check player stats." << endl;
        cout << "3: Switch weapons." << endl;
        cout << "4: Travel (passes time)." << endl;
        //The text for option 5 depends on whether or not there is a shop in this region
        if(region.getHasShop())
        {
            cout << "5: Shop (passes time by one hour if you buy or sell anything)." << endl;
        }
        else
        {
            cout << "5: Shop (no shops nearby)." << endl;
        }
        cout << "6: Rest (passes time by the number of hours you want to rest)." << endl;
        cout << "7: Save." << endl;
        cout << "8: Quit." << endl;
        
        //if it is the final hour, add an 8th option to move on to the final battle.
        if(finalHour)
        {
            cout << "9: Face thine enemy!" << endl;
        }
        //END OF MENU TEXT
        
        //create variables to handle user input
        string choice;
        bool validChoice = false;
        
        getline(cin, choice); //take user input
        text.clearScreen(); //clear the screen after getting user input
        
        //validChoice is true if the user input was a valid int between 1 and 9.
        validChoice = valid.stringValidInt(choice, 1, 9);
        
        //if the user chooses a valid option from the list, enter the switch case
        if(validChoice)
        {
            switch(stoi(choice))
            {
                case 1:
                    //display inventory / use item
                    battle.useItem(heroes);
                    break;
                case 2:
                    //show player stats
                    battle.showPlayerInfo(heroes);
                    break;
                case 3:
                    //switch weapons
                    battle.switchWeapons(heroes);
                    break;
                case 4:
                    //if all of the players die during travel, set stillPlaying to false.
                    stillPlaying = travel();
                    
                    //if it is still the intro, exit the action menu after traveling once.
                    if(!introCompleted)
                    {
                        return stillPlaying;
                    }
                    break;
                case 5:
                    //SHOP
                    
                    //If there is no shop nearby, don't let the player shop.
                    if(!region.getHasShop())
                    {
                        cout << "There is no shop nearby." << endl;
                        text.wait();
                    }
                    else //the region has a store
                    {
                        //if the funciton makes it this far, then the region has a shop.
                        Shop store = region.getShop(); //get the region's shop and call it "store"
                        
                        //Start shopping. If a player bought or sold something, activate this if statement
                        if(shop(false, store))
                        {
                            //pass time by one hour after shopping if it is not the intro or the final hour.
                            if(!introCompleted || finalHour)
                            {
                                cout << "You take a few minutes to shop at the store, and the shopkeeper restocks immediately after you finish." << endl;
                            }
                            else //you traded during normal hours
                            {
                                cout << "You spend an hour shopping. The shopkeeper restocks the store immediately after you finish." << endl;
                                passTime(0.33, 0.50);
                            }
                        }
                        else //you did not buy or sell anything
                        {
                            cout << "You browse the store but don't buy anything. No time passes." << endl;
                        }
                        
                        cout << "You exit the store." << endl << endl << endl;
                        text.wait();
                    }
                    break;
                case 6:
                    //SLEEP
                    stillPlaying = sleep();
                    break;
                case 7:
                    save();
                    text.wait();
                    break;
                case 8:
                    //Call the quit function. If the player quits, stillPlaying = false.
                    //I wrote it this way so stillPlaying could never be changed from false to true.
                    if(quit())
                    {
                        stillPlaying = false; //set stillPlaying to false if you decide to quit.
                    }
                    break;
                case 9:
                    //move onto the final battle
                    if(finalHour)
                    {
                        time++; //increment the hour.
                        finalHour = false; //prevent the warning message from printing when you display time.
                        displayTime();
                        finalBattle(); //commence the final battle against King Rolf.
                        stillPlaying = false; //stop playing after you win / lose to the final boss.
                    }
                    else //it is not the final hour
                    {
                        cout << "You do not have access to this option this early in the game." << endl;
                        text.wait();
                    }
                    break;
                default:
                    cout << "This should never print because input is limited to values from 1 to 8." << endl;
            } //end of switch
            
        } //end of if(valid) for acting on valid input
        else
        {
            //if the input was invalid, tell the user to choose a number between 1 and 8,
            //then wait before clearing the screen.
            text.wait();
        }
        
        
        //after each iteration of taking user input and triggering appropriate actions,
        //if all players are dead or the user chose to quit, stillChoosing = false.
        stillChoosing = stillPlaying;
        
    } //end of while(stillChoosing && stillPlaying)
    
    return stillPlaying; //this will return true unless the player won, lost, or died.
} //end of actionMenu()


/**
 * WRITE THIS LATER!
 * @return true if at least one player is still alive after traveling.
 * @return false if all the players are dead.
 */
bool Story::travel()
{
    TextFormat text; //for wait() and clearScreen()
    ValidInput valid; //for checking if input is valid
    bool stillPlaying = true; //will become false if all players are dead.
    
    //only allow travel if it is not the final hour.
    if(finalHour)
    {
        cout << "The battle is almost upon us! There is no time to travel!" << endl;
        text.wait();
        text.clearScreen();
        //this will return true at the end of the function because not all players are dead.
    }
    else //it is not the final hour, so let the player travel.
    {
        string choice; //user input for the destination
        bool validChoice; //will be true if the choice is an int between 0 and <number of adjacent regions>
        int newIndex; //index of the destination
        
        //repeatedly ask the user to choose a valid destination (or 0 to stay put)
        do {
            displayTime();
            
            //only say how many hours until the enemy arrives if it is not the intro.
            if(introCompleted)
            {
                hoursUntilEnd(); //display how many hours until the final battle
            }
            cout << endl << "You are at " << region.getName() << "." << endl;
            cout << "Choose a region to travel to: " << endl << endl;
            region.displayAdjacentRegions();
            
            getline(cin, choice); //get user input
            text.clearScreen();
            
            //if the user chooses input between 0 and the number of adjacent regions, it is valid.
            validChoice = valid.stringValidInt(choice, 0, region.getNumAdjRegions());
            
            if(validChoice)
            {
                newIndex = stoi(choice) - 1;
                
                //if the user chose 0, quit.
                if(newIndex == -1)
                {
                    //if it the intro, prevent the player from staying put.
                    //this prevents the user from having a scripted battle or boss battle
                    //in the wrong location.
                    if(!introCompleted)
                    {
                        cout << "You can't dilly-dally! You have to see what's wrong with the town! Get moving!" << endl;
                        text.wait();
                        text.clearScreen();
                        return travel();
                    }
                    cout << "You decide to stay put." << endl;
                    text.wait();
                    return true; //still playing
                }
            }
        } while(!validChoice);
        
        //now, the choice is valid and newIndex is valid.
        string destination = region.getRegionNameAt(newIndex); //get the name of the destination.
        int distance = region.getDistance(newIndex); //how far away the destination is.
        int day = 1 + (time + distance) / 24; //part of ETA
        int hour = (time + distance) % 24; //part of ETA
        
        //if it is still the intro, only let the king travel to Entrana Market and Entrana Barracks.
        if(!introCompleted)
        {
            if(destination != "Entrana Market" && destination != "Entrana Barracks")
            {
                cout << "You should go straight to the barracks. That's probably where the thieves are hiding out." << endl << endl;
                text.wait();
                text.clearScreen();
                return travel(); //force them to choose a different destination or stay put.
            }
        }
        
        //say where the player is traveling and when they will arive.
        cout << "Destination: " << destination << "." << endl;
        cout << "ETA: Day " << day << " hour " << hour << "." << endl;
        text.wait();
        
        //if you can't reach the destination before the final battle begins, prevent travel.
        if(time + distance >= startingHour + timeLimit)
        {
            cout << "You can't travel now, there is only " << (startingHour + timeLimit - time);
            cout << " hours until the final battle, and you need one hour to prepare!" << endl;
            cout << "Stay put or choose another destination." << endl;
            text.wait();
            text.clearScreen();
            return travel(); //have the user start choose a valid destination and return the result of that function call.
        }
        
        //AT THIS POINT, THE USER HAS CHOSEN A VALID DESTINATION THAT HE CAN TRAVEL TO IN TIME.
        for(int i = 0; i < distance; i++)
        {
            displayTime();
            cout << "You are traveling through the " << region.getName() << "." << endl << endl;
            
            //Pass the time. If a damaging misfortune occurs, check if any player is still alive.
            if(passTime(0.33, 0.50))
            {
                //if all players are dead at any point in the journey,
                //cut the function short and return false to indicate that the game is over.
                if(battle.allPlayersDead(heroes))
                {
                    return false; 
                }
            }
        }
        
        //after traveling, set your current region to the destination.
        region = data.getRegionByName(destination); //set your new location to the destination.
        cout << "You have arrived at " << region.getName() << "." << endl;
        
        if(destination == "Falador" && !armyRecruited)
        {
            armyRecruited = true;
            recruitArmy();
        }
        
    } //end of if(!finalHour)
    
    text.wait();
    return true;
}


/**
 * Shop at this region's shop.
 * Since this uses a copy of the Region's shop, the shop will reset once you are done shopping.
 * 
 * 
 * Algorithm:
 * Loop everything below this until the user decides to leave the shop.
 * Have the user choose if they want to buy or sell.
 * Then, have them choose if they want to deal with items or weapons.
 * Also, give them the option to check what each player is already carrying (print all item and weapon inventories).
 * Then, choose which player you want to buy or sell weapons / items.
 * 
 * Once all of these factors have been determined, get the Region's shop (region.getShop())
 * and call one of the 4 functions from Shop.cpp (buyItem, sellItem, buyWeapon, sellWeapon).
 * 
 * @param traded: true if you already bought or sold something in the shop. This is false when called from actionMenu()
 * @return true if a player bought or sold something.
 * @return false if no trade took place.
 */
bool Story::shop(bool traded, Shop store)
{
    TextFormat text;
    ValidInput valid;
    bool alreadyTraded = traded; //did you trade anything at any point while you used the shop?
    bool tradedThisTime = false; //did you trade during this iteration of the shop function?
    
    text.clearScreen();
    
    
    //FOR DEBUGGING, DELETE THIS LATER!
    //cout << "Already traded: " << alreadyTraded << endl;
    
    
    //ASK THE USER IF THEY WANT TO BUY, SELL, OR LEAVE THE SHOP
    
    string bsInput; //user input on whether they want to buy or sell
    bool validBs; //true if the user chose 0, 1, or 2
    bool buying; //true if user chose to buy, false if user chose to sell.
    //0: exit shop
    //1: buy
    //2: sell
    //3: see what's in stock
    
    //repeatedly ask the user if they want to buy, sell, or leave the shop.
    do {
        cout << "What would you like to do?" << endl << endl;
        cout << "0: Exit the shop." << endl;
        cout << "1: Buy." << endl;
        cout << "2: Sell." << endl;
        cout << "3: See what's in stock." << endl;
        
        getline(cin, bsInput);
        text.clearScreen();
        
        validBs = valid.stringValidInt(bsInput, 0, 3);
        
        if(validBs)
        {
            int option = stoi(bsInput);
            
            //if option is 0, quit.
            if(option == 0)
            {
                //quit
                return alreadyTraded; //return false if you didn't buy or sell anything from this shop. Return true otherwise.
            }
            else if(option == 1)
            {
                buying = true;
            }
            else if(option == 2)
            {
                buying = false;
            }
            else //check the wares
            {
                validBs = false; //loop back to the top of choosing to buy, sell, or quit
                //print everything that the store has
                cout << "Take a look at what we have to offer:" << endl << endl;
                text.wait();
                text.clearScreen();
                
                cout << "Here are my items:" << endl << endl;
                text.wait();
                store.printItemOptions();
                text.wait();
                text.clearScreen();
                
                cout << "Here are my weapons:" << endl << endl;
                text.wait();
                store.printWeaponOptions();
                text.wait();
                text.clearScreen();
            }
        }
    } while(!validBs);
    
    
    //At this point, buying is true if the player is buying and false otherwise.
    
    string iwInput; //user input on whether they want to deal with items or weapons
    bool validIw; //true if the user chose 0, 1, or 2
    bool item; //true if the user is dealing with items; false if the user is dealing with weapons.
    //0: Go back to main shop menu
    //1: item
    //2: weapon
    
    //repeatedly ask the user if they want to buy, sell, or go back to the main shop menu
    do {
        if(buying)
        {
            cout << "Would you like to buy items or weapons?" << endl;
        }
        else
        {
            cout << "Would you like to sell items or weapons?" << endl;
        }
        cout << "0: Go back to main shop menu." << endl;
        cout << "1: Items." << endl;
        cout << "2: Weapons." << endl;
        
        getline(cin, iwInput);
        text.clearScreen();
        
        validIw = valid.stringValidInt(iwInput, 0, 2);
        
        if(validIw)
        {
            int choice = stoi(iwInput);
            
            if(choice == 0)
            {
                return shop(alreadyTraded, store); //go back to the main menu to shop more, then return the results
            }
            else if(choice == 1)
            {
                item = true;
            }
            else
            {
                item = false;
            }
        }
    } while(!validIw);
    
    
    //At this point, we know what the user wants to buy or sell. Now, we need to know who wants to do it.
    
    string playerInput;
    bool validPlayer;
    int playerIndex; //index of the player in the heroes vector
    
    //repeatedly ask the user which player they want to shop with
    do
    {
        //display player inventories
        cout << "___________________________________________________" << endl << endl;
        cout << "0: Go back to main shop menu." << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        for(int i = 0; i < heroes.size(); i++)
        {
            cout << "Player " << i+1 << ": " << heroes[i].getName() << endl;
            heroes[i].showInventory();
            cout << heroes[i].getName() << "\'s Weapons: " << endl;
            heroes[i].showWeaponInventory();
            cout << endl << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        }
        
        cout << endl << "Look over the inventories carefully before you choose who to shop with." << endl << endl;
        
        
        //construct a string reminding the user what they intend to do before choosing who to shop with
        string order = ""; //what you are buying / selling
        if(buying)
        {
            order += "buy ";
        }
        else
        {
            order += "sell ";
        }
        if(item)
        {
            order += "an item";
        }
        else
        {
            order += "a weapon";
        }
        
        cout << "Which player will " << order << "?" << endl;
        getline(cin, playerInput);
        
        validPlayer = valid.stringValidInt(playerInput, 0, heroes.size());
        
        if(validPlayer)
        {
            playerIndex = stoi(playerInput) - 1;
            
            //quit back to main shop menu if the user entered a 0.
            if(playerIndex == -1)
            {
                return shop(alreadyTraded, store);
            }
            //if the chosen player is unconscous, you can't shop with him.
            else if(!heroes[playerIndex].getIsAlive())
            {
                validPlayer = false;
                cout << "That person is clearly unconscious." << endl;
                cout << "You shouldn't spend people's money without asking them. Choose someone else." << endl << endl;
                text.wait();
                text.clearScreen();
            }
        }
    } while(!validPlayer);
    
    
    //At this point, a valid player index has been chosen. Call one of the four shop functions.
    cout << endl << endl;
    if(buying)
    {
        if(item)
        {
            tradedThisTime = store.buyItem(heroes[playerIndex]);
        }
        else //weapon
        {
            tradedThisTime = store.buyWeapon(heroes[playerIndex]);
        }
    }
    else //selling
    {
        if(item)
        {
            tradedThisTime = store.sellItem(heroes[playerIndex]);
        }
        else //weapon
        {
            tradedThisTime = store.sellWeapon(heroes[playerIndex]);
        }
    }
    
    //after shopping, if you have not traded yet, update whether or not you have traded already.
    if(!alreadyTraded)
    {
        alreadyTraded = tradedThisTime;
    }
    
    
    cout << "What else would you like to do?" << endl << endl;
    text.wait();
    text.clearScreen();
    return shop(alreadyTraded, store); //return to the main shop menu so the user can continue shopping or exit
    
} //end of shop()


//ask the user how long they want to sleep. Pass time each hour.
//each hour, there is a chance that hurt players will heal 1 HP and fainted players will recover.
//return true if at least one player is alive after this function runs.
//if a misfortune occurs and kills all players, return false immediately without finishing the function.
bool Story::sleep()
{
    TextFormat text;
    ValidInput valid;
    
    string input;
    bool validInput; //true if input is a valid number of hours
    int hours; //if input is valid, this will be the input converted to an integer
    
    
    if(!introCompleted) //if it is still the intro, you can't rest.
    {
        cout << "It's too dangerous to rest right now!" << endl;
        text.wait();
        return true; //if you try to sleep during the intro, display this message and quit without doing anything else
    }
    
    //only show the time when it is not the final hour to make the text more visually appealing.
    if(!finalHour)
    {
        displayTime();
    }
    
    //hoursLeft is the number of hours until the final battle.
    //finalHour should trigger in (hoursLeft - 1) hours.
    int hoursLeft = hoursUntilEnd();
    
    //it is already the final hour (or later), you can't sleep; print a message and end the function.
    if(hoursLeft <= 1)
    {
        cout << "You can't sleep now, the battle is almost upon us!" << endl;
        text.wait();
    }
    else //if there is at least 1 hour until the final hour, let the players sleep
    {
        cout << "You need at least one hour to prepare for the battle, so ";
        cout << "you can sleep " << hoursLeft - 1 << " hours at most." << endl << endl;
        
        //ask the user to input the number of hours they want to sleep, until they input a valid number.
        do {
            cout << "Every hour of uninterrupted sleep has a chance of healing players by 1 HP and reviving fainted players." << endl;
            cout << "The deeper your sleep, the more likely your team members are to heal." << endl;
            cout << "How many hours do you want to sleep?" << endl;
            
            getline(cin, input); //get user input
            text.clearScreen();
            
            validInput = valid.stringValidInt(input, 0, hoursLeft - 1);
            
            if(validInput)
            {
                hours = stoi(input);
            }
            
        } while(!validInput);
        
        
        //at this point, a valid number of hours has been chosen
        
        int hoursSlept = 0; //number of consecutive uninterrupted hours of sleep
        
        for(int i = 0; i < hours; i++)
        {
            //for each hour you chose to sleep, do something unless it is the final hour.
            if(!finalHour)
            {
                cout << "Sleeping soundly ..." << endl;
                
                bool interrupted; //will be true if sleep was interrupted by misfortune or final hour
                
                //pass the time and determine if anyone's sleep was interrupted.
                interrupted = passTime(0, 0.2);
                
                if(interrupted)
                {
                    //if all players are dead after a misfortune, exit the function
                    //and return false to indicate that the game is over.
                    if(battle.allPlayersDead(heroes))
                    {
                        return false;
                    }
                    cout << "Out of caution, your party stays awake until the end of the hour." << endl;
                    cout << "The commotion has interrupted your body's natural healing process." << endl;
                    cout << "A few more hours of sleep will help." << endl;
                    text.wait();
                    hoursSlept = 0; //number of consecutive uninterrupted hours of sleep
                }
                
                //if sleep was not interrupted this hour, heal and revive players randomly.
                if(!interrupted)
                {
                    hoursSlept++; //increment hoursSlept for each hour of uninterrupted sleep
                    //cout << "Consecutive hours of uninterrupted sleep: " << hoursSlept << endl; //FOR DEBUGGING
                    
                    //if every player slept uninterrupted, give them a chance to heal by 1 HP or revive.
                    for(int i = 0; i < heroes.size(); i++)
                    {
                        //if the player is alive, have a chance to heal.
                        if(heroes[i].getIsAlive())
                        {
                            //heal chance is 1/2 * hours slept * percentage of health remaining
                            double healChance = 0.5 * hoursSlept * heroes[i].getHp() / heroes[i].getMaxHp();
                            //cout << "Heal chance: " << healChance << endl; //FOR TESTING
                            
                            int d100 = rand() % 100 + 1;
                            if(d100 <= 100 * healChance)
                            {
                                //only heal players if they have less than max hp.
                                if(heroes[i].getHp() < heroes[i].getMaxHp())
                                {
                                    cout << heroes[i].getName() << " recovered a bit during the past hour." << endl;
                                    heroes[i].heal(1);
                                    text.wait();
                                }
                            }
                        }
                        else //unconscious / fainted / dead player
                        {
                            double reviveChance = 0.25 * hoursSlept;
                            //cout << "Revive chance: " << reviveChance << endl;
                            
                            int d100 = rand() % 100 + 1;
                            if(d100 <= 100 * reviveChance)
                            {
                                cout << heroes[i].getName() << " revived by sleeping. He now has 1 HP." << endl;
                                heroes[i].setIsAlive(true); //set the player's status to alive.
                                heroes[i].setHp(1); //set the player's health to 1 HP.
                                text.wait();
                            }
                        }
                    } //end of for loop handling healing / reviving for each player when sleep is uninterrupted
                    
                } //end of if(!interrupted), where events take place
                text.clearScreen();
            } //end of if(!finalHour)
            
        } //end of loop for each hour
        
    } //end of code for if there is at least one hour before the final hour.
    
    //if it makes it to the end of the function, that means at least one player is alive; return true.
    return true;
} //end of sleep function


//ask the user if they want to quit playing. Return true if they say yes.
bool Story::quit()
{
    TextFormat text; //for wait() and clearScreen()
    ValidInput valid; //for testing if input is valid
    
    string choice; //which option from the menu will the user choose?
    bool validChoice; //true if choice is 1, 2, or 3.
    
    string c1 = "save and quit"; //choice 1
    string c2 = "quit without saving"; //choice 2
    string c3 = "keep playing"; //choice 3
    
    //have the user pick a valid choice from the list
    do {
        cout << endl << endl;
        cout << "What do you want to do?" << endl;
        cout << "1: " << c1 << endl;
        cout << "2: " << c2 << endl;
        cout << "3: " << c3 << endl;
        
        getline(cin, choice); //get user input
        text.clearScreen();
        
        //if the choice is 1, 2, or 3, validChoice = true; else, validChoice = false.
        validChoice = valid.stringValidInt(choice, 1, 3);
        
        
        //AFTER THE USER HAS MADE A VALID CHOICE, CONFIRM THEIR CHOICE.
        //If they want to change their course of action, answer no and set validChoice to false.
        if(validChoice)
        {
            string confirm; //will hold a choice of 1 (yes) or 2 (no).
            bool validConfirmation; //true if confirm is 1 or 2.
            
            //ask the user to type input until they choose 1 (yes) or 2 (no).
            do {
                cout << endl << endl;
                
                //print "Are you sure you want to <chosenAction>?"
                cout << "Are you sure you want to ";
                //choose text based on which action they chose.
                switch(stoi(choice))
                {
                    case 1:
                        cout << c1;
                        break;
                    case 2:
                        cout << c2;
                        break;
                    case 3:
                        cout << c3;
                        break;
                    default:
                        cout << "This should never print. Story::quit()" << endl;
                }
                cout << "?" << endl;
                cout << "Option 1: Yes." << endl;
                cout << "Option 2: No." << endl;
                
                getline(cin, confirm); //get user input
                text.clearScreen();
                
                //valid if the user chose 1 or 2.
                validConfirmation = valid.stringValidInt(confirm, 1, 2);
                
                //if the input is valid, see if they chose Yes (1) or No (2).
                if(validConfirmation)
                {
                    //if they chose No, print "Action aborted." and go back to the start of the quit() function.
                    if(stoi(confirm) == 2)
                    {
                        validChoice = false; //have the user choose their action again
                        cout << "Action aborted." << endl << endl;
                    }
                }
            } while(!validConfirmation);
            
        } //end of if(validChoice) for when user chooses 1, 2, or 3
        
    } while(!validChoice); //end of choosing to save and quit, quit without saving, or keep playing.
    
    //At this point, the user has chosen an option and confirmed intent.
    switch(stoi(choice))
    {
        case 1:
            save(); //save and quit
            cout << "Quitting . . ." << endl;
            return true; //true because you are quitting
        case 2:
            cout << "Quitting . . ." << endl;
            return true; //true because you are quitting
        case 3:
            cout << "Returning to game." << endl;
            text.wait();
            return false; //return false because you are not quitting
        default:
            cout << "This should never print. Story::quit()" << endl;
    } //end of code that executes an action
} //end of quit()



//this has a chance to happen during passTime function.
// 50/50 chance for a random player to get weapon or gold (up to 10 gold).
//weapon will be a random weapon carried by a random monster in the region.
void Story::createFortune()
{
    int randPlayer = rand() % heroes.size(); //get the index of a random player
    int lootType = rand() % 2; //0, or 1
    
    cout << "You found something!" << endl;
    
    //Now, give the player loot.
    if(lootType == 0) //weapon
    {
        //give a weapon from the region (that is not named "fist")
        Weapon w;
        bool validWeapon = false;
        while(!validWeapon)
        {
            Monster mon = region.getRandomMonster(); //get a random monster from the region.
            int monIndex = data.getMonsterIndexByName(mon.getName());
            w = data.getRandomWeapon(monIndex); //get a random weapon that monster can carry.
            
            if(w.getName() != "fist")
            {
                validWeapon = true;
            }
        }
        heroes[randPlayer].addWeapon(w); //give the player the weapon
    }
    else if(lootType == 1) //gold
    {
        //give gold
        int randGold = 1 + rand() % 10; //give between 1 and 10 gold
        heroes[randPlayer].gainGold(randGold);
    }
}

/**
 * Roll for misfortune. If misfortune strikes, roll a die for a value 1 through 6.
 *    Rolling a 1 or 2 results in minor damage like tripping over something. player.takeDamage(amount);
 *    Rolling a 3 results in losing an item, weapon, or coins.
 *    Rollin a 4, 5, or 6 results in a battle. Trigger battleToTheDeath().
 * @return true if the misfortune was a damaging one (1, 2, 4, 5, or 6).
 */
bool Story::createMisfortune()
{
    int diceRoll = 1 + rand() % 6;
    
    if(diceRoll == 1 || diceRoll == 2)
    {
        minorDamageMisfortune(); //damage a random living player (if any are alive)
        return true; //return true to indicate that it is possible that all players are dead now.
    }
    else if(diceRoll == 3)
    {
        //have a random player (living or dead) lose something they're carrying.
        bool lostLoot; //this will be true if a player lost something.
        lostLoot = loseRandomLoot();
        
        //if no player was carrying anything, reroll misfortune and return true if it was damaging.
        if(!lostLoot)
        {
            return createMisfortune();
        }
        else
        {
            //if a player lost loot, return false because the misfortune did no damage.
            return false;
        }
    }
    else //rolled a 4, 5, or 6
    {
        startBattle();
        cout << "The battle is over." << endl;
        return true;
    }
}


//happens when createMisfortune rolls a 1 or 2.
//this will damage a living player for at least one damage and up to 4 damage.
void Story::minorDamageMisfortune()
{
    vector<int> livingPlayers; //a vector of indexes of living players
    for(int i = 0; i < heroes.size(); i++)
    {
        if(heroes[i].getIsAlive())
        {
            livingPlayers.push_back(i);
        }
    }
    
    //if no player is alive, exit the function without doing anything.
    if(livingPlayers.size() == 0)
    {
        return;
    }
    
    //pick the index of a random living player to deal damage to.
    int randPlayer = livingPlayers[rand() % livingPlayers.size()];
    int damage = 1 + rand() % 4;
    cout << heroes[randPlayer].getName() << " fell!" << endl;
    heroes[randPlayer].setVulnerability(1); //make sure the player does not take less damage or extra damage.
    heroes[randPlayer].takeDamage(damage); //damage the player.
} //end of minorDamageMisfortune()
    

//helper function for loseRandomLoot() in createMisfortune
//not a member function of Story
bool playerHasItems(Player player)
{
    Inventory inv;
    for(int i = 0; i < inv.getSizeItems(); i++)
    {
        if(player.getItemAt(i).getQuantity() > 0)
        {
            return true;
        }
    }
    return false;
}


/**
 * loseRandomLoot() function
 * happens when createMisfortune rolls a 3.
 * 
 * Algorithm:
 * Make a vector for each of the following:
 *     indexes (in the heroes vector) of players with weapons
 *     indexes (in the heroes vector) of players with items
 *     indexes (in the heroes vector) of players with gold
 * Then, go through each Player in the heroes vector to fill these three vectors.
 * During this loop, if any player has any sort of loot, set a bool "noPlayersHaveLoot" to false.
 * If no players have any loot, return false to indicate that no player lost any loot.
 *     (createMisfortune() will reroll as a result)
 * If the function did not return yet, roll for a random loot type
 *     (0 for weapons, 1 for items, 2 for gold)
 * If any player has the loot type that was rolled, steal it from them. Otherwise, roll again.
 * Return true.
 * 
 * @return true if a player lost some form of loot
 * @return false if no player has any loot to take
 */
bool Story::loseRandomLoot()
{
    vector<int> playersWithWeapons; //vector of indexes of players that have weapons
    vector<int> playersWithItems; //vector of indexes of players that have items
    vector<int> playersWithGold; //vector of indexes of players that have gold
    bool noPlayersHaveLoot = true;
    
    //fill the three vectors
    for(int i = 0; i < heroes.size(); i++)
    {
        Player player = heroes[i];
        
        //if the player has weapons, add him to playersWithWeapons.
        if(player.getNumWeapons() > 0)
        {
            playersWithWeapons.push_back(i);
            noPlayersHaveLoot = false;
        }
        
        if(playerHasItems(player))
        {
            playersWithItems.push_back(i);
            noPlayersHaveLoot = false;
        }
        
        //if the player has at least one coin, the player has loot.
        if(player.getGold() > 0)
        {
            playersWithGold.push_back(i);
            noPlayersHaveLoot = false;
        }
        
    } //end of for loop for filling the three vectors
    
    
    //IF NO PLAYER HAS LOOT, EXIT THE FUNCTION AND RETURN FALSE. misfortune() will reroll after that.
    if(noPlayersHaveLoot)
    {
        return false;
    }
    cout << "Some thieves sneak by and steal something." << endl;
    
    int lootType; //this will hold a value of 0, 1, or 2. It will determine which type of loot is lost.
    bool validLootType = false; //this will be true once a valid loot type is found (one that at least one player has)
    //roll for a loot type until the program finds one that at least one player has
    
    //cout << "Players with Weapons" << playersWithWeapons.size() << endl;
    //cout << "Players with Items" << playersWithItems.size() << endl;
    //cout << "Players with Gold" << playersWithGold.size() << endl;
    while(!validLootType)
    {
        lootType = rand() % 3; //roll a 0, 1, or 2.
        //cout << "Loot Type: " << lootType << endl;
        if(lootType == 0 && playersWithWeapons.size() > 0)
        {
            //if this is the case, a player will lose a weapon.
            
            //get the index (in the heroes vector) of a player that has a weapon.
            int randPlayer = playersWithWeapons[rand() % playersWithWeapons.size()];
            //cout << "Rand Player (weapons): " << randPlayer << endl;
            int randWeapon = rand() % heroes[randPlayer].getNumWeapons(); //index of random weapon
            //cout << "Rand Weapon: " << randWeapon << endl;
            
            //remove the weapon at index randWeapon from the player at index randPlayer
            heroes[randPlayer].removeWeapon(randWeapon);
            validLootType = true;
        }
        else if(lootType == 1 && playersWithItems.size() > 0)
        {
            //if this is the case, a player will lose an item.
            
            //get the index (in the heroes vector) of a player that has an item.
            int randPlayer = playersWithItems[rand() % playersWithItems.size()];
            //cout << "Rand Player (items): " << randPlayer << endl;
            
            //vector which will allow us to choose a random index from the player's inventory
            vector<int> itemIndexes; //a vector of all possible indexes of items to choose
            Inventory inv; //use this to get sizeItems
            //populate itemIndexes
            for(int i = 0; i < inv.getSizeItems(); i++)
            {
                itemIndexes.push_back(i);
            }
            
            /*
            choose a random item index (from the player's inventory) so you can remove one of that item.
            if the quantity of that item is 0, remove that index from itemIndexes and
            try again until you get the index of an item with quantity > 0
            */
            int itemIndex;
            bool validItemIndex = false;
            while(!validItemIndex)
            {
                //get a random index of the itemIndexes vector
                int i = rand() % itemIndexes.size();
                
                //get the number stored at a random index of the vector
                itemIndex = itemIndexes[i];
                //cout << "Item index: " << itemIndex << endl;
                
                if(heroes[randPlayer].getItemAt(itemIndex).getQuantity() > 0)
                {
                    validItemIndex = true; //found an item with quantity > 0
                }
                else //that index of the player's inventory had no items
                {
                    //erase an index of itemIndexes which corresponded to an item with 0 quantity.
                    //if itemIndexes was [0,1,2,3,4] and i was 2, itemIndexes becomes [0,1,3,4].
                    //if itemIndexes was [0,1,3,4] and i was 2 (itemIndex was 3), itemIndexes becomes [0,1,4].
                    itemIndexes.erase(itemIndexes.begin() + i);
                    //cout << "Erased item index " << i << endl;
                }
            }
            //at this point, the index of an item with at least 1 quantity should have been chosen.
            
            //lose an item. Print text saying "<playerName> lost a <itemName>."
            cout << heroes[randPlayer].getName() << " lost a " << heroes[randPlayer].getItemAt(itemIndex).getName() << "." << endl;
            heroes[randPlayer].changeItemQuantity(itemIndex, -1);
            
            validLootType = true;
        }
        else if(lootType == 2 && playersWithGold.size() > 0)
        {
            //in this case, a player will lose some gold
            int randPlayer = playersWithGold[rand() % playersWithGold.size()];
            //cout << "Rand Player (gold): " << randPlayer << endl;
            
            //the player will lose at least 1 gold and up to <the amount of gold he's carrying>
            int randGold = 1 + rand() % (heroes[randPlayer].getGold());
            //cout << "Rand Gold: " << randGold << endl;
            
            //make the random player lose gold.
            heroes[randPlayer].gainGold(-1 * randGold);
            validLootType = true;
        }
    } //end of while(!validLootType)
    //cout << "Done with loseRandomLoot() function." << endl;
    
    //if the function makes it this far, a player lost some loot; return true.
    return true;
} //end of loseRandomLoot() for misfortunes



/**
 * passTime function
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
bool Story::passTime(double fortune, double misfortune)
{
    TextFormat text;
    
    bool returnValue = false;
    double d100 = rand() % 100 + 1;
    
    if(d100 <= fortune * 100)
    {
        createFortune();
        misfortune -= 0.20; //decrease misfortune chances by 20%.
    }
    
    //roll again
    d100 = rand() % 100 + 1;
    if(d100 <= misfortune * 100)
    {
        cout << "Something bad happened!" << endl;
        createMisfortune();
        returnValue = true; //return true because a damaging misfortune occurred
    }
    
    //only increment time and display time if you have not lost the game.
    if(!battle.allPlayersDead(heroes))
    {
        incrementTime();
        
        //at the end, display the time. The if(!finalHour) prevents the warning from printing twice.
        if(!finalHour)
        {
            displayTime();
        }
    }
    text.wait();
    return returnValue;
}


//display time in "Day X, Hour Y" format.
//if it is the final hour, print a warning message telling the player to prepare for the final battle.
void Story::displayTime()
{
    int day = (time / 24) + 1; //starts on day 1
    int hour = time % 24;
    cout << "It is hour " << hour << " of day " << day << "." << endl;
    if(finalHour)
    {
        cout << "This is your final hour to prepare for the final battle. Spend it wisely." << endl;
    }
}


/**
 * The final hour represents the hour before the final battle begins.
 * If the finalHour variable is false but the time indicates that it should be true,
 * print a warning message telling the player to prepare for the final battle, and do not increment time.
 * In any other situation, increment the time by one hour.
 */
void Story::incrementTime()
{
    //if it is not already the final hour but the time indicates that it should be,
    //print a warning message and do not increment the time.
    //this is placed here to safeguard against a non-positive time limit.
    if(!finalHour && time >= (startingHour + timeLimit - 1))
    {
        finalHour = true;
        displayTime();
    }
    else //if it did not just turn into the final hour, increment time by one hour.
    {
        time++; //increment time by one hour.
        
        //also put this after incrementing time for normal situations
        //so you don't have to call this funciton again to update finalHour.
        if(!finalHour && time >= (startingHour + timeLimit - 1))
        {
            finalHour = true;
            displayTime();
        }
    }
} //end of incrementTime()


//print the number of hours until the final battle begins, then return that number.
int Story::hoursUntilEnd()
{
    int hoursLeft = startingHour + timeLimit - time;
    //if it is not the final hour, print how many hours are left.
    if(hoursLeft > 1)
    {
        cout << endl << "Hours until the enemy arrives: " << hoursLeft << endl;
    }
    return hoursLeft;
}