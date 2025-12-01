#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

    typedef struct{
        Vector2 pos;
        Rectangle rec;
        
        Vector2 direction;
        float speed;

        bool isMoving;
    }Player;

    extern Player player;

    void playerInit();

    void playerMovement();

    void drawPlayer();

#endif