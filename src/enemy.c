#include "enemy.h"
#include "player.h"

Enemy enemy[ENEMY_NUM];

void enemyInit(Vector2 pos, int type){

    for(int i = 0; i < ENEMY_NUM; i++){
        if(!enemy[i].active){
            enemy[i].active = true;
            enemy[i].pos = pos;
            enemy[i].type = type;
            enemy[i].rec = (Rectangle){pos.x, pos.y, 75, 75};

            enemy[i].bullets[bulletCapacity];
            enemy[i].bulletDelay = type ;
            enemy[i].bulletTimer = GetTime();
            
            break;
        }
    }
    

}

void enemyFire(int i){

    if(enemy[i].active){
        if(GetTime() - enemy[i].bulletTimer >= enemy[i].bulletDelay){
            bulletInit(enemy[i].bullets, enemy[i].pos);
            enemy[i].bulletTimer = GetTime();
        }
    }
        

    
}


void updateEnemy(){

    for(int i = 0; i < ENEMY_NUM; i++){
        bulletUpdate(enemy[i].bullets, player.isMoving ? 10 : 2.5);
    
        enemyFire(i);
        
    }
}

void drawEnemy(){

    for(int i = 0; i < ENEMY_NUM; i++){
        drawBullet(enemy[i].bullets);

        if(enemy[i].active){
            DrawRectangleRec(enemy[i].rec, BLACK);
        }
    }
    

    
}