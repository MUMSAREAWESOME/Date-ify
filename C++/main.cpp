#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>


struct gameData{
  int romance = 0;
  int money = 0;

  std::vector<std::string> inventory;
};




int randomNumberRange(int a, int b){
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen);
}

void work(gameData &chisai, int amount){
  std::this_thread::sleep_for(std::chrono::seconds(1)); // This is a one seccond delay.
  
  chisai.money += amount;

  std::cout << "Earned " << amount << " dollars.\n";
}

void check(gameData &chisai){
  std::cout << "Romance: " << chisai.romance << "\n" << "Money: "  << chisai.money << "\n";

  std::cout << "Inventory: ";

  for (std::string i : chisai.inventory){
    std::cout << i << " ";
  }

  std::cout << "\n";
}

void talk(){
  std::vector<std::string> responses = {"Hrmph, It's not like i enjoy seeing you or anything...", "Here eat some of this, I accidently made to much...", "It's not like I like you or anything!"};

  int index = randomNumberRange(0, 2);

  std::cout << "Yuki: " << responses[index] << "\n";
}

void help(){
  std::vector<std::string> commands = {"talk", "chat", "work", "check"};

  std::cout << "Valid commands:\n";

  for (std::string i : commands){
    std::cout << i << "\n";
  }
}

int main(){

  gameData chisai;

  std::string input;

  while (true){

    std::cout << "Enter command (/quit to quit, /help for help):\n";
    
    std::cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::tolower);

  
    if (input == "/quit") break;
    else if (input == "check") check(chisai);
    else if (input == "work") work(chisai, 5);
    else if (input == "talk" || input == "chat") talk();
    else if (input == "/help") help();
    else std::cout << "Error, command does not exist\n";
  }
  
  return 0;
}
