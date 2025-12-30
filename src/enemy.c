#include "enemy.h"
#include "player.h"
#include "math.h"
#include "texture.h"
#include "sound.h"

Enemy enemy[ENEMY_NUM];

void enemyInit(Vector2 pos, int type){

    for(int i = 0; i < ENEMY_NUM; i++){
        if(!enemy[i].active){
            enemy[i].active = true;
            enemy[i].pos = pos;
            enemy[i].type = type;
            enemy[i].rec = (Rectangle){pos.x, pos.y, 100, 100};

            switch (type){
                case 56: //Normal Medium
                    enemy[i].enemyColor = YELLOW;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 1.5;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 10;
                    enemy[i].bulletSlowSpeed = 2.5;

                    animationInit(&enemy[i].anim, 0, enemyTilesetTexture, 16, 4, 0, 0);

                    enemy[i].fireSound = mediumShoot;
                    SetSoundVolume(enemy[i].fireSound, 0.25);

                    break;
                case 57: // Sniper
                    enemy[i].enemyColor = RED;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 4;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 17.5;
                    enemy[i].bulletSlowSpeed = 6;

                    animationInit(&enemy[i].anim, 0, enemyTilesetTexture, 16, 4, 0, 16);

                    enemy[i].fireSound = sniperShoot;
                    SetSoundVolume(enemy[i].fireSound, 0.25);
                    break;
                case 58: //Slow but a lot
                    enemy[i].enemyColor = PURPLE;

                    enemy[i].bullets[bulletCapacity];
                    enemy[i].bulletDelay = 0.75;
                    enemy[i].bulletTimer = GetTime();
                    enemy[i].bulletNormalSpeed = 8.5;
                    enemy[i].bulletSlowSpeed = 1;

                    animationInit(&enemy[i].anim, 0, enemyTilesetTexture, 16, 4, 0, 32);

                    enemy[i].fireSound = slowShoot;
                    SetSoundVolume(enemy[i].fireSound, 0.25);
                    break;
                }
            
            break;
        }
    }
    

}

void enemyFire(int i){

    if(enemy[i].active){

        if(fabs(enemy[i].pos.x - player.pos.x) <= 1250 && fabs(enemy[i].pos.y - player.pos.y) <= 1250){
            if(GetTime() - enemy[i].bulletTimer >= enemy[i].bulletDelay){
                PlaySound(enemy[i].fireSound);
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
        drawBullet(enemy[i].bullets, enemy[i].enemyColor);

        if(enemy[i].active){
            if(enemy[i].type == 56 || enemy[i].type == 57  || enemy[i].type == 58){
                playAnimation(&enemy[i].anim, enemy[i].rec, 1, player.isMoving ? 0.25 : 0.5);
            }
            
        }
    }
    
}

void resetEnemies(){
    for(int i = 0; i < ENEMY_NUM; i++){
        resetBullets(enemy[i].bullets);
        enemy[i].bulletTimer = 0;
        enemy[i].active = false;
        enemy[i].pos = (Vector2){0,0};
        enemy[i].type = -1;
        enemy[i].rec = (Rectangle){0,0,0,0};
    }
}