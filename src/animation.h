#ifndef ANIMATION_H
#define ANIMATION_H
#include <raylib.h>

    typedef struct{
        float timer;
        Texture2D texture;
        int size;
        int frameCount;
        int currentFrame;
        int direction;
        int yPos;
    }Animation;

    void animationInit(Animation *animation, float timer, Texture2D texture, int size, int frameCount, int currentFrame, 
     int yPos);

    void playAnimation(Animation *animation, Rectangle destination, int direction, float speed);
    
    void drawAnimationFrame(Animation *animation, Rectangle destination, int direction, int frameNum);

    bool playAnimationOnce(Animation *animation, Rectangle destination, int direction, float speed);

#endif