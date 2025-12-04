#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "level.h"

    typedef enum{
        MENU,
        LEVELONE,
        LEVELTWO,
    }GameState;

    extern GameState currentState;

    void gameInit();

    void gameUpdate();

#endif