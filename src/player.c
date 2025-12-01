#include "player.h"
#include "raymath.h"
#include  "stdio.h"

Player player;

void playerInit(){
    player.pos = (Vector2){500, 500};
    player.rec = (Rectangle){player.pos.x, player.pos.y, 50, 50};
    player.direction = (Vector2){0,0};
    player.speed = 5.0f;

    player.isMoving = false;
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

}

void drawPlayer(){
    DrawRectangleRec(player.rec, BLUE);
}