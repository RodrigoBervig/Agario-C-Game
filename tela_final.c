#include "raylib.h"
#include "globais.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void increaseFramesCounter();
void DrawUserInput();
void salvaHighScore(char* name);
void drawFinal();
void limpaStaticStrings(char* str);

void resetFinalVariables(){
    letterCount = 0;
    limpaStaticStrings(name);
    limpaStaticStrings(score);
    limpaStaticStrings(messageScore);
}

void setFinalVariables(){
    resetFinalVariables();
    snprintf(score, 10, "%.0lf", jogo.tempodejogo);

    strcat(messageScore, "Seu score: ");
    strcat(messageScore, score);
          
}

void drawFinal()
{


    if(IsKeyPressed(KEY_ENTER)){ // se o jogador apertar enter e tiver caracteres na caixa
        jogo.telaAtual = MENU;
        salvaHighScore(name);
    }

    int key = GetKeyPressed();

    while (key > 0){
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

void DrawUserInput()
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
        if (((framesCounter/50)%2) == 0) DrawText("_", textBox.x + 10 + MeasureText(name, 40), textBox.y + 15, 40, MAROON);
    }
    
}

void increaseFramesCounter()
{
    if(framesCounter > 10000) framesCounter = 0;
    else framesCounter++;    
}

void salvaHighScore(char* name)
{
    FILE *arquivo;
    if(!(arquivo = fopen("ganhadores.bin","a+b")))
        DrawText("Erro ao abrir arquivo", LARGURATELA/2, ALTURATELA/2, 25, WHITE);     //Informa erro na abertura de arquivo, caso aconteça
    else {   
        fwrite(name, sizeof(name), 1, arquivo);
        fwrite(name, sizeof(double), 1, arquivo);
    }
    fclose(arquivo);    
}

void limpaStaticStrings(char* str){
    memset(str,0,sizeof(str));
}