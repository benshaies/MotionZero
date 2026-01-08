#include "gameState.h"
#include "stdio.h"
#include "math.h"

Game game;

Camera2D camera;

Level levelOne;
Level levelTwo;
Level levelThree;

int deathFrameCount = 0;

Rectangle transitionRec = {-1000, 0, 1000, 1000};

saveData save;

bool cameraReset = false;

Rectangle playerLevelCompleteRec = {-100, 900, 100, 100};

int walkingSoundFrames2 = 0;
bool walkingRight = false;
bool saveUpdated = false;


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

        save.bestDeaths[0] = -1;
        save.bestDeaths[1] = -1;
        save.bestDeaths[2] = -1;

        save.levelDeaths[0] = 0;
        save.levelDeaths[1] = 0;
        save.levelDeaths[2] = 0;

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

    levelInit(&levelThree, 3);
    loadLevel(&levelThree);


    game.currentState = MAIN_MENU;
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
                    StopMusicStream(game.currentLevel->music);

                    game.isTransitioning = true;
                    game.isGameStateChange = true;
                    game.nextStateGame = RESPAWN;
                    break;
                case 2:  // level Two
                    game.currentLevel = &levelTwo;
                    loadLevelEnemies(&levelTwo);
                    camera.zoom = 0.75;
                    StopMusicStream(game.currentLevel->music);
                
                    game.isTransitioning = true;
                    game.isGameStateChange = true;
                    game.nextStateGame = RESPAWN;
                    break;
                case 3:
                    game.currentLevel = &levelThree;
                    loadLevelEnemies(&levelThree);
                    camera.zoom = 0.75;
                    StopMusicStream(game.currentLevel->music);

                    game.isTransitioning = true;
                    game.isGameStateChange = true;
                    game.nextStateGame = RESPAWN;
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
            
            if(!saveUpdated){
                    //Saving best time
                if(save.bestTimes[game.currentLevel->num-1] != 0 ){
                    if(game.currentLevel->time < save.bestTimes[game.currentLevel->num-1]){
                        save.bestTimes[game.currentLevel->num-1] = game.currentLevel->time;
                    }
                }
                else{
                    save.bestTimes[game.currentLevel->num-1] = game.currentLevel->time;
                }


                //Updating highest level
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

                //Saving level deaths
                if(save.bestDeaths[game.currentLevel->num-1] == -1){
                    save.bestDeaths[game.currentLevel->num-1] = save.levelDeaths[game.currentLevel->num-1];
                }
                else{
                    if(save.levelDeaths[game.currentLevel->num-1] < save.bestDeaths[game.currentLevel->num-1]){
                        save.bestDeaths[game.currentLevel->num-1] = save.levelDeaths[game.currentLevel->num-1];
                        
                    }
                }
                saveUpdated = true;
            }
            

            if(playerLevelCompleteRec.x < 450){
                playerLevelCompleteRec.x += 5;
                PlaySound(victorySound);

                walkingSoundFrames2++;
                if(walkingSoundFrames2 >= 15){
                    SetSoundVolume(walking, 0.12);
                    PlaySound(walking);
                    walkingSoundFrames2 = 0;
                }

            }
            else{
                if(IsKeyPressed(KEY_ENTER)){
                    PlaySound(clickSound);
                    walkingRight = true;
                }

                if(walkingRight){
                    playerLevelCompleteRec.x += 5;

                    walkingSoundFrames2++;
                    if(walkingSoundFrames2 >= 15){
                        SetSoundVolume(walking, 0.12);
                        PlaySound(walking);
                        walkingSoundFrames2 = 0;
                    }

                    if(playerLevelCompleteRec.x > 1000){
                        game.isTransitioning = true;
                        game.isGameStateChange = true;
                        game.nextStateGame = MENU;
                        menuState = LEVEL_SELECTION;
                        walkingRight = false;
                        playerLevelCompleteRec = (Rectangle){-100, 900, 100, 100};
                        saveUpdated = false;
                        save.levelDeaths[game.currentLevel->num-1] = 0;
                    }
                }
            }


            // game.currentState = MENU;
            // menuState = MENU;
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
            DrawText(TextFormat("%d", save.levelDeaths[game.currentLevel->num-1]), 95, 17.5, 40, WHITE);
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
            ClearBackground(BLACK);

            if(playerLevelCompleteRec.x >= 450){
                DrawTexturePro(levelCompleteTexture, (Rectangle){0,0, 1000, 1000}, (Rectangle){0,0,1000,1000}, (Vector2){0,0}, 0.0, WHITE);
                DrawText(TextFormat("%.0f", game.currentLevel->time), 550, 440, 60, RED); 
                DrawText(TextFormat("%d", save.levelDeaths[game.currentLevel->num-1]), 625, 600, 60, RED);
            }

            playAnimation(&player.sideAnim, playerLevelCompleteRec, 1, 0.15);

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