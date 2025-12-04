#include "level.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *fileName;

void levelInit(Level *level, int levelNum){
    level->num = levelNum;
    switch (levelNum){
        case 1:
            level->width = 32;
            level->height = 54;
            break;
    }

    level->array = malloc(level->height * sizeof(int*));
    for(int i = 0; i < level->height; i++){
        level->array[i] = malloc(level->width * sizeof(int));
    }
}

void loadLevel(Level *level){

}

void drawLevel(Level *level){
        for(int y = 0; y < level->height; y++){
            for(int x = 0; x < level->width; x++){
                printf("%d\n", level->array[y][x]);
            }
        }
}