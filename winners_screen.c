#include "raylib.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

static int nWinners = -1;

void updateWinners(){
    if(IsKeyPressed(KEY_ENTER))
        game.currentScreen = MENU;    
}

void drawWinners(){
    BeginDrawing();

        ClearBackground(RAYWHITE);
        int i = 0, j;
        float height = 0.27;
        float height2 = 0.27;
        if(nWinners){
            DrawRectangle(SCREEN_WIDTH*0.1, SCREEN_HEIGHT * 0.1, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.15, BLACK);
            DrawText(winners[0].name, SCREEN_WIDTH * 0.13, SCREEN_HEIGHT*0.1 + 20, 40, RED);
            DrawText(winners[0].score, SCREEN_WIDTH * 0.8, SCREEN_HEIGHT*0.1 + 20, 40, RED);
        }
        while(i < nWinners-1){
            DrawRectangle(SCREEN_WIDTH*0.1, SCREEN_HEIGHT * height, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.15, BLACK);
            height2 = 0.27;
            for(j = 1; j < nWinners; j++){
                DrawText(winners[j].name, SCREEN_WIDTH * 0.13, SCREEN_HEIGHT*height2 + 20, 40, RED);
                DrawText(winners[j].score, SCREEN_WIDTH * 0.8, SCREEN_HEIGHT*height2 + 20, 40, RED);
                height2 += 0.17;
            }
            i++;
            height += 0.17;
        }
    DrawText("SCORE BOARD",
        SCREEN_WIDTH/2 - MeasureText("SCORE BOARD", 35)/2,
        SCREEN_HEIGHT * 0.03,
        35,
        BLACK);

    DrawText("Press enter to go back to the menu",
        SCREEN_WIDTH/2 - MeasureText("Press enter to go back to the menu", 19)/2,
        SCREEN_HEIGHT * 0.95,
        19,
        GRAY);
    EndDrawing();    
}

void readWinners()
{
    nWinners = -1;
    FILE *fwinners = fopen("winners.bin", "rb");
    int i = 0;
    do{
        fread(winners[i].name, sizeof(strlen(name)), 1, fwinners);
        fread(winners[i].score, sizeof(strlen(score)), 1, fwinners);
        printf("%s\n", winners[i].name);
        i++;
        nWinners ++;
    }while(!feof(fwinners) && i <= MAX_HIGHSCORES);
    fclose(fwinners);
}