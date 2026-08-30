#include <cctype>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>
#include <cstdlib>

// Classes

class gameData{
  public:
    // Data
    int romance; // The total romance level that the user has with Yuki
    int money; // How much money the user has
    std::vector<std::string> inventory; // The user's current inventory

    // Constructor
    gameData(int a, int b, std::vector<std::string> vec){
      romance = a;
      money = b;
      for (std::string i : vec){
        inventory.push_back(i);
      }
    }

    // Methods
    void work(int amount){
      // This is how the player earns money
      // There is a 1 seccond wait time before the money is added to the user's total
      std::this_thread::sleep_for(std::chrono::seconds(1));
      money += amount;
      std::cout << "Earned " << amount << " dollars.\n";
    }
    
    void check(){
      // Checks the players stats and prints them to the terminal.
      std::cout << "Romance: " << romance << '\n';
      std::cout << "Money: " << money << '\n';

      std::cout << "Inventory: ";

      for (std::string i : inventory){
        std::cout << i << " ";
      }
      std::cout << '\n';
    }

    void inventoryAdd(std::string str){
      // Adds a value to the inventory cleanly
      inventory.push_back(str);
    }

    void inventoryRemove(std::string target){
      // Finds the target string and removes it from the inventory cleanly
      int target_index = 0;
      for (int i = 0; i < inventory.size(); i ++){
        if (inventory[i] == target) target_index = i;
      }
      inventory.erase(inventory.begin() + target_index); // Removes the value at the specified index (formula = start_index + target_index)
    }
};

int randomNumberRange(int a, int b){
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen);
}

// Functions

void talk(){
  std::vector<std::string> responses = {"Hrmph, It's not like i enjoy seeing you or anything...", "Here eat some of this, I accidently made to much...", "It's not like I like you or anything!"};

  int index = randomNumberRange(0, 2);

  std::cout << "Yuki: " << responses[index] << "\n";
}

void help(){
  std::vector<std::string> commands = {"talk", "chat", "work", "check", "/quit", "/help", "/clear"};

  std::cout << "Valid commands:\n";

  for (std::string i : commands){
    std::cout << i << '\n';
  }
}

void clearScreen(){
  std::system("clear");
}

void shop(gameData& player){

  std::cout << "Entered shop menu" << '\n';

  while (true){
    std::string input;

    std::cout << "shop> ";
    
    std::cin >> input;

    if (input == "/quit") break;
    
    else if (input == "/help"){
     std::cout << "Current commands for shop:\n";
     std::cout << "/quit\n" << "/help\n" << "buy\n";
    }

    // Buy menu opened
    else if (input == "buy"){

      bool cake_owned = false;
      bool gift_owned = false;
      bool ring_owned = false;

      for (std::string i : player.inventory){
        if (i == "cake") cake_owned = true;

        else if (i == "gift") gift_owned = true;

        else if (i == "ring") ring_owned = true;
      }
      
      
      std::cout << "What would you like to buy?\n";
      std::cout << "Current items: cake, gift, ring\n";

      std::string item;

      std::cin >> item;

      transform(item.begin(), item.end(), item.begin(), ::tolower);

      if (item == "cake"){
        if (player.money >= 5 && cake_owned == false){
            player.money -= 5;
            player.inventoryAdd("cake");
            std::cout << "Bought cake\n";
        }
        else std::cout << "You either own cake or you're too poor!\n";
      }
      else if (item == "gift"){
        if (player.money >= 50 && gift_owned == false){
          player.money -= 50;
          player.inventoryAdd("gift");
          std::cout << "Bought gift\n";
        }
        else std::cout << "You either own gift or you're too poor!\n";
      }
      else if (item == "ring"){
        if (player.money >= 100 && ring_owned == false){
          player.money -= 100;
          player.inventoryAdd("ring");
          std::cout << "Bought ring\n";
        }
        else std::cout << "You either own ring or you're too poor!\n";
      }
      else std::cout << "Item does not exist!\n";
    }
    // Buy menu closed
        
    else std::cout << "Error, command does not exist\n\n";
  }
}

// Entry point

int main(){

  int a = 0;
  int b = 0;
  
  std::vector<std::string> vec;

  gameData player(a, b, vec); // Create the player object and initialise the data

  std::string input;

  while (true){

    std::cout << "Enter command (/quit to quit, /help for help):" << '\n' << "> ";
    
    std::cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::tolower);

  
    if (input == "/quit") break;
    else if (input == "check") player.check();
    else if (input == "work") player.work(5);
    else if (input == "talk" || input == "chat") talk();
    else if (input == "/help") help();
    else if (input == "/clear") clearScreen();
    else if (input == "shop") shop(player); // Opens the shop for the player
    else std::cout << "Error, command does not exist\n\n";
  }
  
  return 0;
}
