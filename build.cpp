#include <cstdlib>
#include <iostream>
#include <ostream>

using std::system;

int apple(){
  int temp = system("brew install raylib");
  return temp;
}
int arch(){
  int temp = system("sudo pacman -S base-devel raylib");
  return temp;
}
int fedora(){
  int temp = system("sudo dnf install raylib");
  if (temp == 0) system("sudo dnf groupinstall 'Development Tools'");
  return temp;
}
int deb(){
  int temp = system("sudo apt install build-essential");
  if (temp == 0) system("sudo apt install raylib");
  return temp;
}

int main(){
  std::cout << "Starting build..." << std::endl;

  int temp;

  temp = apple();

  if (temp == 1) temp = arch();

  if (temp == 1) temp = fedora();

  if (temp == 1) temp = deb();

  if (temp == 1){
    std::cerr << "IKD what the fuck you running, good luck!" << std::endl;
    return 1;
  }

  int build  = system("g++ main.cpp game.cpp functions.cpp player.cpp image.cpp -o main.exe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11");

  if (build == 0){
    std::cout << "Program compiled successfully!" << std::endl;
  }
  else{
    std::cerr << "Program failed to build, please ensure you have g++ installed";
    return 1;
  }

  return 0;
}
