#include "raylib.h"
#include "raymath.h"
#include "physac.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include "play_screen.h"

void callGame()
{
    game.currentScreen = PLAY;
    game.gameTime = GetTime();
    game.buffer = 0;
    game.pause = 0;
    game.create_new = GetTime();
    
    player.alive = 1;
    player.r = INITIAL_RADIUS;
    player.poisoned = 0;
    player.v = 2.5;
    
    alive_enemies = INITIAL_ENEMIES;
    int i;    
    
    for(i=0;i<alive_enemies;i++){
        createEnemy(i);
    }    
    
}

void loadGame()
{
    game.currentScreen = PLAY;
    FILE *file;
    if(!(file = fopen("meu_agario.bin", "rb"))){
        DrawText("There is no saved game!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 25, WHITE);
    } else {
        fread(&game, sizeof(GAME), 1, file);
        fread(&player, sizeof(PLAYER), 1, file);
        fread(&alive_enemies, sizeof(int),1, file);
        fread(enemies, sizeof(ENEMY), alive_enemies, file);
        fclose(file);
    }
}

void TitleDraw()
{
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Agario", SCREEN_WIDTH/2 - MeasureText("Agario", 80)/2, SCREEN_HEIGHT * 0.06, 80,  GREEN); 
        
        DrawText(((menuSelected == 0) ? "- Play-" : "Jogar"), // O que é desenhado (ver condicionais ternários)
            SCREEN_WIDTH/2 - MeasureText(((menuSelected == 0) ? "- Play-" : "Jogar"), 40)/2, //Posição x do texto
            SCREEN_HEIGHT * 0.26, //posição y do texto
            40, //tamanho do texto
            (menuSelected == 0) ? BLUE : WHITE); //cor em que o texto vai estar
        DrawText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 
            SCREEN_WIDTH/2 - MeasureText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 40)/2, 
            SCREEN_HEIGHT * 0.38, 
            40, 
            (menuSelected == 1) ? BLUE : WHITE);
        DrawText(((menuSelected == 2) ? "- Instructions -" : "Instructions"), 
            SCREEN_WIDTH/2 - MeasureText(((menuSelected == 2) ? "- Instructions -" : "Instructions"), 40)/2, 
            SCREEN_HEIGHT * 0.52, 
            40, 
            (menuSelected == 2) ? BLUE : WHITE);
        DrawText(((menuSelected == 3) ? "- Load Game -" : "Load Game"), 
            SCREEN_WIDTH/2 - MeasureText(((menuSelected == 3) ? "- Load Game -" : "Load Game"), 40)/2, 
            SCREEN_HEIGHT * 0.66, 
            40, 
            (menuSelected == 3) ? BLUE : WHITE);
        DrawText(((menuSelected == 4) ? "- Leave -" : "Leave"), 
            SCREEN_WIDTH/2 - MeasureText(((menuSelected == 4) ? "- Leave -" : "Leave"), 40)/2, 
            SCREEN_HEIGHT * 0.80, 
            40, 
            (menuSelected == 4) ? RED : WHITE);        

        //Instruções do menu
        DrawText("-SPACE- select    -W- up  -S- down", 
            SCREEN_WIDTH/2 - MeasureText("-SPACE- select    -W- up  -S- down", 20)/2, 
            SCREEN_HEIGHT * 0.90, 20, WHITE);
        
        // Créditos
        DrawText("[Created by - João Pedro Ourique and Rodrigo Bervig - INF UFRGS]",
            SCREEN_WIDTH/2 - MeasureText("[Created by - João Pedro Ourique and Rodrigo Bervig - INF UFRGS]", 15)/2,
            SCREEN_HEIGHT * 0.95,
            17,
            WHITE);
        
        EndDrawing();
    }

void TitleUpdate()
{

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed('S')){
            menuSelected = (menuSelected + 1) % 5;
            
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressed('W')){
        menuSelected = (menuSelected == 0)? menuSelected = 4 : --menuSelected; 

    }
    if (IsKeyPressed(KEY_ENTER)){
        switch (menuSelected){
            case 0: { //PLAY
                callGame();
            } break;
            case 1: {
                game.currentScreen = WINNERS;
            } break;
            case 2: {
                game.currentScreen = INSTRUCTIONS;
            } break;
            case 3: {
                loadGame();
            } break;
            case 4: {                    
                CloseWindow();
            } break;
        }
    }
}