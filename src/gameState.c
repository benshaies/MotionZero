#include "gameState.h"
#include "stdio.h"
#include "math.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;

int deathFrameCount = 0;

Rectangle transitionRec = {-1000, 0, 1000, 1000};

saveData save;

bool cameraReset = false;


int loadSave(saveData *save)
{
    FILE *file = fopen("save.dat", "rb");
    if (!file) return 0;  // no save yet

    size_t read = fread(save, sizeof(saveData), 1, file);
    fclose(file);

    return read == 1;
}

void saveGame(saveData *save)
{
    FILE *file = fopen("save.dat", "wb");
    if (!file) return;

    fwrite(save, sizeof(saveData), 1, file);
    fclose(file);
}

bool transitionIn(){
    if(transitionRec.x < 0){
        transitionRec.x += 50;
        return false;
    }
    else{
        transitionRec.x = 0;
        return true;
    }
}

bool transitionOut(){
    if(transitionRec.x >= 0 && transitionRec.x < 1000){
        transitionRec.x += 50;
        return false;
    }
    else{
        transitionRec.x = -1000;
        return true;
    }
}


void cameraUpdate(){
    
    Vector2 direction = {player.pos.x - player.oldPos.x, player.pos.y - player.oldPos.y};
    Vector2 cameraDirection = {player.hitbox.x + (direction.x * 45), player.hitbox.y + (direction.y * 45)};

    //Update camera target with player position
    camera.target = (Vector2){player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2};

    float zoom = camera.zoom;

    camera.target.x = roundf(camera.target.x * zoom) / zoom;
    camera.target.y = roundf(camera.target.y * zoom) / zoom;



    if(!player.isMoving){
        if(camera.zoom <= 0.90f){
            camera.zoom += 0.01f;
        }
    }
    else{
        if(camera.zoom > 0.75f){
            camera.zoom -= 0.01;
        }
    }
}

void gameInit(){

    if(!loadSave(&save)){
        save.hightestLevel = 1;
        save.deaths[0] = 0;
        save.deaths[1] = 0;
        save.deaths[2] = 0;

        save.bestTimes[0] = 0;
        save.bestTimes[1] = 0;
        save.bestTimes[2] = 0;

    }

    loadTexture();



    //Load Sounds
    loadSound();

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
    game.currentLevel = &levelOne;
    game.isTransitioning = false;
    game.transIn = false;
    game.transOut = false;

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
                case -1: // Still in menu stuff
                    break;
                case 1: // Level One

                    
                    game.currentLevel = &levelOne;
                    loadLevelEnemies(&levelOne);
                    camera.zoom = 0.75;

                    game.isTransitioning = true;
                    game.isGameStateChange = true;
                    game.nextStateGame = RESPAWN;
                    break;
                case 2:  // level Two
                    game.currentLevel = &levelTwo;
                    loadLevelEnemies(&levelTwo);
                    camera.zoom = 0.75;

                    game.isTransitioning = true;
                    game.isGameStateChange = true;
                    game.nextStateGame = RESPAWN;
                    break;
                case 3:
                    break;
            }
            break;
            
        case PLAYING:

            if(!cameraReset){
                camera.zoom = 0.75;
                cameraReset = true;
            }
            
            cameraUpdate();
            updateEnemy(game.currentLevel);
            playerUpdate(game.currentLevel);
            UpdateMusicStream(game.currentLevel->music);

            game.currentLevel->time += GetFrameTime();

            if(IsKeyPressed(KEY_TAB)){
                game.isTransitioning = true;
                game.isGameStateChange = true;
                game.nextStateGame = MENU;
                menuState = MAIN_MENU;
            }
            break;
        case DEAD:
            deathFrameCount++;
            if(camera.zoom < 2.5f){
                camera.zoom += 0.05;
            }
            if (deathFrameCount >= 210){
                deathFrameCount = 0;
                
                game.isTransitioning = true;
                game.isGameStateChange = true;
                game.nextStateGame = RESPAWN;
                cameraReset = false;
                
            }
            game.currentLevel->time = 0.0f;
            break;
        case RESPAWN:
                
                resetPlayer(game.currentLevel);
                resetEnemies();
                loadLevelEnemies(game.currentLevel);
                game.currentState = PLAYING;
                
                game.currentLevel->time = 0.0f;

            break;
        case LEVEL_COMPLETE:
            save.bestTimes[game.currentLevel->num-1] = game.currentLevel->time;
            switch(game.currentLevel->num){
                case 1:
                    save.hightestLevel = 2;
                    break;
                case 2:
                    save.hightestLevel = 3;
                    break;
                case 3:
                    break;
            }
            game.currentState = MENU;
            menuState = MENU;
            break;
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
            DrawTexturePro(levelUITexture, (Rectangle){0,0, 48, 32}, (Rectangle){10,10, 144, 96}, (Vector2){0,0}, 0.0, WHITE);
            DrawText(TextFormat("%d", save.deaths[game.currentLevel->num-1]), 95, 17.5, 40, WHITE);
            DrawText(TextFormat("%.0f", game.currentLevel->time),100, 65, 40, WHITE);
            break;

        case DEAD:
            BeginMode2D(camera);
            
                drawLevel(game.currentLevel);
                drawEnemy();
                drawPlayerDeath();
                
        
            EndMode2D();
            break;
        case LEVEL_COMPLETE:
            break;
        
        case RESPAWN:
            // BeginMode2D(camera);

                
 
            //     drawLevel(game.currentLevel);
            //     drawPlayer();
            //     drawEnemy();
                
            // EndMode2D();
            break;

    }

}