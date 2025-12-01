#ifndef BULLET_H
#define BULLET_H
#include "raylib.h"

extern int bulletCapacity;

    typedef struct{
        bool active;
        Vector2 pos;
        float radius;
        float speed;
        float timer;
        float delay;
        Vector2 direction;
    }Bullets;



    void bulletInit(Bullets bullet[], Vector2 enemyPos);

    void bulletUpdate(Bullets bullet[], float speed);

    void fireBullet();

    void drawBullet(Bullets bullet[]);

#endif