#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "bullet.h"

    typedef struct{
        Vector2 pos;
        int type;
        bool alive;
        Rectangle rec;
        Bullets bullets[20];
    }Enemy;

    extern Enemy enemy;

    void enemyInit();

    void enemyFire();

    void updateEnemy();

    void drawEnemy();
#endif