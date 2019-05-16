// CSCI1300 Fall 2018
// Author: John Salame
// Recitation: 104 – Richard Tilquist
// Cloud9 Workspace Editor Link: https://ide.c9.io/josa5095/csci1300/Project3
// Project 3

#include <iostream>
#include "Shop.h"
#include "ValidInput.h"
#include "TextFormat.h"
using namespace std;

Shop::Shop()
{
    //do nothing since the member variables are arrays and vectors
}


/**
 * Constructor which sets the quantities of the items.
 * @param quantities: array of ints representing the quantity each item should have in the Inventory
 * @param size: the number of elements in the quantities array
 */
Shop::Shop(int quantities[], int size)
{
    for(int i = 0; i < size; i++)
    {
        //input only valid (non-negative) quantities into valid indexes of the items array (inventory)
        if(i < itemStock.getSizeItems() && quantities[i] >= 0)
        {
            itemStock.setItemQuantity(i, quantities[i]);
        }
    }
}


//add a weapon to the weaponStock vector
void Shop::addWeapon(Weapon w)
{
    weaponStock.push_back(w);
}


void Shop::printItemOptions()
{
    cout << endl;
    for(int i = 0; i < 5; i++)
    {
        Item item = itemStock.getItemAt(i);
        cout << "Item " << i+1 << ": " << item.getName() << endl;
        cout << item.getDescription() << endl;
        
        if(item.getName() != "Unimplemented")
        {
            cout << "Buy price: " << item.getBuyPrice() << endl;
            cout << "Sell price: " << item.getSellPrice() << endl;
            cout << "Quantity: " << item.getQuantity() << endl;
        }
        cout << endl;
    }
    cout << endl << endl;
}


void Shop::printWeaponOptions()
{
    cout << endl;
    for(int i = 0; i < weaponStock.size(); i++)
    {
        cout << "Option " << i+1 << ":" << endl;
        Weapon w = weaponStock[i];
        cout << w.getName() << ":" << endl;
        cout << w.getDamage() << " damage." << endl;
        cout << "Buy price: " << w.getBuyPrice() << endl;
        cout << "Sell price: " << w.getSellPrice() << endl;
        cout << endl;
    }
}


//have a player buy an item from the shop
//return true if the player bought something
bool Shop::buyItem(Player& player)
{
    TextFormat text; //for wait() and clearScreen()
    ValidInput valid;
    
    string itemInput;
    bool validItem; //true if the player chose a valid item in the store
    int itemIndex;
    int storeQuantity;
    
    text.clearScreen();
    
    //ask the user to choose an item to buy until they choose "buy nothing" or choose an item with at least 1 quantity.
    do {
        cout << player.getName() << " wants to buy an item." << endl << endl;
        //show the player's inventory
        player.showInventory();
        text.wait();
        text.clearScreen();
        
        cout << "_____________________________________________________" << endl << endl;
        cout << player.getName() << " has " << player.getGold() << " gold." << endl;
        cout << "Choose an item for " << player.getName() << " to buy:" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        cout << "0: Buy Nothing." << endl;
        printItemOptions();
        cout << "Choose an item for " << player.getName() << " to buy." << endl;
        
        getline(cin, itemInput); //get user input
        text.clearScreen(); //clear the screen
        
        Inventory inv; //used to get the number of unique items in an inventory
        validItem = valid.stringValidInt(itemInput, 0, inv.getSizeItems()); //check if input is valid
        
        if(validItem)
        {
            itemIndex = stoi(itemInput) - 1; //track the index of the item the user entered
            
            //if the player chooses 0, quit.
            if(itemIndex == -1)
            {
                cout << player.getName() << " decided not to buy any item." << endl;
                cout << "Returning to main shop menu." << endl;
                text.wait();
                text.clearScreen();
                return false; //return false because the player did not buy anything.
            }
            
            //if the function makes it this far, the item has a valid index (and it is not -1). Get the quantity of the chosen item.
            storeQuantity = itemStock.getItemAt(itemIndex).getQuantity();
            
            //if the player chooses an item that is out of stock, warn the player and make input invalid
            if(storeQuantity <= 0)
            {
                validItem = false;
                cout << endl << "The store does not have any of " << itemStock.getItemAt(itemIndex).getName() << "." << endl;
                text.wait();
                text.clearScreen();
            }
            //if the player does not have enough gold to buy the item, make the choice invalid.
            else if(itemStock.getItemAt(itemIndex).getBuyPrice() > player.getGold())
            {
                validItem = false;
                cout << player.getName() << " cannot afford to buy a " << itemStock.getItemAt(itemIndex).getName() << "." << endl << endl;
                text.wait();
                text.clearScreen();
            }
        }
        else //if the input was invalid, display the "Invalid input! Please enter a number between x and y.", then wait.
        {
            text.wait();
            text.clearScreen();
        }
        
    } while(!validItem);
    
    
    //At this point, a valid item with at least 1 quantity has been chosen.

    string quantInput; //user input for quantity to purchase
    bool validQuantity = false; //true if there is at least quantInput to buy and you have enough money.
    int quantBuy; //how much you will end up buying
    int price = 0; //how much the player will need to pay in total
    
    //ask the user to select a quantity or back out of the menu until they choose an acceptable amount.
    do {
        cout << endl << endl;
        cout << player.getName() << " wants to buy " << itemStock.getItemAt(itemIndex).getName() << "." << endl;
        //print how much gold the player has and how much of the item the player has.
        cout << player.getName() << " has " << player.getGold() << " gold and ";
        cout << player.getItemAt(itemIndex).getQuantity() << " " << itemStock.getItemAt(itemIndex).getName() << "." << endl;
        cout << endl << endl;
        cout << "How many " << itemStock.getItemAt(itemIndex).getName() << " do you want to buy?" << endl;
        cout << "The store currently has " << storeQuantity << " of this item." << endl;
        cout << "Cost per item: " << itemStock.getItemAt(itemIndex).getBuyPrice() << "." << endl;
        
        getline(cin, quantInput); //get user input
        text.clearScreen(); //clear the screen
        
        validQuantity = valid.stringValidInt(quantInput, 0, storeQuantity); //check if input is valid
        
        //If you are not trying to buy more than the store has, check to see if the player has enough money.
        //Print statements for trying to buy more than the store has is already handled in Inventory::changeItemQuantity
        if(validQuantity)
        {
            quantBuy = stoi(quantInput); //turn string to int
            
            //if the user entered 0, quit back to the main shopping menu (int Story.cpp)
            if(quantBuy == 0)
            {
                cout << player.getName() << " decided not to buy anything." << endl;
                cout << "Press enter to continue shopping." << endl;
                text.wait();
                text.clearScreen();
                return false;
            }
            else //if the player decides to buy at least one item, calculate the total cost.
            {
                price = quantBuy * itemStock.getItemAt(itemIndex).getBuyPrice();
            }
            
            //if the player does not have enough money, tell the player and set validQuantity to false.
            if(player.getGold() < price)
            {
                validQuantity = false;
                cout << player.getName() << " does not have enough money." << endl;
                cout << "The player has " << player.getGold() << " gold. The order costs " << price << " gold." << endl;
                
                //calculate how much the player can buy at most:
                int max = 0;
                //increment max if the player can afford one more item and max is less than storeQuantity
                while(player.getGold() >= (max + 1) * player.getItemAt(itemIndex).getBuyPrice() && max < storeQuantity)
                {
                    max++;
                }
                cout << player.getName() << " can buy " << max << " of this item at most." << endl;
                cout << endl << endl;
                text.wait();
                text.clearScreen();
            }
        }
    } while(!validQuantity); //end of do while loop
    
    //At this point, the player has chosen an amount that he/she can buy.
    itemStock.changeItemQuantity(itemIndex, -1 * quantBuy); //remove items from store
    player.changeItemQuantity(itemIndex, quantBuy); //add the items to player inventory
    player.gainGold(-1 * price); //spend the gold
    cout << player.getName() << " has " << player.getGold() << " gold remaining." << endl;
    
    
    //now, ask the player if they want to buy any more items.
    string yn; //hold user input of 0 (NO) or 1 (YES)
    bool validYn; //true if the user typed 0 or 1
    bool buyMore; //true if the player wants to keep buying more items
    
    //keep asking the user to enter 0 or 1.
    do {
        cout << endl;
        text.wait();
        text.clearScreen();
        cout << "Do you want " << player.getName() << " to buy more items?" << endl;
        cout << "0: No." << endl;
        cout << "1: Yes." << endl;
        
        getline(cin, yn); //get user input
        text.clearScreen();
        
        validYn = valid.stringValidInt(yn, 0, 1);
        
        if(validYn)
        {
            //if the user chose 0, don't buy more; return to main shopping menu
            if(stoi(yn) == 0)
            {
                buyMore = false;
            }
            //if the user chose 1, buy more items with this character.
            else
            {
                buyMore = true;
            }
        }
        
    } while(!validYn);
    
    //if the player chose to buy more, restart the buyItem function with that player, then return true.
    if(buyMore)
    {
        buyItem(player);
    }
    
    return true; //if the function makes it this far, it means this player bought at least one item; return true.
    
} //end of buyItem function


//have a player sell an item to the shop
//return true if you sell something, return false if you don't.
bool Shop::sellItem(Player& player)
{
    TextFormat text; //for wait() and clearScreen()
    ValidInput valid; //for checking if input is a valid number
    
    text.clearScreen();
    
    string itemInput;
    bool validItem; //true if the player chose a valid item in the store
    int itemIndex;
    
    //ask the user to choose an item to buy until they choose "buy nothing" or choose an item with at least 1 quantity.
    do {
        cout << "_____________________________________________________" << endl << endl;
        cout << player.getName() << " wants to sell an item." << endl << endl;
        cout << player.getName() << " has " << player.getGold() << " gold." << endl;
        cout << "Choose an item for " << player.getName() << " to sell (Press 0 if you don't want to sell anything):" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        //show the player's inventory
        player.showInventory();
        cout << "Choose an item for " << player.getName() << " to sell (Press 0 if you don't want to sell anything)." << endl;
        
        getline(cin, itemInput); //get user input
        text.clearScreen(); //clear the screen
        
        Inventory inv; //used to get the number of unique items in an inventory
        validItem = valid.stringValidInt(itemInput, 0, inv.getSizeItems()); //check if input is valid
        
        if(validItem)
        {
            itemIndex = stoi(itemInput) - 1;
            
            //if the player chose 0, exit out and return false
            if(itemIndex == -1)
            {
                cout << player.getName() << " did not sell an item." << endl;
                text.wait();
                text.clearScreen();
                return false; //did not sell an item
            }
            else if(player.getItemAt(itemIndex).getQuantity() <= 0)
            {
                validItem = false;
                cout << player.getName() << " does not have any " << player.getItemAt(itemIndex).getName() << "." << endl;
                text.wait();
                text.clearScreen();
            }
        }
    } while(!validItem);
    
    
    //At this point, a valid item with at least 1 quantity has been chosen from the player's inventory.
    
    string quantInput; //user input for quantity to purchase
    bool validQuantity = false; //true if you are not selling more items than you have.
    int heldQuantity = player.getItemAt(itemIndex).getQuantity(); //how much the player has
    int quantSell; //how much you will end up selling
    int revenue; //how much your items will sell for, total
    
    //ask the user to select a quantity or back out of the menu until they choose an acceptable amount.
    do {
        cout << endl << endl;
        cout << player.getName() << " wants to sell " << itemStock.getItemAt(itemIndex).getName() << "." << endl;
        cout << player.getName() << " has " << player.getGold() << " gold and ";
        cout << heldQuantity << " " << itemStock.getItemAt(itemIndex).getName() << "." << endl;
        cout << endl << endl;
        cout << "How many of " << player.getItemAt(itemIndex).getName() << " do you want to sell?" << endl;
        cout << "Sell price: " << itemStock.getItemAt(itemIndex).getSellPrice() << " gold per item." << endl;
        
        getline(cin, quantInput); //get user input
        text.clearScreen();
        
        //check if input is valid (quantInput is between 0 and number of items in player inventory)
        validQuantity = valid.stringValidInt(quantInput, 0, heldQuantity);
        
        //If you are not trying to sell more items than you have, go ahead and sell the items
        //Print statements for trying to sell too many items is already handled in Inventory::changeItemQuantity
        if(validQuantity)
        {
            quantSell = stoi(quantInput); //turn string to int
            revenue = quantSell * player.getItemAt(itemIndex).getSellPrice();
            
            //if the user entered 0, exit back to the main shopping menu (in Story.cpp)
            if(quantSell == 0)
            {
                cout << player.getName() << " decided not to sell anything." << endl;
                cout << "Press enter to continue shopping." << endl;
                text.wait();
                return false; //return false since the player sold 0 items.
            }
        } //end of if(validQuantity)
            
    } while(!validQuantity); //end of do while asking how much the player wants to sell
    
    //AT THIS POINT, THE PLAYER HAS CHOSEN A VALID QUANTITY TO SELL.
    //BEFORE THEY SELL, HAVE THE USER VERIFY THEIR CHOICE BY ANSWERING A YES OR NO QUESTION.
    bool validConfirmation = false;
    
    //only continue past this do while loop if they confirm that they want to sell.
    do {
        string yn; //holds user input of 1 (yes) or 2 (no)
        cout << endl << endl;
        //Print "Are you sure you want to sell x itemName for y gold?"
        cout << "Are you sure you want to sell " << quantSell << " ";
        cout << player.getItemAt(itemIndex).getName() << " for ";
        cout << revenue << " gold?" << endl;
        cout << "1: Yes. Sell the items." << endl;
        cout << "2: No. Sell something else." << endl;
        
        
        getline(cin, yn); //get user input
        text.clearScreen();
        
        //confirmation is valid if user typed a 1 or 2
        validConfirmation = valid.stringValidInt(yn, 1, 2);
        
        //IF THE USER TYPED 2 (No), go back to the start of sellItem and run it again (using recursion).
        if(validConfirmation && stoi(yn) == 2)
        {
            return sellItem(player);
        }
    } while(!validConfirmation); //end of do while asking if they are sure they want to sell
    
    
    //At this point, the player has chosen items to sell and has confirmed intent.
    itemStock.changeItemQuantity(itemIndex, quantSell); //add items to the store
    player.changeItemQuantity(itemIndex, -1 * quantSell); //remove the items from player inventory
    player.gainGold(revenue); //gain gold from selling
    
    //now, ask the player if they want to sell any more items.
    string yn; //hold user input of 0 (NO) or 1 (YES)
    bool validYn; //true if the user typed 0 or 1
    bool sellMore; //true if the player wants to keep buying more items
    
    //keep asking the user to enter 0 or 1.
    do {
        cout << endl;
        text.wait();
        text.clearScreen();
        cout << "Do you want " << player.getName() << " to sell more items?" << endl;
        cout << "0: No." << endl;
        cout << "1: Yes." << endl;
        
        getline(cin, yn); //get user input
        text.clearScreen();
        
        validYn = valid.stringValidInt(yn, 0, 1);
        
        if(validYn)
        {
            //if the user chose 0, don't buy more; return to main shopping menu
            if(stoi(yn) == 0)
            {
                sellMore = false;
            }
            //if the user chose 1, buy more items with this character.
            else
            {
                sellMore = true;
            }
        }
        
    } while(!validYn);
    
    //if the player chose to buy more, restart the buyItem function with that player, then return true.
    if(sellMore)
    {
        sellItem(player);
    }
    
    return true; //sold items
} //end of sellItem function


//have a player buy a weapon from the shop
bool Shop::buyWeapon(Player& player)
{
    //if the weapon index is valid, ask the user to choose one of the weapons
    ValidInput valid;
    TextFormat text; //for wait() and clearScreen()
    bool returnValue; //this is used near the bottom of the function
    
    text.clearScreen();
    
    string choice; //which number in the list of weapons the user will choose
    bool validChoice = false;
    int weaponIndex; //will get a value once valid input is entered
    int price; //how much the chosen weapon costs
    
    //prompt the user to select a weapon until they choose a valid number
    do {
        cout << endl << endl;
        cout << "__________________________________________________________" << endl << endl;
        cout << player.getName() << " wants to buy a weapon." << endl << endl;
        cout << player.getName() << " has " << player.getGold() << " gold." << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        text.wait(); //wait before displaying a long list of the store's weapons.
        
        cout << "Option 0: Buy nothing. Return to the main shop menu." << endl;
        printWeaponOptions();
        cout << "Choose one of the options above:" << endl;
        
        getline(cin, choice); //get user input
        text.clearScreen();
        
        //choice is valid if it is 0 or a number from 1 to the number of weapons in stock.
        validChoice = valid.stringValidInt(choice, 0, weaponStock.size());
        
        //if the user input is valid, get its index in the weaponStock vector.
        //if the index is -1 (choice was 0), then exit the funciton.
        //else, get the buy price of the weapon and check if the player can afford to buy it.
        if(validChoice)
        {
            weaponIndex = stoi(choice) - 1; //convert input to int
            
            //now, we look at cases which either quit or invalidate the input
            //if the user typed 0, quit
            if(weaponIndex == -1)
            {
                cout << player.getName() << " decided not to buy anything." << endl;
                cout << "Press enter to continue shopping." << endl;
                text.wait();
                return false; //bought no weapons
            }
            else //if weaponIndex is valid, 
            {
                price = weaponStock[weaponIndex].getBuyPrice();
            }
            
            
            //if the player can't afford to buy the weapon, make validChoice false.
            if(player.getGold() < price)
            {
                validChoice = false;
                cout << player.getName() << " does not have enough money." << endl;
                cout << "The player has " << player.getGold() << " gold. The weapon costs " << price << "." << endl;
                text.wait();
            }
        }
    } while(!validChoice);
    
    //at this point, a valid weapon has been chosen, and its index and price are known.
    //if there is room in the player's weapon inventory to add the weapon, buy it.
    if(player.addWeapon(weaponStock[weaponIndex]))
    {
        weaponStock.erase(weaponStock.begin() + weaponIndex); //remove the weapon from the store
        player.gainGold(-1 * price); //spend money
        returnValue = true; //bought a weapon
    }
    else //no room to keep weapon
    {
        cout << "Consider selling some weapons to make room." << endl;
        returnValue = false; //did not buy a weapon
    }
    
    cout << player.getName() << " has " << player.getGold() << " gold left." << endl;
    cout << endl;
    text.wait();
    return returnValue;
} //end of buyWeapon function


//have a player sell a weapon to the shop
bool Shop::sellWeapon(Player& player)
{
    //if the weapon index is valid, ask the user to choose one of the weapons
    ValidInput valid;
    TextFormat text; //for wait() and clearScreen()
    
    text.clearScreen();
    
    bool validChoice = false; //will be true when the user enters a valid number from the list
    string choice; //which number in the list of weapons the user will choose (from his inventory)
    int weaponIndex; //will get a value once valid input is entered
    int revenue; //how much the chosen weapon sells for
    
    //prompt the user to select a weapon until they choose a valid number
    do {
        cout << endl << endl;
        cout << player.getName() << " wants to sell a weapon." << endl;
        cout << player.getName() << " has " << player.getGold() << " gold." << endl << endl;
        text.wait();
        text.clearScreen();
        cout << "Choose one of the options below:" << endl;
        cout << "0: Don't sell a weapon. Return to main shop menu." << endl;
        player.showWeaponInventory();
        
        getline(cin, choice); //get user input
        text.clearScreen();
        
        //if the input was valid, set validChoice to true; else, set it to false.
        validChoice = valid.stringValidInt(choice, 0, player.getNumWeapons());
        
        
        //if the choice is valid, store the index of the chosen weapon.
        if(validChoice)
        {
            weaponIndex = stoi(choice) - 1; //convert input to int
            //if weaponIndex is not -1, set revenue down below
            
            //if the user typed 0, quit
            if(weaponIndex == -1)
            {
                cout << player.getName() << " decided not to sell anything." << endl;
                cout << "Press enter to continue shopping." << endl;
                text.wait();
                return false; //sold no weapons
            }
            else //if the user entered a valid non-zero number, get the weapon index and set revenue to sell price.
            {
                revenue = player.getWeaponAt(weaponIndex).getSellPrice();
            }
            
            
            //before they sell, ask if they are sure they want to sell.
            bool validConfirmation = false;
            
            //only continue past this do while loop if they say yes
            do {
                string yn; //holds user input of 0 (no) or 1 (yes)
                cout << endl << endl;
                //Print "Are you sure you want to sell <weaponName> for y gold?"
                cout << "Are you sure you want to sell ";
                cout << player.getWeaponAt(weaponIndex).getName() << " for ";
                cout << revenue << " gold?" << endl;
                cout << "0: No. Choose a different weapon to sell." << endl;
                cout << "1: Yes. Sell the weapon." << endl;
                
                getline(cin, yn); //get user input
                text.clearScreen();
                
                //confirmation is valid if user typed a 0 or 1
                validConfirmation = valid.stringValidInt(yn, 0, 1);
                
                //if the user typed 0, go back to the start of sellItem
                if(validConfirmation && stoi(yn) == 0)
                {
                    validChoice = false; //now they will be asked again what they want to sell.
                }
            } while(!validConfirmation); //end of do while asking if they are sure they want to sell
            
        } //end of if(validChoice)
        
    } while(!validChoice);
    
    //At this point, the player has chosen which Weapon to sell and has confirmed intent.
    Weapon w = player.getWeaponAt(weaponIndex);
    addWeapon(w); //add the weapon to the shop
    player.removeWeapon(weaponIndex); //remove the weapon from the player's inventory
    player.gainGold(revenue); //get paid for selling the weapon.
    cout << endl;
    text.wait();
    return true; //sold a weapon
} //end of sellWeapon function
