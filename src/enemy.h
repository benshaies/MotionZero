#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "bullet.h"

#define ENEMY_NUM 20

    typedef struct{
        Vector2 pos;
        int type;
        bool active;
        Rectangle rec;
        Bullets bullets[20];
        float bulletDelay;
        float bulletTimer;
    }Enemy;

    extern Enemy enemy[ENEMY_NUM];

    void enemyInit(Vector2 pos, int type);

    void enemyFire(int i);

    void updateEnemy();

    void drawEnemy();
#endif