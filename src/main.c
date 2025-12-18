#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "level.h"
#include "gameState.h"
#include "texture.h"

const int screenWidth = 1000;
const int screenHeight = 1000;

void draw(){
    BeginDrawing();

    ClearBackground(BLACK);

    gameDraw();

    EndDrawing();
}

int main(void){
    InitWindow(screenWidth, screenHeight, "MotionZero");  
    SetTargetFPS(60);

    gameInit();
    while (!WindowShouldClose()){
        gameUpdate();

        draw(); 
    }
    unloadTexture();
    CloseWindow();
    return 0;
}