#include "gameState.h"
#include "stdio.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;

int deathFrameCount = 0;

void gameInit(){

    loadTexture();

    //Loads level one
    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
    loadLevelEnemies(&levelOne);

    //Load level two



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
            camera.target = (Vector2){player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2};
        
            updateEnemy(game.currentLevel);
            playerUpdate(game.currentLevel);

            if(IsKeyPressed(KEY_SPACE)){
                game.currentState = DEAD;
            }

            break;
        case DEAD:
            deathFrameCount++;
            if(camera.zoom < 2.5f){
                camera.zoom += 0.05;
            }
            if (deathFrameCount >= 300){
                game.currentState = RESPAWN;
                deathFrameCount = 0;
                camera.zoom = 1.0;
            }
            break;
        case RESPAWN:

            game.currentState = PLAYING;
            resetPlayer(game.currentLevel);
            resetEnemies();
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
            BeginMode2D(camera);
            
                drawLevel(game.currentLevel);
                drawEnemy();
                drawPlayerDeath();
        
            EndMode2D();
            break;
        case RESPAWN:


        case PAUSED:

    }

}