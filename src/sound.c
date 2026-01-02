#include "sound.h"

Sound walking, mediumShoot, sniperShoot, slowShoot, death;
Music levelOneMusic, levelTwoMusic;



void loadSound(){
    InitAudioDevice();
    
    walking = LoadSound("../sound/walking.wav");
    mediumShoot = LoadSound("../sound/mediumShoot.wav");
    slowShoot = LoadSound("../sound/slowShoot.wav");
    sniperShoot = LoadSound("../sound/snipperShoot.wav");
    death = LoadSound("../sound/death.wav");


    levelOneMusic = LoadMusicStream("../sound/level1.wav");
    levelTwoMusic = LoadMusicStream("../sound/level2.wav");
}

    

void unloadSound(){
    UnloadSound(walking);
    UnloadSound(mediumShoot);
    UnloadSound(slowShoot);
    UnloadSound(sniperShoot);
    UnloadSound(death);


    UnloadMusicStream(levelOneMusic);
    UnloadMusicStream(levelTwoMusic);
    CloseAudioDevice();
}