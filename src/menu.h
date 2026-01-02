#ifndef MENU_H
#define MENU_H
#include "raylib.h"


    #define BUTTON_NUM 10

    typedef enum{
        MAIN_MENU,
        GUIDE_SCREEN,
        LEVEL_SELECTION,
        START_PRESSED,
        GUIDE_SCREEN_PRESSED,
        LEVEL_COMPLETED,
    }Menu;

    extern Menu menuState;


    int levelSelectionUpdate();

    void menuInit();

    int updateMenu();

    void drawMenu();
#endif