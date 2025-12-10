#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "level.h"
#include "player.h"
#include "raylib.h"
#include "enemy.h"


    typedef enum{
        MENU,
        PLAYING,
        DEAD,
        PAUSED,
    }GameState;

    typedef struct{
        GameState currentState;
        Level *currentLevel;
    }Game;
    
    extern Game game;

    void gameInit();

    void gameUpdate();

    void gameDraw();

#endif