#include "bullet.h"
#include "player.h"
#include "raymath.h"

int bulletCapacity = 5;


void bulletInit(Bullets bullet[], Vector2 enemyPos){
    for(int i = 0; i < bulletCapacity; i++){
        if(!bullet[i].active){
            bullet[i].active = true;
            bullet[i].pos = enemyPos;
            bullet[i].radius = 5;  
            bullet[i].speed = 10.0f;
            bullet[i].direction = (Vector2){player.pos.x - enemyPos.x, player.pos.y - enemyPos.y};
            bullet[i].direction = Vector2Normalize(bullet[i].direction);
            
            break;
        }
    }
}

void deleteBullet(Bullets bullet[], int i){
    bullet[i].active = false;
    bullet[i].pos = (Vector2){0};
    bullet[i].radius = 0.0f;
    bullet[i].speed = 0.0f;
    bullet[i].direction = (Vector2){0};
}

void bulletUpdate(Bullets bullet[], float speed, Level *level){
    for(int i = 0; i < bulletCapacity; i++){
        if(bullet[i].active){
            bullet[i].pos.x += bullet[i].direction.x * speed;
            bullet[i].pos.y += bullet[i].direction.y * speed;

            //Loop through level rectangles 
            //If all the bullet isnt in any of the rectnagles, deletes it
            int collisionCheckNum = 0;
            for(int j = 0; j < level->RecNum; j++){
                if(!(CheckCollisionCircleRec(bullet[i].pos, bullet[i].radius, level->rec[j]))){
                    collisionCheckNum++;

                    if(collisionCheckNum == level->RecNum){
                        deleteBullet(bullet, i);
                    }

                }
            }
            
            
        }
        
    }
}

void drawBullet(Bullets bullet[]){
    for (int i = 0; i < bulletCapacity; i++){
        if(bullet[i].active){
            DrawCircleV(bullet[i].pos, 10, RED);
        }
    }
}





