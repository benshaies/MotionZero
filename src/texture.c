#include "texture.h"

Texture2D playerDownTexture, playerSideTexture, playerUpTexture, playerNotMovingTexture, playerDeathTexture, graveStoneTexture;

void loadTexture(){
    playerDownTexture = LoadTexture("../assets/playerDown.png");
    playerSideTexture = LoadTexture("../assets/playerSide.png");
    playerUpTexture = LoadTexture("../assets/playerUp.png");
    playerNotMovingTexture = LoadTexture("../assets/playerNotMoving.png");
    playerDeathTexture = LoadTexture("../assets/playerDeath.png");
    graveStoneTexture = LoadTexture("../assets/graveStone.png");
}

void unloadTexture(){
    UnloadTexture(playerDownTexture);
    UnloadTexture(playerSideTexture);
    UnloadTexture(playerUpTexture);
    UnloadTexture(playerNotMovingTexture);
    UnloadTexture(playerDeathTexture);
    UnloadTexture(graveStoneTexture);
}