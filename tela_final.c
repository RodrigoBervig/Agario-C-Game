#include "raylib.h"
#include "globais.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tela_ganhadores.h"

void increaseFramesCounter();
void DrawUserInput();
void salvaHighScore(char* name);
void drawFinal();
void limpaStaticStrings(char* str);
int nGanhadores();
void sobreEscreveUltimo();
void sortGanhadores(GANHADOR ganhadores[]);
void swapG(GANHADOR *g1, GANHADOR *g2); 

static int qualifyAsHighScore = 0;
static double scoreComparison = 0;

void resetFinalVariables(){
    qualifyAsHighScore = 0;
    letterCount = 0;
    limpaStaticStrings(name);
    limpaStaticStrings(score);
    limpaStaticStrings(messageScore);
}

void setFinalVariables(){
    readGanhadores();
    sscanf(ganhadores[4].score, "%lf", &scoreComparison);
    //if(nGanhadoresAtual < 5) qualifyAsHighScore = 1;
    if (jogo.tempodejogo > scoreComparison) qualifyAsHighScore = 1;

    printf("SCORE ULTIMO: %lf\n", scoreComparison);
    snprintf(score, 10, "%0.lf", jogo.tempodejogo);
    strcat(messageScore, "Seu score: ");
    strcat(messageScore, score);
          
}

void drawFinal()
{


    if(IsKeyPressed(KEY_ENTER) && qualifyAsHighScore){ // se o jogador apertar enter e tiver caracteres na caixa
        jogo.telaAtual = MENU;
        if(nGanhadores() == 5) sobreEscreveUltimo();
        else salvaHighScore(name);
        readGanhadores();
        sortGanhadores(ganhadores);
    } else if(IsKeyPressed(KEY_ENTER)){
        jogo.telaAtual = MENU;
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

         
        if(qualifyAsHighScore){
            DrawText("GAME OVER",
                LARGURATELA/2 - MeasureText("GAME OVER", 70)/2,
                ALTURATELA * 0.2,
                70,
                RED);         
            DrawUserInput(messageScore, name, letterCount);
        } else{
            DrawText("GAME OVER",
            LARGURATELA/2 - MeasureText("GAME OVER", 100)/2,
            ALTURATELA * 0.4,
            100,
            RED);
            DrawText("Aperte enter para voltar ao menu",
                LARGURATELA/2 - MeasureText("Aperte enter para voltar ao menu", 20)/2,
                ALTURATELA * 0.70,
                20,
                GRAY);  
        } 

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
        fwrite(name, sizeof(strlen(name)), 1, arquivo);
        fwrite(score, sizeof(strlen(score)), 1, arquivo);
    }
    fclose(arquivo);    
}

void limpaStaticStrings(char* str)
{
    memset(str,0,sizeof(str));
}

int nGanhadores()
{
    int i = -1;
    FILE *fganhadores = fopen("ganhadores.bin", "rb");
    char ptr[20];
    do{
        fread(ptr, sizeof(strlen(name)), 1, fganhadores);
        fread(ptr, sizeof(strlen(score)), 1, fganhadores);
        i++;
    }while(!feof(fganhadores) && i <= MAX_HIGHSCORES);
    fclose(fganhadores);
    return i;
}

void sobreEscreveUltimo()
{
    FILE *fganhadores = fopen("ganhadores.bin", "wb");
    fseek(fganhadores, 4 * sizeof(name), SEEK_SET);
    fseek(fganhadores, 5 * sizeof(score), SEEK_SET);
    fwrite(name, sizeof(strlen(name)), 1, fganhadores);
    fwrite(score, sizeof(strlen(score)), 1, fganhadores);
    fclose(fganhadores);
}

void swapG(GANHADOR *g1, GANHADOR *g2) 
{ 
    GANHADOR temp = *g1; 
    *g1 = *g2; 
    *g2 = temp; 
} 

void sortGanhadores(GANHADOR *ganhadores) 
{ 
   int i, j;
   double s1, s2; 
   for (i = 0; i < MAX_HIGHSCORES-1; i++)       
    
    for (j = 0; j < MAX_HIGHSCORES-i-1; j++){
        sscanf(ganhadores[j].score, "%lf", &s1);
        sscanf(ganhadores[j+1].score, "%lf", &s2);  
        if (s1 < s2) 
            swapG(&ganhadores[j], &ganhadores[j+1]);
    } 
} 
