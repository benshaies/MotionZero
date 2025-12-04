#include "gameState.h"
#include "stdio.h"

GameState currentState = LEVELONE;

Level levelOne;

void gameInit(){
    levelInit(&levelOne, 1);
    loadLevel(&levelOne);
}

void gameUpdate(){
    drawLevel(&levelOne);
}