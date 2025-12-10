#include "gameState.h"
#include "stdio.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;

void gameInit(){

    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
    loadLevelEnemies(&levelOne);

    game.currentState = PLAYING;
    game.currentLevel = &levelOne;

    playerInit(game.currentLevel->startPos); 

    //Setup camera
    camera = (Camera2D){0};
    camera.target = player.pos;
    camera.offset = (Vector2){500, 500};
    camera.zoom = 1.0f; 
    
}

void gameUpdate(){
    switch (game.currentState){
        case MENU:
            
        case PLAYING:
            //Update camera target with player position
            camera.target = player.pos;
        
            updateEnemy(game.currentLevel);
            playerUpdate(game.currentLevel);
            break;
        case DEAD:
            resetPlayer(game.currentLevel);
            game.currentState = PLAYING;
            break;
        case PAUSED:
    }
}

void gameDraw(){

    switch (game.currentState){
        case MENU:
            ClearBackground(BLACK);
            break;
        case PLAYING:
            BeginMode2D(camera);

                drawLevel(game.currentLevel);

                drawPlayer();
                drawEnemy();
        
            EndMode2D();
            break;

        case DEAD:
            
            

        case PAUSED:

    }

}