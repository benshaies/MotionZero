#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "level.h"

    typedef struct{
        Vector2 pos;
        Rectangle rec;
        
        Vector2 direction;
        float speed;

        bool isMoving;

        Vector2 leftPoint, rightPoint, topPoint, downPoint;
    }Player;

    extern Player player;

    void playerInit(Vector2 starPos);

    void playerUpdate(Level *level);

    void playerMovement();

    void playerCollisions(Level *level);

    void drawPlayer();

    void resetPlayer(Level *level);
#endif