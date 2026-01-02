#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "level.h"
#include "gameState.h"
#include "texture.h"
#include "sound.h"

const int screenWidth = 1000;
const int screenHeight = 1000;

extern Rectangle rec;

typedef enum{
    TRANSITION_IN,
    TRANSITION_OUT,
}transState;

transState transitionState = 0;

void draw(){
    BeginDrawing();


    ClearBackground(BLACK);


    gameDraw();

    

    DrawRectangleRec(transitionRec, BLACK);

    EndDrawing();
}

int main(void){
    InitWindow(screenWidth, screenHeight, "MotionZero");  
    SetTargetFPS(60);

    gameInit();
    while (!WindowShouldClose()){

    
        draw(); 
            
        if(!game.isTransitioning){
            gameUpdate();
        }
        else{
            switch (transitionState){
                case 0:
                    if(transitionIn()){
                        transitionState = 1;
                        if(game.isGameStateChange){
                            game.currentState = game.nextStateGame;
                        }
                        else{
                            menuState = game.nextStateMenu;
                        }
                        game.isGameStateChange = NULL;
                    }
                    break;
                
                case 1:
                    if(transitionOut()){
                        transitionState = 0;
                        game.isTransitioning = false;
                    }
                    break;
            }
        }        
        

        
    }
    saveGame(&save);
    unloadSound();
    unloadTexture();
    CloseWindow();
    return 0;
}