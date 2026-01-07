#include "sound.h"

Sound walking, mediumShoot, sniperShoot, slowShoot, death, transitionSwipe, victorySound, clickSound;
Music levelOneMusic, levelTwoMusic, mainMenuMusic, levelSelectionMusic;



void loadSound(){
    InitAudioDevice();
    
    walking = LoadSound("../sound/walking.wav");
    mediumShoot = LoadSound("../sound/mediumShoot.wav");
    slowShoot = LoadSound("../sound/slowShoot.wav");
    sniperShoot = LoadSound("../sound/snipperShoot.wav");
    death = LoadSound("../sound/dead.wav");
    transitionSwipe = LoadSound("../sound/transitionSwipe.mp3");
    victorySound = LoadSound("../sound/victory.mp3");
    clickSound = LoadSound("../sound/click.wav");


    levelOneMusic = LoadMusicStream("../sound/level1.wav");
    levelTwoMusic = LoadMusicStream("../sound/level2.wav");
    mainMenuMusic = LoadMusicStream("../sound/mainMenu.mp3");
    levelSelectionMusic = LoadMusicStream("../sound/levelSelection.ogg");
}

    

void unloadSound(){
    UnloadSound(walking);
    UnloadSound(mediumShoot);
    UnloadSound(slowShoot);
    UnloadSound(sniperShoot);
    UnloadSound(death);
    UnloadSound(transitionSwipe);
    UnloadSound(victorySound);
    UnloadSound(clickSound);


    UnloadMusicStream(levelOneMusic);
    UnloadMusicStream(levelTwoMusic);
    UnloadMusicStream(mainMenuMusic);
    UnloadMusicStream(levelSelectionMusic);
    CloseAudioDevice();
}