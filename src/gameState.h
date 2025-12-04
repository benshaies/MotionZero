#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "level.h"
#include "player.h"
#include "raylib.h"
#include "enemy.h"


    typedef enum{
        MENU,
        LEVELONE,
        LEVELTWO,
    }GameState;

    extern GameState currentState;

    void gameInit();

    void gameUpdate();

    void gameDraw();

#endif