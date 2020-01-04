#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "globals.h"
#include "instructions_screen.h"
#include "play_screen.h"
#include "menu.h"
#include "winners_screen.h"
#include "final_screen.h"

void updateScreen();

int main(){
     
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AGARIO.C");
    
    game.currentScreen = MENU; //the game starts with Menu screen.
    readWinners();
    
    SetTargetFPS(60); // set game to 60 fps
    
    // Main loop game
    while (!WindowShouldClose()) // Execute game while player does not press Esc
    {                
        updateScreen();        
    }

    CloseWindow();
    return 0;
}

void updateScreen(){
    switch(game.currentScreen){
        case(MENU):
        {
            TitleDraw();
            TitleUpdate();
        } break;
        case(INSTRUCTIONS):
        {
            drawInstructions();
            updateInstructions();
        } break;
        case(WINNERS):
        {
            drawWinners();
            updateWinners();
        } break;
        case(PLAY):
        {   
            updateScreen();
            drawGame();
        } break;
        case(FINAL):
        {
            drawFinal();
        } break;
    }   
}
