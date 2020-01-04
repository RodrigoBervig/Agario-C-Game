#include "raylib.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "winners_screen.h"

void increaseFramesCounter();
void DrawUserInput();
void saveHighScore(char* name);
void drawFinal();
void wipeStaticStrings(char* str);
int nWinners();
void overwriteLast();
void sortWinners(WINNER winners[]);
void swapG(WINNER *g1, WINNER *g2); 

static int qualifyAsHighScore = 0;
static double scoreComparison = 0;

void resetFinalVariables(){
    qualifyAsHighScore = 0;
    letterCount = 0;
    wipeStaticStrings(name);
    wipeStaticStrings(score);
    wipeStaticStrings(messageScore);
}

void setFinalVariables(){
    readWinners();
    sscanf(winners[4].score, "%lf", &scoreComparison);
    
    if (game.gameTime > scoreComparison) qualifyAsHighScore = 1;

    printf("LAST SCORE: %lf\n", scoreComparison);
    snprintf(score, 10, "%0.lf", game.gameTime);
    strcat(messageScore, "Your Score: ");
    strcat(messageScore, score);
          
}

void drawFinal()
{
    if(IsKeyPressed(KEY_ENTER) && qualifyAsHighScore){ // if player press enter and there are characters in the box
        game.currentScreen = MENU;
        if(nWinners() == 5) overwriteLast();
        else saveHighScore(name);
        readWinners();
        sortWinners(winners);
    } else if(IsKeyPressed(KEY_ENTER)){
        game.currentScreen = MENU;
    }

    int key = GetKeyPressed();

    while (key > 0){
        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
            name[letterCount] = (char)key;
            letterCount++;
        }
        key = GetKeyPressed();  //Check next character in the line
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        letterCount--;
        name[letterCount] = '\0';

        if (letterCount < 0) letterCount = 0;
    }
        
    increaseFramesCounter();

    BeginDrawing();

        ClearBackground(RAYWHITE);
        if(qualifyAsHighScore){
            DrawText("GAME OVER",
                SCREEN_WIDTH/2 - MeasureText("GAME OVER", 70)/2,
                SCREEN_HEIGHT * 0.2,
                70,
                RED);         
            DrawUserInput(messageScore, name, letterCount);
        } else{
            DrawText("GAME OVER",
            SCREEN_WIDTH/2 - MeasureText("GAME OVER", 100)/2,
            SCREEN_HEIGHT * 0.4,
            100,
            RED);
            DrawText("Press enter to go back to the menu",
                SCREEN_WIDTH/2 - MeasureText("Press enter to go back to the menu", 20)/2,
                SCREEN_HEIGHT * 0.70,
                20,
                GRAY);  
        } 
    EndDrawing();

}

void DrawUserInput()
{

    Rectangle textBox = {SCREEN_WIDTH/2 - 225, SCREEN_HEIGHT * 0.5, 450, 65}; //pos x, pos y, largura , altura

    DrawText("Insert your name in the box bellow!",
        SCREEN_WIDTH/2 - MeasureText("Insert your name in the box bellow!", 20)/2,
        SCREEN_HEIGHT * 0.45,
        20,
        GRAY);

    DrawText(messageScore,
        SCREEN_WIDTH/2 - MeasureText(messageScore, 40)/2,
        SCREEN_HEIGHT * 0.70,
        40,
        BLACK);                      


    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);

    DrawText(name, textBox.x + 10, textBox.y + 15, 40, MAROON);

    if (letterCount < MAX_INPUT_CHARS){
        if (((framesCounter/50)%2) == 0) DrawText("_", textBox.x + 10 + MeasureText(name, 40), textBox.y + 15, 40, MAROON);
    }
    
}

void increaseFramesCounter()
{
    if(framesCounter > 10000) framesCounter = 0;
    else framesCounter++;    
}

void saveHighScore(char* name)
{
    FILE *arquivo;
    if(!(arquivo = fopen("winners.bin","a+b")))
        DrawText("Error in opening the file", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 25, WHITE);     //Informa erro na abertura de arquivo, caso aconteça
    else {   
        fwrite(name, sizeof(strlen(name)), 1, arquivo);
        fwrite(score, sizeof(strlen(score)), 1, arquivo);
    }
    fclose(arquivo);    
}

void wipeStaticStrings(char* str)
{
    memset(str,0,sizeof(str));
}

int nWinners()
{
    int i = -1;
    FILE *fwinners = fopen("winners.bin", "rb");
    char ptr[20];
    do{
        fread(ptr, sizeof(strlen(name)), 1, fwinners);
        fread(ptr, sizeof(strlen(score)), 1, fwinners);
        i++;
    }while(!feof(fwinners) && i <= MAX_HIGHSCORES);
    fclose(fwinners);
    return i;
}

void overwriteLast()
{
    FILE *fwinners = fopen("winners.bin", "wb");
    fseek(fwinners, 4 * sizeof(name), SEEK_SET);
    fseek(fwinners, 5 * sizeof(score), SEEK_SET);
    fwrite(name, sizeof(strlen(name)), 1, fwinners);
    fwrite(score, sizeof(strlen(score)), 1, fwinners);
    fclose(fwinners);
}

void swapG(WINNER *g1, WINNER *g2) 
{ 
    WINNER temp = *g1; 
    *g1 = *g2; 
    *g2 = temp; 
} 

void sortWinners(WINNER *winners) 
{ 
   int i, j;
   double s1, s2; 
   for (i = 0; i < MAX_HIGHSCORES-1; i++)       
    
    for (j = 0; j < MAX_HIGHSCORES-i-1; j++){
        sscanf(winners[j].score, "%lf", &s1);
        sscanf(winners[j+1].score, "%lf", &s2);  
        if (s1 < s2) 
            swapG(&winners[j], &winners[j+1]);
    } 
} 
