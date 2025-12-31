#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "animation.h"
#include "texture.h"
#include "player.h"
#include "level.h"
#include "gameState.h"

    #define BUTTON_NUM 10

    typedef enum{
        MAIN_MENU,
        GUIDE_SCREEN,
        LEVEL_SELECTION,
        START_PRESSED,
        GUIDE_SCREEN_PRESSED,
        
    }Menu;

    extern Menu menuState;


    bool rectangleIn();

    bool rectangleOut();

    int levelSelectionUpdate();

    void menuInit();

    int updateMenu();

    void drawMenu();
#endif