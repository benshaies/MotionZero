#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "level.h"
#include "player.h"
#include "raylib.h"
#include "enemy.h"
#include "texture.h"
#include "menu.h"
#include "sound.h"
#include "stdio.h"

    typedef struct{
        int hightestLevel;
        float deaths[3];
        float bestTimes[3];
    }saveData;

    extern saveData save;

    typedef enum{
        MENU,
        PLAYING,
        DEAD,
        PAUSED,
        RESPAWN,
    }GameState;

    typedef struct{
        GameState currentState;
        Level *currentLevel;
    }Game;
    
    extern Game game;

    int loadSave(saveData *save);

    void saveGame(saveData *save);

    void gameInit();

    void gameUpdate();

    void gameDraw();

#endif