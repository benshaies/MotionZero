#include "enemy.h"
#include "player.h"

Enemy enemy;

void enemyInit(){
    enemy.alive = true;
    enemy.pos = (Vector2){100, 100};
    enemy.type = 1;
    enemy.rec = (Rectangle){100, 100, 75, 75};
    enemy.bullets[bulletCapacity];
}

void enemyFire(){
    if(IsKeyPressed(KEY_SPACE)){
        bulletInit(enemy.bullets, enemy.pos);
    }
}


void updateEnemy(){

    bulletUpdate(enemy.bullets, player.isMoving ? 10 : 2.5);
    
    enemyFire();
}

void drawEnemy(){
    if(enemy.alive){
        DrawRectangleRec(enemy.rec, BLACK);
    }

    drawBullet(enemy.bullets);
}