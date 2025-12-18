#include "bullet.h"
#include "player.h"
#include "raymath.h"

int bulletCapacity = 10;


void bulletInit(Bullets bullet[], Vector2 enemyPos){
    for(int i = 0; i < bulletCapacity; i++){
        if(!bullet[i].active){
            bullet[i].active = true;
            bullet[i].pos = (Vector2){enemyPos.x + 37.5, enemyPos.y + 37.5};
            bullet[i].radius = 7.5;  
            bullet[i].direction = (Vector2){player.hitbox.x + player.hitbox.width/2 - enemyPos.x, player.hitbox.y + player.hitbox.height/2 - enemyPos.y};
            bullet[i].direction = Vector2Normalize(bullet[i].direction);
            
            break;
        }
    }
}

void deleteBullet(Bullets bullet[], int i){
    bullet[i].active = false;
    bullet[i].pos = (Vector2){0};
    bullet[i].radius = 0.0f;
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
            DrawCircleV(bullet[i].pos, bullet[i].radius, RED);
        }
    }
}

void resetBullets(Bullets bullet[]){
    for (int i = 0; i < bulletCapacity; i++){
        bullet[i].active = false;
        bullet[i].pos = (Vector2){0,0};
        bullet[i].radius = 0;
        bullet[i].direction = (Vector2){0,0};
    }
}





