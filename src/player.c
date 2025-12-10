#include "player.h"
#include "raymath.h"
#include  "stdio.h"
#include "enemy.h"
#include "gameState.h"

Player player;

void playerInit(Vector2 startPos){
    player.pos = startPos;
    player.rec = (Rectangle){player.pos.x, player.pos.y, 50, 50};
    player.direction = (Vector2){0,0};
    player.speed = 5.0f;
    player.isMoving = false;
}

void playerUpdate(Level *level){

    playerCollisions(level);

    playerMovement();
}

void playerMovement(){  
    if(IsKeyDown(KEY_W)){
        player.direction.y -= 1;
    }
    else if(IsKeyDown(KEY_S)){
        player.direction.y += 1;
    }

    if(IsKeyDown(KEY_D)){
        player.direction.x += 1;
    }
    else if(IsKeyDown(KEY_A)){
        player.direction.x -= 1;
    }

    //Update moving variable
    if(player.direction.x != 0 || player.direction.y != 0){
        player.isMoving = true;
    }
    else{
        player.isMoving = false;
    }

    player.direction = Vector2Normalize(player.direction);

    player.pos.x += player.direction.x * player.speed;
    player.pos.y += player.direction.y * player.speed;

    player.direction = (Vector2){0,0};

    player.rec.x = player.pos.x;
    player.rec.y = player.pos.y;

    //Update player collision points
    player.leftPoint = (Vector2){player.rec.x, player.rec.y+player.rec.height/2};
    player.rightPoint = (Vector2){player.rec.x + player.rec.width, player.rec.y + player.rec.height/2};
    player.topPoint = (Vector2){player.rec.x + player.rec.width/2, player.rec.y};
    player.downPoint = (Vector2){player.rec.x + player.rec.width/2, player.rec.y + player.rec.height};

}

void playerCollisions(Level *level){

    for(int i = 0; i < ENEMY_NUM; i++){
        //Enemy active check
        if(enemy[i].active){
            //If active, loop through active enemy bullets
            for(int j = 0; j < bulletCapacity; j++){
                if(enemy[i].bullets[j].active){
                    if(CheckCollisionCircleRec(enemy[i].bullets[j].pos, enemy[i].bullets[j].radius, player.rec)){
                        game.currentState = DEAD;                  
                    }
                }
            }
        }
    }

    //Check player collision with walls
    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            if(level->array[y][x] == 4){
                Rectangle wallrec = {x*TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                if(CheckCollisionPointRec(player.leftPoint, wallrec)){
                    player.pos.x = x * TILE_SIZE + TILE_SIZE + 1;
                }
                else if(CheckCollisionPointRec(player.rightPoint, wallrec)){
                    player.pos.x = (x * TILE_SIZE) - player.rec.width - 1;
                }
                
                if(CheckCollisionPointRec(player.topPoint, wallrec)){
                    player.pos.y = (y * TILE_SIZE) + TILE_SIZE + 1;
                }
                else if(CheckCollisionPointRec(player.downPoint, wallrec)){
                    player.pos.y = (y * TILE_SIZE) - player.rec.height - 1;
                }
            }
        }
    }
}

void drawPlayer(){
    DrawRectangleRec(player.rec, BLACK);
}

void resetPlayer(Level *level){
    player.pos = level->startPos;
    player.rec.x = level->startPos.x;
    player.rec.y = level->startPos.y;
    player.direction = (Vector2){0,0};
    player.isMoving = false;
}