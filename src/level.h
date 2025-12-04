#ifndef LEVEL_H
#define LEVEL_H

    #define LEVEL_ONE_SIZE_X 32
    #define LEVEL_ONE_SIZE_Y 54

    typedef struct{
        int width;
        int height;
        int **array;
        int num;
    }Level;

    void loadLevel(Level *level);

    void levelInit(Level *level, int levelNum);

    void drawLevel(Level *level);


#endif