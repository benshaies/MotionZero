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
        int bestDeaths[3];
        float bestTimes[3];
        int levelDeaths[3];
    }saveData;

    extern saveData save;
    
    extern Rectangle transitionRec;
    extern bool isTransitioning;

    typedef enum{
        MENU,
        PLAYING,
        DEAD,
        PAUSED,
        RESPAWN,
        LEVEL_COMPLETE,
    }GameState;

    typedef struct{
        GameState currentState;
        Level *currentLevel;

        bool isTransitioning;
        bool transOut;
        bool transIn;
        bool isGameStateChange;
        GameState nextStateGame;
        Menu nextStateMenu;
    }Game;
    
    extern Game game;

    bool transitionIn();

    bool transitionOut();

    int loadSave(saveData *save);

    void saveGame(saveData *save);

    void gameInit();

    void gameUpdate();

    void gameDraw();

#endif