#include "player.h"
#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <chrono>

// Constructor
gameData::gameData(int a, int b, std::vector<std::string> vec){
    romance = a;
    money = b;
    for (std::string i : vec){
    inventory.push_back(i);
    }
}

// Methods
void gameData::work(int amount){
    // This is how the player earns money
    // There is a 1 seccond wait time before the money is added to the user's total

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    money += amount;
    std::cout << "Earned " << amount << " dollars.\n";
}

void gameData::check(){
    // Checks the players stats and prints them to the terminal.
    std::cout << "Romance: " << romance << '\n';
    std::cout << "Money: " << money << '\n';

    std::cout << "Inventory: ";

    for (std::string i : inventory){
    std::cout << i << " ";
    }
    std::cout << '\n';
}

void gameData::inventoryAdd(std::string str){
    // Adds a value to the inventory cleanly
    inventory.push_back(str);
}

void gameData::inventoryRemove(std::string target){
    // Finds the target string and removes it from the inventory cleanly
    int target_index = 0;
    for (int i = 0; i < inventory.size(); i ++){
    if (inventory[i] == target) target_index = i;
    }
    inventory.erase(inventory.begin() + target_index); // Removes the value at the specified index (formula = start_index + target_index)
}

bool gameData::inventoryItemCheck(std::string item){

    bool has;

    for (std::string i : inventory){
    if (i == item){
        has = true;
        break;
    } 
    }

    if (has == true){
    return true;
    }
    
    return false;
}