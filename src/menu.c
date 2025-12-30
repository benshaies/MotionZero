#include "menu.h"
#include "stdio.h"

Menu menuState;

Animation mainMenuAnimation, howToPlayAnimation;


void menuInit(){
    menuState = MAIN_MENU;
    
    animationInit(&mainMenuAnimation, 0, mainMenuTexture, 1000, 9, 0, 0);
    animationInit(&howToPlayAnimation, 0, howToPlayTexture, 1000, 4, 0, 0);

}

int updateMenu(){
    
    switch (menuState){
        case MAIN_MENU:
            if(IsKeyPressed(KEY_ENTER)){
                menuState = LEVEL_SELECTION;
            }
            else if(IsKeyPressed(KEY_TAB)){
                menuState = GUIDE_SCREEN;
            }
            return 0;
            break;
        case GUIDE_SCREEN:

            if(IsKeyPressed(KEY_TAB)){
                menuState = MAIN_MENU;
            }
            return 0;
            break;

        case START_PRESSED:

        case LEVEL_SELECTION:
            if(IsKeyPressed(KEY_J)){
                return 1;
            }
            else if(IsKeyPressed(KEY_K)){
                return 2;
            }

            break;
        
    }
}

void drawMenu(){

    switch(menuState){
        case MAIN_MENU:
            playAnimation(&mainMenuAnimation, (Rectangle){0,0,1000,1000}, 1, 0.1);
            playAnimation(&player.sideAnim, (Rectangle){450, 850, 100, 100}, 1, 0.25);
            break;
        case GUIDE_SCREEN:
            playAnimation(&howToPlayAnimation, (Rectangle){0,0, 1000, 1000}, 1, 0.25);
            break;

        case START_PRESSED:

        case LEVEL_SELECTION:
            DrawText("Level One - PRESS J", 300, 300, 50, BLACK);
            DrawText("Level Two - PRESS K", 300, 600, 50, BLACK);

    }
    

}