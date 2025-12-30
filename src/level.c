#include "level.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "enemy.h"
#include "texture.h"
#include "sound.h"
#include "player.h"

int wallTileIds[21] = {0, 1, 2, 3, 4, 5, 7,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

//Sets up level struct and allocated memory for array
void levelInit(Level *level, int levelNum){
    
    switch (levelNum){
        case 1:
            level->num = levelNum;
            level->width = 32;
            level->height = 54;
            level->startPos = (Vector2){4*TILE_SIZE, 51*TILE_SIZE};

            level->filename = "../levels/level1.csv";

            //Level rec init
            level->RecNum = 3;
            level->rec = malloc(sizeof(Rectangle) * level->RecNum);

            level->rec[0] = (Rectangle){100, 2300, 800, 3000};
            level->rec[1] = (Rectangle){900, 2300, 2200, 800};
            level->rec[2] = (Rectangle){2300, 100, 800, 2200};

            level->music = levelOneMusic;
            level->musicVolume = 0.05;

            break;
        
        case 2:
            level->num = levelNum;
            level->width = 73;
            level->height = 40;
            level->startPos = (Vector2){3 * TILE_SIZE, 5 * TILE_SIZE};

            level->filename = "../levels/level2.csv";

            level->RecNum = 5;
            level->rec = malloc(sizeof(Rectangle) * level->RecNum);

            level->rec[0] = (Rectangle){100, 100, 2087.5, 917};
            level->rec[1] = (Rectangle){1194, 987.5, 1000, 2908};
            level->rec[2] = (Rectangle){2162.5, 3094, 4054, 815.5};
            level->rec[3] = (Rectangle){5209, 96, 1000, 3037.5};
            level->rec[4] = (Rectangle){6209, 92, 1016, 921};

            level->music = levelTwoMusic;
            level->musicVolume = 0.02;

            break;
    }

    level->array = malloc(level->height * sizeof(int*));
    for(int i = 0; i < level->height; i++){
        level->array[i] = malloc(level->width * sizeof(int));
    }
}

//Loads struct array with csv level data
void loadLevel(Level *level){

    FILE *file = fopen(level->filename, "r");
    if(!file){
        printf("Failed to open %s\n", level->filename);
        return;
    }

    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            fscanf(file, "%d,", &level->array[y][x]);
        }
    }

    fclose(file);
    
}

//Takes level array and spawns in enemies (and starts playing music)
void loadLevelEnemies(Level *level){
    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            if(level->array[y][x] == 56 || level->array[y][x] == 57 || level->array[y][x] == 58){
                enemyInit((Vector2){x*TILE_SIZE, y*TILE_SIZE}, level->array[y][x]);
            }
        }
    }
    SetMusicVolume(level->music, level->musicVolume);
    PlayMusicStream(level->music);
}

//Draws level (and updates music stream)
void drawLevel(Level *level){
    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            
                        
            if(level->array[y][x] != -1 && level->array[y][x] != 56 && level->array[y][x] != 57 && level->array[y][x] != 58){
                Rectangle sourceRec = {(level->array[y][x] % 8) * 16, (level->array[y][x]/8) * 16, 16, 16};
                Rectangle destRec = {TILE_SIZE*x, TILE_SIZE*y, TILE_SIZE, TILE_SIZE};
                DrawTexturePro(levelTilesetTexture, sourceRec, destRec, (Vector2){0,0}, 0.0f, WHITE);
                //DrawRectangleLines(destRec.x, destRec.y, TILE_SIZE, TILE_SIZE, RED);
            }

            if(level->array[y][x] == 56 || level->array[y][x] == 57|| level->array[y][x] == 58){
                DrawTexturePro(levelTilesetTexture, (Rectangle){0, 16, 16, 16}, (Rectangle){TILE_SIZE*x, TILE_SIZE*y, TILE_SIZE, TILE_SIZE}, (Vector2){0,0}, 0.0f, WHITE);
            }
        
        }
    }

}

bool isWallTile(int tileId){
    bool wall;

    for(int i  = 0; i < 21; i++){
        if(tileId == wallTileIds[i]){
            wall = true;
            break;
        }
        else{
            wall = false;
        }
    }

    return wall;
}