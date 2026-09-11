#include "player.h"
#include "functions.h"
#include "game.h"
#include <cctype>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <algorithm>

// Entry point

int main(){

  int a = 0;
  int b = 0;
   
  std::vector<std::string> vec;

  gameData player(a, b, vec); // Create the player object and initialise the data

  bool saveFile;

  saveFile = load(player);

  if (saveFile == false) return 1;

  if (player.first_run == 0){
    firstRun(player);
    clearScreen();
  }
  
  std::string input;

  while (true){

    std::cout << "Enter command (/quit to quit, /help for help):" << '\n' << "> ";
    
    std::cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::tolower);

  
    if (input == "/quit"){
      bool temp;
      temp = save(player);
      if (temp == false){
        return 1;
      }
      else std::cout << "Saved data!\n";
      break;
    }
    else if (input == "check") player.check();
    else if (input == "work") player.work(5);
    else if (input == "talk" || input == "chat") talk();
    else if (input == "/help") help();
    else if (input == "/clear") clearScreen();
    else if (input == "shop") shop(player); // Opens the shop for the player
    else if (input == "save") {
      bool temp;
      temp = save(player);

      if (temp == false){
        return 1;
      }
      else std::cout << "Saved data!\n";
    }
    else if (input == "give") giveItem(player);
    else if (input == "story") storyMenu();
    else if (input == "view") view(player);
    else if (input == "kiss") {
      bool temp = gameRun("Kiss Yuki!", 500);
      if (temp) player.romance += 30;
      std::cout << "You earned 30 romance";
    }
    else std::cout << "Error, command does not exist\n\n";
  }
  return 0;
}

