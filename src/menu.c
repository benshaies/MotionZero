#include "menu.h"
#include "stdio.h"

Menu menuState;

bool isHovering(Rectangle rec){
    if(CheckCollisionPointRec(GetMousePosition(), rec)){
        return true;
    }
    else{
        return false;
    }
}

bool isClicked(Rectangle rec){
    if(isHovering(rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        return true;
    }
    else{
        return false;
    }
}

void buttonArrayInit(){
    for(int i = 0; i < BUTTON_NUM; i++){
        buttons[i].id = -1;
        buttons[i].rec = (Rectangle){0,0,0,0};
        buttons[i].isHovering = false;
        buttons[i].isClicked = false;
        buttons[i].active = false;
    }
}

void createButton(int id, Rectangle rec){
    for(int i = 0; i < BUTTON_NUM; i++){
        if(!buttons[i].active){
            buttons[i].id = id;
            buttons[i].rec = rec;
            buttons[i].isClicked = false;
            buttons[i].isHovering = false;
            buttons[i].active = true;
            buttons[i].color = BLACK;

            break;
        }
    }
}

void menuInit(){
    menuState = MAIN_MENU;
    buttonArrayInit();

    createButton(1, (Rectangle){200, 500, 200, 100});
    createButton(2, (Rectangle){600, 500, 200, 100});

}

int updateMenu(){
    for(int i = 0; i < BUTTON_NUM; i++){
        if(buttons[i].active){

            if(isHovering(buttons[i].rec)){
                buttons[i].color = ORANGE;
            }
            else{
                buttons[i].color = BLACK;
            }

            if(isClicked(buttons[i].rec)){
                return buttons[i].id;
                break;
            }
        }
    }
}

void drawMenu(){

    switch (menuState){
        case MAIN_MENU:
            DrawText("Motion Zero", 275, 200, 75, RED);

            for(int i = 0; i < BUTTON_NUM; i++){
                if(buttons[i].active){
                    DrawRectangleRec(buttons[i].rec, buttons[i].color);

                    if(buttons[i].id == 1){
                        DrawText("1", buttons[i].rec.x + buttons[i].rec.width/2, buttons[i].rec.y + buttons[i].rec.height/2, 35, WHITE);
                    }
                    else if (buttons[i].id == 2){
                        DrawText("2", buttons[i].rec.x + buttons[i].rec.width/2, buttons[i].rec.y + buttons[i].rec.height/2, 35, WHITE);
                    }
                    
                }
            }
            break;
    }
    

}