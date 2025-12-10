#include "enemy.h"
#include "player.h"
#include "math.h"

Enemy enemy[ENEMY_NUM];

void enemyInit(Vector2 pos, int type){

    for(int i = 0; i < ENEMY_NUM; i++){
        if(!enemy[i].active){
            enemy[i].active = true;
            enemy[i].pos = pos;
            enemy[i].type = type;
            enemy[i].rec = (Rectangle){pos.x, pos.y, 75, 75};

            switch (type){
                case 1: 
                    enemy[i].enemyColor = RED;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 2;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 8;
                    enemy[i].bulletSlowSpeed = 2.5;
                    break;
                case 2:
                    enemy[i].enemyColor = YELLOW;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 5;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 17.5;
                    enemy[i].bulletSlowSpeed = 6;
                    break;
                case 3:
                    enemy[i].enemyColor = BLUE;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 0.5;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 6;
                    enemy[i].bulletSlowSpeed = 1;
                    break;
                }
            
            break;
        }
    }
    

}

void enemyFire(int i){

    if(enemy[i].active){

        if(fabs(enemy[i].pos.x - player.pos.x) <= 750 || fabs(enemy[i].pos.y - player.pos.y) <= 750){
            if(GetTime() - enemy[i].bulletTimer >= enemy[i].bulletDelay){
                bulletInit(enemy[i].bullets, enemy[i].pos);
                enemy[i].bulletTimer = GetTime();
            }
        }
        
    }
        

    
}


void updateEnemy(Level *level){

    for(int i = 0; i < ENEMY_NUM; i++){
        bulletUpdate(enemy[i].bullets, player.isMoving ? enemy[i].bulletNormalSpeed : enemy[i].bulletSlowSpeed, level);
    
        enemyFire(i);
        
    }
}

void drawEnemy(){

    for(int i = 0; i < ENEMY_NUM; i++){
        drawBullet(enemy[i].bullets);

        if(enemy[i].active){
            DrawRectangleRec(enemy[i].rec, enemy[i].enemyColor);
        }
    }
    

    
}