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
#include <fstream>

// Classes

class gameData{
  public:
    // Data
    int romance; // The total romance level that the user has with Yuki
    int money; // How much money the user has
    int first_run = 0; // Used to check if it is the first run
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

    bool inventoryItemCheck(std::string item){

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
};

// Functions

int randomNumberRange(int a, int b){
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen);
}

void firstRun(gameData& player) {
  #if _WIN32
    std::system("winget install -e --id mpv.net");
  #elif defined(__APPLE__)
    std::system("brew install mpv");
  #else
    #if IS_ARCH
      std::system("sudo pacman -S mpv");
    #elif defined (IS_FEDORA)
      std::system("sudo dnf install mpv");
    #elif defined (IS_UBUNTU)
      std::system("sudo apt install mpv");
    #endif
  #endif

  player.first_run = 1;
}
  
void talk(){
  std::vector<std::string> responses = {"Hrmph, It's not like i enjoy seeing you or anything...", "Here eat some of this, I accidently made to much...", "It's not like I like you or anything!"};

  int index = randomNumberRange(0, 2);

  std::cout << "Yuki: " << responses[index] << "\n";
}

void help(){
  std::vector<std::string> commands = {"talk", "chat", "work", "check", "save", "story", "/quit", "/help", "/clear"};

  std::cout << "Valid commands:\n";

  for (std::string i : commands){
    std::cout << i << '\n';
  }
}

void clearScreen(){
  // Checks if it is windows at compile time
  #if _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
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

bool save(gameData& player){

  std::ofstream file("saves/save.txt");

  if (file.is_open()){
    file << player.romance << std::endl;
    file << player.money << std::endl;
    file << player.first_run << std::endl;
  }
  else{
    std::cerr << "Error, IDK what is wrong here bro, you're cooked lol ¯\\_₍⸍⸌̣ʷ̣̫⸍̣⸌₎_/¯";
    return false;
  }
  
  file.close();

  std::ofstream file2("saves/inventory.txt");

  if (file2.is_open()){
    for (std::string i : player.inventory){
      file2 << i << std::endl;
    }
  }
  else{
    std::cerr << "Error, IDK bro you fucked this up somehow, you're cooked lol ¯\\_₍⸍⸌̣ʷ̣̫⸍̣⸌₎_/¯";
    return false;
  }
  
  file2.close();

  return true;
}

bool load(gameData& player){


  std::ifstream file("saves/save.txt");

  if (file.is_open()){

    std::vector<int> vec;

    int a;

    while (file >> a){
      vec.push_back(a);
    }

    player.romance = vec[0];
    player.money = vec[1];
    player.first_run = vec[2];
  }
  else{
    std::cerr << "Error, save file ('save.txt') not found or is empty. Please ensure it exists and contains two numbers seperated by a newline.";
    return false;
  }
  
  file.close();

  std::ifstream file2("saves/inventory.txt");

  if (file2.is_open()) {

    std::string b;

    while (file2 >> b){
      player.inventory.push_back(b);
    }
  }
  else{
    std::cerr << "Error, save file ('inventory.txt') not found, please ensure it is in the saves folder.";
    return false;
  }
  
  file2.close();

  return true;
}

void giveItem(gameData& player){

  std::string choice;

  while (true){

    std::cout << "GiveMenu> ";

    std::cin >> choice;

    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if (choice == "/help"){
      std::cout << "Current commands:\nGive\n/quit\n/quit\n";
    }
    else if (choice == "/quit"){
      break;
    }
    else if (choice == "give"){

      std::string item;
      
      while (true){
        std::cout << "GiveItem> ";

        std::cin >> item;

        transform(item.begin(), item.end(), item.begin(), ::tolower);

        if (item == "/help") std::cout << "Current commands:\ncake\ngift\nring\n/quit\n/help\n";
        else if (item == "/quit") break;
        // Cake
        else if (item == "cake" && player.inventoryItemCheck("cake") == true){
          player.romance += 5;
          player.inventoryRemove("cake");
          std::cout << "Yuki: Is this for me? *Blushes* I'll take it, but only because its rude not to!\n";
        }
        // Gift
        else if (item == "gift" && player.inventoryItemCheck("gift") == true){
          player.romance += 15;
          player.inventoryRemove("gift");
          std::cout << "Yuki: A gift? What are you stupid it's not my birthday you know! *Looks down to hide her blush* You better have not spent to much on this baka~!\n";
        }
        // Ring
        else if (item == "ring" && player.inventoryItemCheck("ring") == true){
          player.romance += 30;
          player.inventoryRemove("ring");
          std::cout << "Yuki: A ring? What are you implying? This is the nicest thing anybody has ever done for me... I'm going to put it on my left ring finger...\n" << "You: Isn't that the finger to the heart? What are you implying\n" << "Yuki: It's not like I like you or anything, Baka~!\n";
        }
        else std::cout << "Error, you either dont own the specified item or you have entered an invalid command. Type /help for commands and /quit to exit this menu.\n";
      }
    }
  }
}

// View Image

void view(){
  int i = randomNumberRange(0, 7);
  std::vector<std::string> vec = {"yuki.png", "yuki_angry.png", "yuki_clingy.png", "yuki_embarrassed.png", "yuki_happy.png", "yuki_jealous.png", "yuki_soft.png", "yuki_surprised.png"};
  std::string command = "mpv images/";
  command += vec[i];
  std::system(command.c_str());
}

// Story

void beachDay(){
  std::ifstream file("story/beach.txt");

  if (file.is_open()){
    std::string line;
    int count = 0;
    while (getline(file, line)){
      if (count == 5){
        std::string choice;
        std::cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        if (choice == "no" || choice == "n"){
          break;
        }
        count = 0;
      }
      else std::cout << line << '\n';
      count += 1;
    }
  }
  else{
    std::cerr << "Error, story file not found ('story/beach.txt'). Please insure the story directory exists and there are the storys inside it\n";
  }
}

void storyMenu(){
  std::vector<std::string> vec = {"beach_day"};

  while (true){
    std::cout << "What would you like to do?: ";

    std::string choice;
  
    std::cin >> choice;

    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if (choice == "/quit") break;
    else if (choice == "/help"){
      std::cout << "Commands for story menu: /quit, /help, beach\n";
    }
    else if (choice == "beach_day" || choice == "beach day" || choice == "beach") beachDay();
    else std::cout << "Error, command not found\n";
  }
}

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
    else if (input == "view") view();
    else std::cout << "Error, command does not exist\n\n";
  }
  return 0;
}

