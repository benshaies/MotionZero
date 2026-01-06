#ifndef SOUND_H
#define SOUND_H
#include "raylib.h"

    extern Sound walking, mediumShoot, sniperShoot, slowShoot, death, transitionSwipe;
    extern Music levelOneMusic, levelTwoMusic, mainMenuMusic, levelSelectionMusic;

    void loadSound();

    void unloadSound();


#endif