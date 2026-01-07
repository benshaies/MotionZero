#include "texture.h"

Texture2D playerDownTexture, playerSideTexture, playerUpTexture, playerNotMovingTexture, playerDeathTexture, graveStoneTexture;

Texture2D levelTilesetTexture;

Texture2D enemyTilesetTexture;

Texture2D mainMenuTexture, howToPlayTexture, levelUITexture, levelCompleteTexture, bestRunsTexture;

void loadTexture(){
    playerDownTexture = LoadTexture("../assets/playerDown.png");
    playerSideTexture = LoadTexture("../assets/playerSide.png");
    playerUpTexture = LoadTexture("../assets/playerUp.png");
    playerNotMovingTexture = LoadTexture("../assets/playerNotMoving.png");
    playerDeathTexture = LoadTexture("../assets/playerDeath.png");
    graveStoneTexture = LoadTexture("../assets/graveStone.png");
    levelTilesetTexture = LoadTexture("../assets/levelTileset.png");
    enemyTilesetTexture = LoadTexture("../assets/enemyTilset.png");
    mainMenuTexture = LoadTexture("../assets/mainMenuSheet.png");
    howToPlayTexture = LoadTexture("../assets/howToPlay.png");
    levelUITexture = LoadTexture("../assets/levelUI.png");
    levelCompleteTexture = LoadTexture("../assets/levelComplete.png");
    bestRunsTexture = LoadTexture("../assets/bestRuns.png");


    SetTextureFilter(levelTilesetTexture, TEXTURE_FILTER_POINT);
    
}

void unloadTexture(){
    UnloadTexture(playerDownTexture);
    UnloadTexture(playerSideTexture);
    UnloadTexture(playerUpTexture);
    UnloadTexture(playerNotMovingTexture);
    UnloadTexture(playerDeathTexture);
    UnloadTexture(graveStoneTexture);
    UnloadTexture(levelTilesetTexture);
    UnloadTexture(enemyTilesetTexture);
    UnloadTexture(mainMenuTexture);
    UnloadTexture(howToPlayTexture);
    UnloadTexture(levelUITexture);
    UnloadTexture(levelCompleteTexture);
    UnloadTexture(bestRunsTexture);
}