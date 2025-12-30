#ifndef SOUND_H
#define SOUND_H
#include "raylib.h"

    extern Sound walking, mediumShoot, sniperShoot, slowShoot, death[3];
    extern Music levelOneMusic, levelTwoMusic;

    void loadSound();

    void unloadSound();


#endif