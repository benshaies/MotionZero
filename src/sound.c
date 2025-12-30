#include "sound.h"

Sound walking, mediumShoot, sniperShoot, slowShoot, death[3];
Music levelOneMusic, levelTwoMusic;



void loadSound(){
    InitAudioDevice();
    
    walking = LoadSound("../sound/walking.wav");
    mediumShoot = LoadSound("../sound/mediumShoot.wav");
    slowShoot = LoadSound("../sound/slowShoot.wav");
    sniperShoot = LoadSound("../sound/snipperShoot.wav");
    death[0] = LoadSound("../sound/deathOne.mp3");
    death[1] = LoadSound("../sound/deathTwo.mp3");
    death[2] = LoadSound("../sound/deathThree.mp3");


    levelOneMusic = LoadMusicStream("../sound/level1.wav");
    levelTwoMusic = LoadMusicStream("../sound/level2.wav");
}

    

void unloadSound(){
    UnloadSound(walking);
    UnloadSound(mediumShoot);
    UnloadSound(slowShoot);
    UnloadSound(sniperShoot);
    UnloadSound(death[0]);
    UnloadSound(death[1]);
    UnloadSound(death[2]);


    UnloadMusicStream(levelOneMusic);
    UnloadMusicStream(levelTwoMusic);
    CloseAudioDevice();
}