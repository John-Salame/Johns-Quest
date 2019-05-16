// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <string>
#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "ValidInput.h"
#include "TextFormat.h"
using namespace std;

//default constructor NOT FINISHED YET
Player::Player()
{
    name = "Brave Hero";
    isAlive = true;
    maxHp = 10;
    gold = 0;
    
    strength = 1;
    attack = 1;
    agility = 1;
    defense = 1;
    
    addRandomStats(6); //start the player with 6 stats randomly added to the base stats
    
    //combat related stuff
    hp = maxHp;
    vulnerability = 1;
    canMove = true; //this player can attack, block, and use items (this actually doesn't do anything right now)
    
    //weapon is fist by default
}


//PARAMETERIZED CONSTRUCTOR FOR PLAYER. USE THIS WHEN LOADING SAVES.
Player::Player(string newName, int newHp, int newMaxHp, double str, double att, double ag, double def, int newGold)
{
    name = newName;
    hp = newHp;
    maxHp = newMaxHp;
    strength = str;
    attack = att;
    agility = ag;
    defense = def;
    gold = newGold;
    vulnerability = 1;
    canMove = true;
    if(hp > 0)
    {
        isAlive = true;
    }
    else
    {
        isAlive = false;
    }
}


void Player::addRandomStats(int num)
{
    //assign the remaining 6 out of 10 stat points randomly (can also affect maxHp).
    for(int i = 0; i < num; i++)
    {
        int attribute = rand() % 5; //value of 0, 1, 2, 3, or 4
        
        //add one point to the randomly chosen attribute
        switch(attribute)
        {
            case 0:
                maxHp++;
                hp++;
                break;
            case 1:
                strength++;
                break;
            case 2:
                attack++;
                break;
            case 3:
                agility++;
                break;
            case 4:
                defense++;
                break;
            default:
                cout << "This should not print out. Check Player default constructor." << endl;
        }
    }
}


//a function to set the value of isAlive
void Player::setIsAlive(bool tf)
{
    //I am not going to include the commented out part because canMove does nothing right now.
    /*
    //if the player was not alive / conscious before the function call, he can't move for the time being.
    if(!isAlive)
    {
        canMove = false;
    }
    */
    
    isAlive = tf; //update the value of isAlive.
    
    //I am not going to include the commented out part because canMove does nothing right now.
    /*
    //if the function call changed the player's status to dead / unconscious, set canMove to false.
    if(!isAlive)
    {
        canMove = false;
    }
    */
} //end of setIsAlive function

//a function to set canMove
void Player::setCanMove(bool tf)
{
    canMove = tf;
}


//directly set the value of the player's hp.
void Player::setHp(int amount)
{
    if(amount >= 0 && amount <= maxHp)
    {
        hp = amount;
    }
}


//set the player's max hp. This is good for when you recruit players later in the game.
void Player::setMaxHp(int amount)
{
    //each player should have at least 10 max HP
    if(amount >= 10)
    {
        maxHp = amount;
    }
    else
    {
        cout << "Players should not have less than 10 max HP." << endl;
    }
}


int Player::takeDamage(double baseDamage)
{
    int damage = baseDamage * vulnerability; //damage taken, rounded down.
    hp = hp - damage; //take the damage by subracting from hp.
    
    //if the player is out of hp, kill the player.
    if(hp <= 0)
    {
        //if it was overkill, change damage to how much health the player had left in the first place.
        damage = damage + hp;
        hp = 0;
        setIsAlive(false); //set isAlive and canMove to false.
    }
    cout << name << " took " << damage << " damage." << endl << endl;
    if(!isAlive)
    {
        cout << name << " fainted." << endl << endl;
    }
    
    return damage;
} //end of takeDamage function


void Player::heal(int amount)
{
    //only allow people to heal by positive amounts (not zero)
    if(amount <= 0)
    {
        return;
    }
    canMove = true; //the burst of energy from healing cures the player of sluggishness.
    
    int oldHp = hp;
    hp += amount;
    
    //cap off hp at max hp if the player healed too much
    if(hp > maxHp)
    {
        hp = maxHp;
    }
    
    //if the player didn't gain any health, don't print any text.
    if(hp - oldHp == 0)
    {
        return;
    }
    
    //print a message saying how much the player healed
    cout << name << " healed for " << hp - oldHp << "." << endl;
    
    //if they player is at full health, 
    if(hp == maxHp)
    {
        cout << name << " is at full health." << endl;
    }
} //end of heal function


void Player::switchWeapons(int weaponIndex)
{
    
    if(weaponIndex >=0 && weaponIndex < weapons.size())
    {
        weapon = weapons[weaponIndex];
    }
    else //if the player tries to switch to an invalid index, switch to fist
    {
        Weapon fist; //create a default weapon (fist)
        weapon = fist; //set player's weapon to "fist"
    }
}


string Player::getName() const
{
    return name;
}
int Player::getHp() const
{
    return hp;
}
int Player::getMaxHp() const
{
    return maxHp;
}
bool Player::getIsAlive() const
{
    return isAlive;
}
double Player::getStrength() const
{
    return strength;
}
double Player::getAttack() const
{
    return attack;
}
double Player::getAgility() const
{
    return agility;
}
double Player::getDefense() const
{
    return defense;
}
bool Player::getCanMove() const
{
    return canMove;
}
//returns the current size of weapons vector
int Player::getNumWeapons() const
{
    return weapons.size();
}
Weapon Player::getWeapon() const
{
    return weapon;
}
int Player::getGold() const
{
    return gold;
}


void Player::showInventory() const
{
    cout << name << "\'s Inventory:" << endl;
    cout << "Gold: " << gold << endl; //how many coins the player has
    cout << "Items:" << endl;
    for(int i = 0; i < items.getSizeItems(); i++)
    {
        //print item number: name xQuantity
        cout << i+1 << ": " << items.getItemAt(i).getName() << " x";
        cout << items.getItemAt(i).getQuantity();
        cout << "   (" << items.getItemAt(i).getDescription() << ")" << endl;
    }
    cout << endl << endl;
}


void Player::showWeaponInventory() const
{
    for(int i = 0; i < weapons.size(); i++)
    {
        cout << i+1 << ": " << weapons[i].getName() << ": " << weapons[i].getDamage() << " damage." << endl;
    }
}


//FOR TESTING PURPOSES
void Player::printDetails() const
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


void Player::setName(string newName)
{
    name = newName;
}
void Player::setVulnerability(double d)
{
    vulnerability = d;
}

//functions to gain experience
void Player::gainStrength(double amount)
{
    int oldStrength = strength;
    strength += amount;
    
    //if your strength leveled up, gain an extra life point
    if(int(strength) > oldStrength)
    {
        maxHp += 3;
        hp++;
        cout << name << " leveled up!" << endl;
        cout << name << " healed by 1 HP and gained 3 MAX HP." << endl;
        cout << name << " has " << hp << " HP." << endl;
        cout << "Max HP is now " << maxHp << endl << endl;
    }
}
void Player::gainAttack(double amount)
{
    int oldAttack = attack;
    attack += amount;
    
    //if your attack leveled up, gain an extra life point
    if(int(attack) > oldAttack)
    {
        maxHp += 3;
        hp++;
        cout << name << " leveled up!" << endl;
        cout << name << " healed by 1 HP and gained 3 MAX HP." << endl;
        cout << name << " has " << hp << " HP." << endl;
        cout << "Max HP is now " << maxHp << endl << endl;
    }
}
void Player::gainAgility(double amount)
{
    int oldAgility = agility;
    agility += amount;
    
    //if your agility leveled up, gain an extra life point
    if(int(agility) > oldAgility)
    {
        maxHp += 3;
        hp++;
        cout << name << " leveled up!" << endl;
        cout << name << " healed by 1 HP and gained 3 MAX HP." << endl;
        cout << name << " has " << hp << " HP." << endl;
        cout << "Max HP is now " << maxHp << endl << endl;
    }
}
void Player::gainDefense(double amount)
{
    int oldDefense = defense;
    defense += amount;
    
    //if your agility leveled up, gain an extra life point
    if(int(defense) > oldDefense)
    {
        maxHp += 3;
        hp++;
        cout << name << " leveled up!" << endl;
        cout << name << " healed by 1 HP and gained 3 MAX HP." << endl;
        cout << name << " has " << hp << " HP." << endl;
        cout << "Max HP is now " << maxHp << endl << endl;
    }
}


//add gold (or subtract if amount is negative) to coin pouch
void Player::gainGold(int amount)
{
    if(amount > 0)
    {
        cout << name << " gained " << amount << " coins." << endl;
    }
    if(amount < 0)
    {
        //if you have less coins than the program wants to take, change amount so it brings you to 0.
        //this can't happen in stores, only during misfortunes
        if(gold < amount)
        {
            amount = gold;
        }
        cout << name << " lost " << -1 * amount << " coins." << endl;
    }
    gold += amount;
}


//return false if no weapon is added. This makes it so you can't be charged at shops
//for weapons you don't buy.
bool Player::addWeapon(Weapon w)
{
    bool returnValue;
    ValidInput valid;
    TextFormat text;
    
    if(w.getName() == "fist")
    {
        cout << "You cannot add fist to your inventory." << endl;
        returnValue = false;
    }
    else if(weapons.size() < sizeWeapons)
    {
        weapons.push_back(w);
        cout << name << " obtained a " << w.getName() << "." << endl;
        returnValue = true;
    }
    else //if the player has no room, ask if they want to drop a weapon to get the new one.
    {
        cout << name << " has too many weapons to keep this." << endl << endl;
        
        //now repeatedly ask if the player wants to discard a weapon.
        string yn; //holds 1 for yes, 2 for no.
        bool dropWeapon; //true if the user wants to drop a weapon.
        do {
            cout << "Do you want to get rid of a weapon to make room for " << w.getName() << "?" << endl;
            cout << "You won't get any money from doing this." << endl;
            cout << "1: Yes" << endl;
            cout << "2: No" << endl;
            
            getline(cin, yn); //get user input
            text.clearScreen();
            
            //dropWeapon is false if input is not 1 or 2. stringValidInt will print an error message.
            dropWeapon = valid.stringValidInt(yn, 1, 2);
            
            if(dropWeapon)
            {
                //if input was valid and it was 2, return false.
                if(stoi(yn) == 2)
                {
                    return false; //return false because no weapon was added to player's inventory.
                }
            }
        } while(!dropWeapon);
        
        text.clearScreen();
        
        
        //At this point, the user has answered yes about dropping a weapon.
        //Now, ask the player which weapon they want to drop.
        string weaponChoice; //stores user input
        bool validWeapon; //will be true if the input is between 0 and the number of weapons the user has.
        
        //repeatedly ask the player which weapon they want to drop until they choose a valid weapon or quit.
        do {
            cout << "Which weapon do you want to drop?" << endl << endl;
            cout << "0: None; don't replace any weapon with " << w.getName() << "." << endl;
            showWeaponInventory(); //list the other choices
            
            getline(cin, weaponChoice); //get input
            text.clearScreen();
            
            //validWeapon is false if input is not a number from the list.
            //stringValidInt will print an error message if the input is invalid.
            validWeapon = valid.stringValidInt(weaponChoice, 0, weapons.size());
            
            //if the player chose 0, return false and quit.
            if(validWeapon && stoi(weaponChoice) == 0)
            {
                cout << name << " doesn't want to drop a weapon." << endl;
                //text.wait();
                return false;
            }
        } while(!validWeapon);
        
        
        text.clearScreen();
        
        //At this point, a valid weapon has been chosen.
        removeWeapon(stoi(weaponChoice) - 1);
        addWeapon(w);
        
        returnValue = true; //if the player got rid of a weapon and got the new one, return true.
    }
    
    //if the player got a new weapon, ask them if they want to equip it.
    if(returnValue == true)
    {
        string yn; //holds user input. It is valid if it is 1 (yes) or 2 (no).
        bool validChoice; //true if the input is valid
        
        //repeatedly ask the user if they want to equip the new weapon
        do {
            cout << "Do you want to equip your new " << w.getName() << "?" << endl;
            cout << "1: Yes" << endl;
            cout << "2: No" << endl;
            
            getline(cin, yn); //get user input
            text.clearScreen();
            
            //validChoice is false if input is not 1 or 2. stringValidInt will print an error message.
            validChoice = valid.stringValidInt(yn, 1, 2);
            
            if(validChoice)
            {
                //if input was valid and it was 1 (yes), equip the weapon.
                if(stoi(yn) == 1)
                {
                    weapon = w;
                    cout << name << " equipped the " << w.getName() << "." << endl;
                }
            }
        } while(!validChoice); //end of asking if they want to equip new weapon
    }
    
    return returnValue;
} //end of addWeapon function


//return true if the weapon was removed
bool Player::removeWeapon(int index)
{
    //if the index is valid, remove the weapon
    if(index >= 0 && index < weapons.size())
    {
        Weapon w = weapons[index]; //get a copy of the weapon from the vector
        cout << name << " no longer has his " << w.getName() << "." << endl;
        weapons.erase(weapons.begin() + index); //remove the weapon
        
        //if the name of the weapon you sold matches the name of the weapon the player is holding,
        //unequip it and notify the player that he is no longer holding a weapon.
        if(weapon.getName() == w.getName())
        {
            Weapon fist;
            weapon = fist;
            cout << name << " is no longer holding any weapon. You may want to equip another weapon." << endl;
        }
        return true;
    }
    else //if the index is invalid, print a message and return false
    {
        cout << "Invalid choice for weapon. Choose between 1 and " << weapons.size();
        return false;
    }
}


//this only produces a copy of the weapon; should not be modified.
Weapon Player::getWeaponAt(int index) const
{
    if(index >= 0 && index < weapons.size())
    {
        return weapons[index];
    }
    else //invalid index
    {
        cout << "Index " << index << " does not exist in " << name << " \'s weapon inventory." << endl;
        cout << "Player::getWeaponAt(index) returning default weapon (fist) instead." << endl;
        cout << "If inputs were handled properly, this message should never print." << endl;
        Weapon fist; //default Weapon
        return fist;
    }
}


//this only produces a copy of the item; should not be modified.
Item Player::getItemAt(int index) const
{
    if(index >= 0 && index < items.getSizeItems())
    {
        return items.getItemAt(index);
    }
    else //invalid index
    {
        cout << "Index " << index << " does not exist in " << name << " \'s inventory." << endl;
        cout << "Player::getItemAt(index) returning default item instead." << endl;
        cout << "If inputs were handled properly, this message should never print." << endl;
        Item defaultItem;
        return defaultItem;
    }
}


void Player::changeItemQuantity(int index, int deltaq)
{
    //this is fine because invalid input is handled inside items.changeItemQuantity
    items.changeItemQuantity(index, deltaq);
}