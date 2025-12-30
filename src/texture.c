#include "texture.h"

Texture2D playerDownTexture, playerSideTexture, playerUpTexture, playerNotMovingTexture, playerDeathTexture, graveStoneTexture;

Texture2D levelTilesetTexture;

Texture2D enemyTilesetTexture;

Texture2D mainMenuTexture, howToPlayTexture;

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
}