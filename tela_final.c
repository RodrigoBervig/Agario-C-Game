#include "raylib.h"
#include "globais.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void increaseFramesCounter();
void DrawUserInput(char *messageScore, char* nome, int letterCount);

void drawFinal()
{

    char name[MAX_INPUT_CHARS + 1] = "\0"; 
    int letterCount = 0;

    char score[10];
    snprintf(score, 10, "%.0lf", jogo.tempodejogo);

    char messageScore[50] = {};
    strcat(messageScore, "Seu score: ");
    strcat(messageScore, score);

    SetTargetFPS(30);           


    while (!WindowShouldClose())  {

        int key = GetKeyPressed();

        while (key > 0){
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
                name[letterCount] = (char)key;
                letterCount++;
            }
                
            key = GetKeyPressed();  // Checa o próximo caractere na fila
        }

        if (IsKeyPressed(KEY_BACKSPACE)){
            letterCount--;
            name[letterCount] = '\0';

            if (letterCount < 0) letterCount = 0;
        }
        

        increaseFramesCounter();

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("GAME OVER",
                LARGURATELA/2 - MeasureText("GAME OVER", 70)/2,
                ALTURATELA * 0.2,
                70,
                RED);          

            /*if(jogo.tempodejogo > menor highscore)*/DrawUserInput(messageScore, name, letterCount);

          /*  DrawText("Insira seu nome na caixa!",
                LARGURATELA/2 - MeasureText("Insira seu nome na caixa", 20)/2,
                ALTURATELA * 0.45,
                20,
                GRAY);*/

        EndDrawing();
    }

    CloseWindow(); 

}

void DrawUserInput(char *messageScore, char* name, int letterCount)
{

    Rectangle textBox = {LARGURATELA/2 - 225, ALTURATELA * 0.5, 450, 65}; //pos x, pos y, largura , altura

    DrawText("Insira seu nome na caixa!",
        LARGURATELA/2 - MeasureText("Insira seu nome na caixa", 20)/2,
        ALTURATELA * 0.45,
        20,
        GRAY);

    DrawText(messageScore,
        LARGURATELA/2 - MeasureText(messageScore, 40)/2,
        ALTURATELA * 0.70,
        40,
        BLACK);                      


    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);

    DrawText(name, textBox.x + 10, textBox.y + 15, 40, MAROON);


    if (letterCount < MAX_INPUT_CHARS){
        // desenha | piscando
        if (((framesCounter/15)%2) == 0) DrawText("_", textBox.x + 10 + MeasureText(name, 40), textBox.y + 15, 40, MAROON);
    }
    
}

void increaseFramesCounter()
{
    if(framesCounter > 10000) framesCounter = 0;
    else framesCounter++;    
}