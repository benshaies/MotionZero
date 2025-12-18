#ifndef TEXTURE_H
#define TEXTURE_H
#include "raylib.h"

    extern Texture2D playerDownTexture;
    extern Texture2D playerSideTexture;
    extern Texture2D playerUpTexture;
    extern Texture2D playerNotMovingTexture;
    extern Texture2D playerDeathTexture;
    extern Texture2D graveStoneTexture;
    
    extern Texture2D levelTilesetTexture;

    void loadTexture();

    void unloadTexture();

#endif