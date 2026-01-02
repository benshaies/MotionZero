#ifndef LEVEL_H
#define LEVEL_H
#include "raylib.h"

    #define TILE_SIZE 100

    #define LEVEL_ONE_SIZE_X 32
    #define LEVEL_ONE_SIZE_Y 54

    typedef struct{
        int width;
        int height;
        int **array;
        int num;
        Vector2 startPos;
        Rectangle *rec;
        int RecNum;
        const char *filename;
        Music music;
        float musicVolume;

        float time;
    }Level;

    void loadLevel(Level *level);

    void levelInit(Level *level, int levelNum);

    void loadLevelEnemies(Level *level);

    void drawLevel(Level *level);

    bool isWallTile(int tileId);


#endif