#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "animation.h"
#include "texture.h"
#include "player.h"

    #define BUTTON_NUM 10

    typedef enum{
        MAIN_MENU,
        GUIDE_SCREEN,
        START_PRESSED,
        LEVEL_SELECTION,
    }Menu;

    extern Menu menuState;

    void menuInit();

    int updateMenu();

    void drawMenu();
#endif