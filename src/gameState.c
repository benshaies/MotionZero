#include "gameState.h"
#include "stdio.h"

GameState currentState = LEVELONE;

Camera2D camera;

Level levelOne;

void gameInit(){
    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
    loadLevelEnemies(&levelOne);

    playerInit(levelOne.startPos);

    //Setup camera
    camera = (Camera2D){0};
    camera.target = player.pos;
    camera.offset = (Vector2){500, 500};
    camera.zoom = 1.0f;
    
}

void gameUpdate(){
    //Update camera target with player position
    camera.target = player.pos;
    
    updateEnemy(&levelOne);
    playerUpdate();
}

void gameDraw(){

    BeginMode2D(camera);

        drawLevel(&levelOne);

        drawPlayer();
        drawEnemy();
    
    EndMode2D();
}