#include "player.h"
#include "raymath.h"
#include "stdio.h"
#include "enemy.h"
#include "gameState.h"
#include "texture.h"

Player player;

bool isMovingRight;

void playerInit(Vector2 startPos)
{
    player.pos = startPos;
    player.rec = (Rectangle){player.pos.x, player.pos.y, 75, 75};
    player.hitbox = (Rectangle){player.pos.x+20, player.pos.y+20, player.rec.width/2, player.rec.height/2};
    player.direction = (Vector2){0, 0};
    player.speed = 5.0f;
    player.isMoving = false;

    animationInit(&player.downAnim, 0, playerDownTexture, 16, 4, 0, 0);
    animationInit(&player.sideAnim, 0, playerSideTexture, 16, 4, 0, 0);
    animationInit(&player.upAnim, 0, playerUpTexture, 16, 4,0, 0);
    animationInit(&player.notMovingAnim, 0, playerNotMovingTexture, 16, 4, 0, 0);
    player.playDownAnim = false;
    player.playSideAnim = false;
    player.playUpAnim = true;

    animationInit(&player.deathAnim, 0, playerDeathTexture, 16, 10, 0, 0);
    animationInit(&player.graveStoneAnim, 0, graveStoneTexture, 16, 6, 0, 0);

    player.animState = PLAYER_DEATHANIM;
}

void playerUpdate(Level *level)
{

    

    playerMovement();

    playerCollisions(level);

    printf("x:%f y%f\n", player.pos.x, player.pos.y);
    if(IsKeyPressed(KEY_F)){
        player.pos = level->startPos;
    }
}

void playerMovement()
{
    if (IsKeyDown(KEY_W))
    {
        player.direction.y -= 1;
        player.playUpAnim = true;
        player.playDownAnim = false;
    }
    else if (IsKeyDown(KEY_S))
    {
        player.direction.y += 1;
        player.playDownAnim = true;
        player.playUpAnim = false;
    }

    if (IsKeyDown(KEY_D))
    {
        player.direction.x += 1;
        player.playSideAnim = true;
        isMovingRight = true;
    }
    else if (IsKeyDown(KEY_A))
    {
        player.direction.x -= 1;
        player.playSideAnim = true;
        isMovingRight = false;
    }

    // Update moving variable
    if (player.direction.x != 0 || player.direction.y != 0)
    {
        player.isMoving = true;
        
    }
    else
    {
        player.isMoving = false;
        player.playSideAnim = false;
        player.playDownAnim = false;
        player.playUpAnim = false;
    }

    player.direction = Vector2Normalize(player.direction);

    player.pos.x += player.direction.x * player.speed;
    player.pos.y += player.direction.y * player.speed;

    player.direction = (Vector2){0, 0};

    player.rec.x = player.pos.x;
    player.rec.y = player.pos.y;

    player.hitbox = (Rectangle){player.pos.x+20, player.pos.y+20, player.rec.width/2, player.rec.height/2};

    // Update player collision points
    player.leftPoint = (Vector2){player.rec.x, player.rec.y + player.rec.height / 2};
    player.rightPoint = (Vector2){player.rec.x + player.rec.width, player.rec.y + player.rec.height / 2};
    player.topPoint = (Vector2){player.rec.x + player.rec.width / 2, player.rec.y};
    player.downPoint = (Vector2){player.rec.x + player.rec.width / 2, player.rec.y + player.rec.height};
}

void playerCollisions(Level *level)
{

        if(game.currentState != DEAD){
        // Check player collision with walls
        for (int y = 0; y < level->height; y++)
        {
            for (int x = 0; x < level->width; x++)
            {
                if (isWallTile(level->array[y][x]))
                {
                    
                    Rectangle wallrec = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    if (CheckCollisionPointRec(player.leftPoint, wallrec))
                    {
                        player.pos.x = x * TILE_SIZE + TILE_SIZE + 1;
                    }
                    else if (CheckCollisionPointRec(player.rightPoint, wallrec))
                    {
                        player.pos.x = (x * TILE_SIZE) - player.rec.width - 1;
                    }

                    if (CheckCollisionPointRec(player.topPoint, wallrec))
                    {
                        player.pos.y = (y * TILE_SIZE) + TILE_SIZE + 1;
                    }
                    else if (CheckCollisionPointRec(player.downPoint, wallrec))
                    {
                        player.pos.y = (y * TILE_SIZE) - player.rec.height - 1;
                    }
                }
            }
        }   
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        // Enemy active check
        if (enemy[i].active)
        {
            // If active, loop through active enemy bullets
            for (int j = 0; j < bulletCapacity; j++)
            {
                if (enemy[i].bullets[j].active)
                {
                    if (CheckCollisionCircleRec(enemy[i].bullets[j].pos, enemy[i].bullets[j].radius, player.hitbox))
                    {
                        deleteBullet(enemy[i].bullets, i);
                        game.currentState = DEAD;
                        return;
                        break;
                    }
                }
            }
        }
    }


    
}

void drawPlayer()
{   

    if(player.playSideAnim){
        playAnimation(&player.sideAnim, player.rec, isMovingRight ? 1 : -1, 0.15f);
    }
    else if(player.playUpAnim){
        playAnimation(&player.upAnim, player.rec, isMovingRight ? 1 : -1, 0.15f);
    }
    else if(player.playDownAnim){
        playAnimation(&player.downAnim, player.rec, isMovingRight ? 1 : -1, 0.15f);
    }
    else if(!player.isMoving){
        playAnimation(&player.notMovingAnim, player.rec, 1, 0.15f);
    }


    
}

void resetPlayer(Level *level)
{
    player.pos = level->startPos;
    player.rec.x = level->startPos.x;
    player.rec.y = level->startPos.y;
    player.direction = (Vector2){0, 0};
    player.isMoving = false;
    player.animState = PLAYER_DEATHANIM;
}

void drawPlayerDeath(){

    switch(player.animState){
        case PLAYER_DEATHANIM:
            if(playAnimationOnce(&player.deathAnim, player.rec, 1, 0.15f)){
                player.animState = GRAVESTONE_ANIM;
                
            }
            break;
        case GRAVESTONE_ANIM:
            if(playAnimationOnce(&player.graveStoneAnim, player.rec, 1, 0.15f)){
                player.animState = GRAVETSTONE_IDLE;
            }
            break;
            
        case GRAVETSTONE_IDLE:
            drawAnimationFrame(&player.graveStoneAnim, player.rec, 1, player.graveStoneAnim.frameCount);
            break;
    }
}