#include "image.h"
#include <string>
#include "raylib.h"

void showImage(std::string image, int windowX, int windowY){

  SetTraceLogLevel(LOG_NONE);

  InitWindow(windowX, windowY, "Yuki Kazue");
  
  Texture2D picture = LoadTexture(image.c_str());

  int posX = (windowX - picture.width) / 2;
  int posY = (windowY - picture.height) / 2;

  while (!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(WHITE);
      DrawTexture(picture, posX, posY, WHITE);
    EndDrawing();
  }

  UnloadTexture(picture);
  CloseWindow();
}
