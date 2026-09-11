#pragma once

// Foward declaration of the gameData class
class gameData;

// Function Declartion

// Random Numbers
int randomNumberRange(int a, int b);

// Baisc Game Stuff
void firstRun(gameData& player);
void talk();
void help();
void clearScreen();
void shop(gameData& player);
bool save(gameData& player);
bool load(gameData& player);
void giveItem(gameData& player);

// Images
void view(gameData& player);

// Story
void beachDay();
void storyMenu();
