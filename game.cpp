#include "game.h"
#include "raylib.h"
#include <string>

int waitCount = 60;
int lookingCount = 240;
int invincibleTimer = 180;
bool looking = false;

bool gameRun(std::string name, int winScore){
  Player player;

  SetTraceLogLevel(LOG_NONE);

  InitWindow(600, 600, name.c_str());
  
  Texture2D kiss = LoadTexture("images/yuki_kiss_no_bg.png");
  Texture2D noKiss = LoadTexture("images/yuki_post_kiss_no_bg.png");

  SetTargetFPS(60);
  
  while (!WindowShouldClose()){

    if (IsKeyPressed(KEY_C)){
      break;
    }
    
    while (player.alive > 0){

      if (IsKeyPressed(KEY_C)){
        UnloadTexture(kiss);
        UnloadTexture(noKiss);
        CloseWindow();
        return false;
      }
      
      if (IsKeyDown(KEY_SPACE)){
        player.kissing = true;
      }
      else player.kissing = false;

      if (lookingCount == 0){
        looking = true;
        lookingCount = 180;
      }
      else if (lookingCount > 120) lookingCount --;
      else{
        lookingCount --;
        looking = false;
      }
    
      if (player.kissing && waitCount > 0){
        waitCount --;
      }
      else waitCount = 50;

      if (player.kissing && !looking && waitCount == 0){
        player.points += 50;
        waitCount = 50;
      }

      if (looking && player.kissing){
        player.alive = false;
      }

      if (player.points == winScore){
        player.win = true;
      }

      if (player.win){
        break;
      }

      BeginDrawing();
        ClearBackground(WHITE);
          if (player.kissing){
            DrawTexture(kiss, 190, 300, WHITE);
          }
          else{
            DrawTexture(noKiss, 190, 300, WHITE);
          }
        DrawText(TextFormat("Score: %d", player.points), 50, 100, 15, BLACK);
        DrawText(TextFormat("Wait Count: %d", waitCount), 235, 100, 15, BLACK);
        DrawText(TextFormat("Looking: %d", looking), 450, 100, 15, BLACK);
      EndDrawing();
    }
    
    if (!player.alive){
      BeginDrawing();
        ClearBackground(RED);
        DrawText("YOU DIED!", 223, 235, 30, WHITE);
        DrawText("Press 'C' to quit", 235, 500, 15, WHITE);      
      EndDrawing();
    }
    else{
      BeginDrawing();
        ClearBackground(GREEN);
        DrawText("YOU WIN!", 223, 235, 30, WHITE);
        DrawText("Press 'C' to quit", 235, 500, 15, WHITE);
      EndDrawing();
    }
    
  }

  UnloadTexture(noKiss);
  UnloadTexture(kiss);
  CloseWindow();

  if (!player.alive) return false;

  return true;
}
