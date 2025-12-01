#include "bullet.h"
#include "player.h"
#include "raymath.h"

int bulletCapacity = 10;


void bulletInit(Bullets bullet[], Vector2 enemyPos){
    for(int i = 0; i < bulletCapacity; i++){
        if(!bullet[i].active){
            bullet[i].active = true;
            bullet[i].pos = enemyPos;
            bullet[i].radius = 5;  
            bullet[i].speed = 10.0f;
            bullet[i].delay = 0;
            bullet[i].timer = 0;
            bullet[i].direction = (Vector2){player.pos.x - enemyPos.x, player.pos.y - enemyPos.y};
            bullet[i].direction = Vector2Normalize(bullet[i].direction);
            
            break;
        }
    }
}

void bulletUpdate(Bullets bullet[], float speed){
    for(int i = 0; i < bulletCapacity; i++){
        if(bullet[i].active){
            bullet[i].pos.x += bullet[i].direction.x * speed;
            bullet[i].pos.y += bullet[i].direction.y * speed;
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





