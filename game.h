#pragma once
#include <string>

class Player{
  public:
    int points = 0;
    bool alive = true;
    bool kissing = false;
    bool invincible = false;
    bool win = false;
};

bool gameRun(std::string name, int winScore);
