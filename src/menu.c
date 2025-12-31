#include "menu.h"
#include "stdio.h"

Menu menuState;

Animation mainMenuAnimation, howToPlayAnimation;

Rectangle playerAnimationRec;
Rectangle transitionRec = {-1000,0, 1000, 1000};

Level levelSelection;

Camera2D camera1;




bool rectangleIn(){
    if(transitionRec.x < 0){
        transitionRec.x += 50;
        return false;
    }
    else {
        transitionRec.x = 0;
        return true;
    }


}

bool rectangleOut(){

    if(!(transitionRec.x <= -1000)){
        if(transitionRec.x >= 0 && transitionRec.x < 1000){
            transitionRec.x += 50;
            return false;
        }
        else if(transitionRec.x >= 1000){
            transitionRec.x = -1000;
            return true;
        }
    }

    
    
}


void menuInit(){

    playerAnimationRec = (Rectangle){467.5, 850, 75, 75};

    menuState = MAIN_MENU;
    
    animationInit(&mainMenuAnimation, 0, mainMenuTexture, 1000, 9, 0, 0);
    animationInit(&howToPlayAnimation, 0, howToPlayTexture, 1000, 4, 0, 0);

    levelInit(&levelSelection, 0);
    loadLevel(&levelSelection);

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
                menuState = GUIDE_SCREEN_PRESSED;
            }
            return -1;
            break;
        case GUIDE_SCREEN:
            rectangleOut();
            if(IsKeyPressed(KEY_TAB)){
                menuState = MAIN_MENU;
            }
            return -1;
            break;

        case LEVEL_SELECTION:
            rectangleOut();
            camera1.target = player.pos;
            if(IsKeyPressed(KEY_SPACE)){
                return 1;
            }

            playerUpdate(&levelSelection);
            
            

            break;

        case START_PRESSED:
            if(playerAnimationRec.y > 500){
                playerAnimationRec.y -= 2;
            }
            else{
                if(rectangleIn()){
                    resetPlayer(&levelSelection);
                    menuState = LEVEL_SELECTION;
                }
                
            }

            return -1;
            break;

        case GUIDE_SCREEN_PRESSED:
            if(rectangleIn()){
                menuState = GUIDE_SCREEN;
            }
            return -1;
            break;

       
        
        
        
    }
}

void drawMenu(){

    switch(menuState){
        case MAIN_MENU:
            playAnimation(&mainMenuAnimation, (Rectangle){0,0,1000,1000}, 1, 0.1);
            playAnimation(&player.sideAnim, playerAnimationRec, 1, 0.25);
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