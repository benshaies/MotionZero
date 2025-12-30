#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "level.h"
#include "animation.h"

    typedef enum{
        PLAYER_DEATHANIM,
        GRAVESTONE_ANIM,
        GRAVETSTONE_IDLE,
    }State;

    typedef struct{
        Vector2 pos;
        Vector2 oldPos;
        Rectangle rec;
        Rectangle hitbox;
        
        Vector2 direction;
        float speed;

        bool isMoving;

        Vector2 leftPoint, rightPoint, topPoint, downPoint;

        Animation downAnim, sideAnim, upAnim, notMovingAnim;
        Animation deathAnim, graveStoneAnim;
        bool playDownAnim, playSideAnim, playUpAnim;

        State animState;

        //Sound variables
        Sound deathSound[3];


    }Player;

    extern Player player;

    void playerInit(Vector2 starPos);

    void playerUpdate(Level *level);

    void playerMovement();

    void playerCollisions(Level *level);

    void drawPlayer();

    void resetPlayer(Level *level);

    void drawPlayerDeath();
#endif