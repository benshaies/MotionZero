#include "gameState.h"
#include "stdio.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;

int deathFrameCount = 0;

void gameInit(){

    loadTexture();

    //Load menu
    menuInit();

    //Loads level one
    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
    //loadLevelEnemies(&levelOne);

    //Load level two
    levelInit(&levelTwo, 2);
    loadLevel(&levelTwo);


    game.currentState = MENU;
    game.currentLevel = &levelTwo;

    playerInit(game.currentLevel->startPos); 

    //Setup camera
    camera = (Camera2D){0};
    camera.target = player.pos;
    camera.offset = (Vector2){500, 500};
    camera.zoom = 0.75f; 
    
}

void gameUpdate(){
    switch (game.currentState){
        case MENU:
            switch (updateMenu()){
                case 1:
                    loadLevelEnemies(&levelOne);
                    game.currentLevel = &levelOne;
                    game.currentState = RESPAWN;
                    break;
                case 2:
                    loadLevelEnemies(&levelTwo);
                    game.currentLevel = &levelTwo;
                    game.currentState = RESPAWN;
                    break;
            }
            break;
            
        case PLAYING:
            //Update camera target with player position
            camera.target = (Vector2){player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2};
        
            updateEnemy(game.currentLevel);
            playerUpdate(game.currentLevel);

            if(IsKeyPressed(KEY_SPACE)){
                game.currentState = MENU;
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
                camera.zoom = 0.75;
            }
            break;
        case RESPAWN:

            game.currentState = PLAYING;
            resetPlayer(game.currentLevel);
            resetEnemies();
            loadLevelEnemies(game.currentLevel);
            break;
        case PAUSED:
    }
}

void gameDraw(){

    switch (game.currentState){
        case MENU:
            ClearBackground(WHITE);
            drawMenu();
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