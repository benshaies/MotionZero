#include "menu.h"
#include "stdio.h"
#include "animation.h"
#include "texture.h"
#include "player.h"
#include "level.h"
#include "gameState.h"


Menu menuState;

Animation mainMenuAnimation, howToPlayAnimation;

Rectangle playerAnimationRec;

Level levelSelection;

Camera2D camera1;

int levelSelectionGates[3];





int levelSelectionUpdate(){

    if(save.hightestLevel == 1){
        
    }
    else if(save.hightestLevel == 2){
        levelSelection.array[0][levelSelectionGates[1]] = 6;
    }
    else if(save.hightestLevel == 3){
        levelSelection.array[0][levelSelectionGates[1]] = 6;
        levelSelection.array[0][levelSelectionGates[2]] = 6;
    }

    if(CheckCollisionRecs(player.rec, (Rectangle){levelSelectionGates[0] * TILE_SIZE, -100, TILE_SIZE, TILE_SIZE})){
            return 1;
    }
    else if(CheckCollisionRecs(player.rec, (Rectangle){levelSelectionGates[1] * TILE_SIZE, -100, TILE_SIZE, TILE_SIZE}) && (save.hightestLevel == 2 || save.hightestLevel == 3) ){
            return 2;
    }
    else if(CheckCollisionRecs(player.rec, (Rectangle){levelSelectionGates[2] * TILE_SIZE, -100, TILE_SIZE, TILE_SIZE}) && save.hightestLevel == 3){
            return 3;
    }




    
}


void menuInit(){

    playerAnimationRec = (Rectangle){467.5, 850, 75, 75};

    levelSelectionGates[0] = 3;
    levelSelectionGates[1] = 8;
    levelSelectionGates[2] = 13;

    menuState = MAIN_MENU;
    
    animationInit(&mainMenuAnimation, 0, mainMenuTexture, 1000, 9, 0, 0);
    animationInit(&howToPlayAnimation, 0, howToPlayTexture, 1000, 4, 0, 0);

    levelInit(&levelSelection, 0);
    loadLevel(&levelSelection);

    //Main menu music
    PlayMusicStream(mainMenuMusic);
    SetMusicVolume(mainMenuMusic, 0.5);



    camera1 = (Camera2D){0};
    camera1.target = player.pos;
    camera1.offset = (Vector2){500, 500};
    camera1.zoom = 0.75f; 

}

int updateMenu(){
    
    switch (menuState){
        

        case MAIN_MENU:
            playerAnimationRec.y = 850;
            if(IsKeyPressed(KEY_ENTER)){
                menuState = START_PRESSED;
                
            }
            else if(IsKeyPressed(KEY_TAB)){
                
                game.isTransitioning = true;
                game.isGameStateChange = false;
                game.nextStateMenu = GUIDE_SCREEN;

                PauseMusicStream(mainMenuMusic);
                
            }
            ResumeMusicStream(mainMenuMusic);
            UpdateMusicStream(mainMenuMusic);
            
            return -1;
            break;
        case GUIDE_SCREEN:
            ResumeMusicStream(mainMenuMusic);
            UpdateMusicStream(mainMenuMusic);

            if(IsKeyPressed(KEY_TAB)){
                game.isTransitioning = true;
                game.isGameStateChange = false;
                game.nextStateMenu = MAIN_MENU;

                PauseMusicStream(mainMenuMusic);
            }
            return -1;
            break;

        case LEVEL_SELECTION:
            camera1.target = player.pos;
            

            playerUpdate(&levelSelection);
            UpdateMusicStream(levelSelectionMusic);

            if(player.pos.y >= 800){
                game.isTransitioning = true;
                game.isGameStateChange = false;
                game.nextStateMenu = MAIN_MENU;
            }
            
            
            return levelSelectionUpdate();
            break;

        case START_PRESSED:
            UpdateMusicStream(mainMenuMusic);
            if(playerAnimationRec.y > 500){
                playerAnimationRec.y -= 2;
                
            }
            else{
                PauseMusicStream(mainMenuMusic);
                PlayMusicStream(levelSelectionMusic);
                SetMusicVolume(levelSelectionMusic, 0.6);

                resetPlayer(&levelSelection);
                game.isTransitioning = true;
                game.isGameStateChange = false;
                game.nextStateMenu = LEVEL_SELECTION;
                camera1.target = player.pos;
                if(!game.isTransitioning){
                    playerAnimationRec = (Rectangle){467.5, 850, 75, 75};
                }
                
            }



            return -1;
            break;

        case GUIDE_SCREEN_PRESSED:

                menuState = GUIDE_SCREEN;

            return -1;
            break;

       
        
        
        
    }
}

void drawMenu(){

    switch(menuState){
        case MAIN_MENU:
            playAnimation(&mainMenuAnimation, (Rectangle){0,0,1000,1000}, 1, 0.1);
            if(playerAnimationRec.y == 850){
                playAnimation(&player.sideAnim, playerAnimationRec, 1, 0.25);
            }
            
            break;
        case GUIDE_SCREEN:
            playAnimation(&howToPlayAnimation, (Rectangle){0,0, 1000, 1000}, 1, 0.25);
            break;
        
        case LEVEL_SELECTION:
            BeginMode2D(camera1);
                ClearBackground(BLACK);
                drawLevel(&levelSelection);
                drawPlayer();
            EndMode2D();
            break;

        case START_PRESSED:
            playAnimation(&mainMenuAnimation, (Rectangle){0,0,1000,1000}, 1, 0.1);
            if(playerAnimationRec.y > 725){
                playAnimation(&player.upAnim, playerAnimationRec, 1, 0.25);
            }
            break;
        
        case GUIDE_SCREEN_PRESSED:
            playAnimation(&mainMenuAnimation, (Rectangle){0,0,1000,1000}, 1, 0.1);
            playAnimation(&player.sideAnim, playerAnimationRec, 1, 0.25);

            break;

        
    

    }


    DrawRectangleRec(transitionRec, BLACK);

}