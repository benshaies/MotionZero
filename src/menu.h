#ifndef MENU_H
#define MENU_H
#include "raylib.h"

    #define BUTTON_NUM 10

    typedef enum{
        MAIN_MENU,
        LEVEL_SELECTION,
    }Menu;

    typedef struct{
        char id;
        Rectangle rec;
        bool isHovering;
        bool isClicked;
        bool active;
        Texture2D texture;
        Color color;
    }Button;

    static Button buttons[BUTTON_NUM];

    extern Menu menuState;

    void buttonArrayInit();

    void createButton(int id, Rectangle rec);

    void menuInit();

    int updateMenu();

    void drawMenu();
#endif