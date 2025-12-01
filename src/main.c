#include "raylib.h"
#include "player.h"
#include "enemy.h"

const int screenWidth = 1000;
const int screenHeight = 1000;

void draw(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "MotionZero");  
    SetTargetFPS(60);

    playerInit();

    enemyInit();
}

void update(){
    playerMovement();
    updateEnemy();

    draw(); 
    drawPlayer();
    drawEnemy();
}

int main(void){

    init();
    while (!WindowShouldClose()){
        update();
    }

    CloseWindow();
    return 0;
}