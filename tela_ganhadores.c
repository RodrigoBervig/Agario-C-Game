#include "raylib.h"
#include "globais.h"
#include  <stdio.h>
#include <string.h>


void atualizar_ganhadores(){
    if(jogo.telaAtual == INSTRUCOES)
        if(IsKeyPressed(KEY_ENTER))
            jogo.telaAtual = MENU;    
}

void desenharGanhadores(){
    BeginDrawing();

        ClearBackground(RAYWHITE);
        
        DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.1, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
        DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.27, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
        DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.44, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
        DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.61, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
        DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.78, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);

        DrawText(nomeGanhadores[0], 200, 200, 40, RED);
 //       char scoreTexto[5];
   //     snprintf(scoreTexto, 5, "%.0lf", scoreGanhadores[0]);
        DrawText(scoreGanhadoresString[0], 500, 200, 40, RED);
    EndDrawing();    
}

void readGanhadores()
{
    FILE *fganhadores = fopen("ganhadores.bin", "rb");
    int i = 0;
    while(!feof(fganhadores) && i < MAX_HIGHSCORES){
        fread(nomeGanhadores[i], sizeof(strlen(nomeGanhadores[i])), 1, fganhadores);
        fread(scoreGanhadoresString[i], sizeof(strlen(scoreGanhadoresString[i])), 1, fganhadores);
        printf("%s\n", scoreGanhadoresString[i]);
        i++;
    }
    fclose(fganhadores);
    printf("%s\n", scoreGanhadoresString[i]);
}