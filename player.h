#pragma once

#include <string>
#include <vector>
#include <algorithm>

class gameData{
  public:
    // Data
    int romance; // The total romance level that the user has with Yuki
    int money; // How much money the user has
    int first_run = 0; // Used to check if it is the first run
    std::vector<std::string> inventory; // The user's current inventory

    // Constructor
    gameData(int a, int b, std::vector<std::string> vec);

    // Methods
    void work(int amount);
    void check();
    void inventoryAdd(std::string str);
    void inventoryRemove(std::string target);
    bool inventoryItemCheck(std::string item);
};
