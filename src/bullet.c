#include "bullet.h"
#include "player.h"
#include "raymath.h"
#include "stdio.h"

int bulletCapacity = 20;


void bulletInit(Bullets bullet[], Vector2 enemyPos){
    for(int i = 0; i < bulletCapacity; i++){
        if(!bullet[i].active){
            bullet[i].active = true;
            bullet[i].pos = (Vector2){enemyPos.x + 37.5, enemyPos.y + 37.5};
            bullet[i].radius = 7.5;  

            Vector2 direction = {player.pos.x - player.oldPos.x, player.pos.y - player.oldPos.y};
            Vector2 aimDirection = {player.hitbox.x + GetRandomValue(-10, 10) + (direction.x * 45), player.hitbox.y + GetRandomValue(-10,10) + (direction.y * 45)};
            printf("x:%f y:%f\n", direction.x, direction.y);
            bullet[i].direction = (Vector2){aimDirection.x - enemyPos.x, aimDirection.y - enemyPos.y};
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

            //Store previos position
            bullet[i].previousPreviousPos = (Vector2){bullet[i].pos.x - (bullet[i].direction.x * speed), bullet[i].pos.y - (bullet[i].direction.y * speed) };
            bullet[i].previousPos = bullet[i].pos;

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

void drawBullet(Bullets bullet[], Color bulletColor){
    for (int i = 0; i < bulletCapacity; i++){
        if(bullet[i].active){

            if(player.isMoving){
                DrawCircleV(bullet[i].previousPreviousPos, bullet[i].radius,  Fade(bulletColor, 0.25));
                DrawCircleV(bullet[i].previousPos, bullet[i].radius,  Fade(bulletColor, 0.5) );
            }
            else{
                DrawCircleV(bullet[i].pos, bullet[i].radius + 4, Fade(SKYBLUE, 0.75));
                
                Vector2 firstTrail = {bullet[i].pos.x - (bullet[i].direction.x * 8), bullet[i].pos.y - (bullet[i].direction.y * 8)};
                DrawCircleV(firstTrail, bullet[i].radius,  Fade(bulletColor, 0.5));
               
            }


            DrawCircleV(bullet[i].pos, bullet[i].radius, bulletColor);
            
        }
    }
}

void resetBullets(Bullets bullet[]){
    for (int i = 0; i < bulletCapacity; i++){
        bullet[i].active = false;
        bullet[i].pos = (Vector2){0,0};
        bullet[i].radius = 0;
        bullet[i].direction = (Vector2){0,0};
        bullet[i].previousPos = (Vector2){0,0};
    }
}





