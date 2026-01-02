#include "gameState.h"
#include "stdio.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;

int deathFrameCount = 0;

Rectangle transitionRec = {-1000, 0, 1000, 1000};
bool isTransitioning = false;

saveData save;

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

bool transitionIn(int newState){
    isTransitioning = true;
    if(transitionRec.x < 0){
        transitionRec.x += 15;
        return false;
    }
    else{
        transitionRec.x = 0;
        return true;
    }
}

bool transitionOut(){
    if(transitionRec.x >= 0 && transitionRec.x < 1000){
        transitionRec.x += 15;
        return false;
    }
    else{
        transitionRec.x = -1000;
        isTransitioning = false;
        return true;
    }
}


void cameraUpdate(){
    
    Vector2 direction = {player.pos.x - player.oldPos.x, player.pos.y - player.oldPos.y};
    Vector2 cameraDirection = {player.hitbox.x + (direction.x * 45), player.hitbox.y + (direction.y * 45)};

    //Update camera target with player position
    camera.target = (Vector2){player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2};

   

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

    //Load menu
    menuInit();

    //Load Sounds
    loadSound();

    //Loads level one
    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
    //loadLevelEnemies(&levelOne);

    //Load level two
    levelInit(&levelTwo, 2);
    loadLevel(&levelTwo);


    game.currentState = MENU;
    game.currentLevel = &levelOne;

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
                case 0: // level selection
                    break;
                case 1: // Level One
                    loadLevelEnemies(&levelOne);
                    game.currentLevel = &levelOne;
                    game.currentState = RESPAWN;
                    break;
                case 2:  // level Two
                    loadLevelEnemies(&levelTwo);
                    game.currentLevel = &levelTwo;
                    game.currentState = RESPAWN;
                    break;
                case 3:
                    break;
            }
            break;
            
        case PLAYING:
            
            cameraUpdate();
            updateEnemy(game.currentLevel);
            playerUpdate(game.currentLevel);
            UpdateMusicStream(game.currentLevel->music);

            game.currentLevel->time += GetFrameTime();

            if(IsKeyPressed(KEY_TAB)){
                game.currentState = MENU;
                menuState = MENU;
            }
            break;
        case DEAD:
            deathFrameCount++;
            if(camera.zoom < 2.5f){
                camera.zoom += 0.05;
            }
            if (deathFrameCount >= 210){
                game.currentState = RESPAWN;
                deathFrameCount = 0;
                camera.zoom = 0.75;
            }
            game.currentLevel->time = 0.0f;
            break;
        case RESPAWN:
                game.currentState = PLAYING;
                resetPlayer(game.currentLevel);
                resetEnemies();
                loadLevelEnemies(game.currentLevel);
                game.currentLevel->time = 0.0f;

            break;
        case LEVEL_COMPLETE:
            save.bestTimes[game.currentLevel->num-1] = game.currentLevel->time;
            if(game.currentLevel->num != 3){
                save.hightestLevel++;
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
            DrawText(TextFormat("%d", save.deaths[game.currentLevel->num-1]), 0, 0, 50, WHITE);
            DrawText(TextFormat("%.0f", game.currentLevel->time),0, 75, 50, WHITE);
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

    }

}