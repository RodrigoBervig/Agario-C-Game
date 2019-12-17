#include "raylib.h"
#include "globais.h"
#include <stdio.h>
#include <string.h>

static int nGanhadores = -1;

void atualizar_ganhadores(){
    if(IsKeyPressed(KEY_ENTER))
        jogo.telaAtual = MENU;    
}

void desenharGanhadores(){
    BeginDrawing();

        ClearBackground(RAYWHITE);
        int i = 0, j;
        float height = 0.27;
        float height2 = 0.27;
        if(nGanhadores){
            DrawRectangle(LARGURATELA*0.1, ALTURATELA * 0.1, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
            DrawText(ganhadores[0].nome, LARGURATELA * 0.13, ALTURATELA*0.1 + 20, 40, RED);
            DrawText(ganhadores[0].score, LARGURATELA * 0.8, ALTURATELA*0.1 + 20, 40, RED);
        }
        while(i < nGanhadores-1){
            DrawRectangle(LARGURATELA*0.1, ALTURATELA * height, LARGURATELA*0.8, ALTURATELA*0.15, BLACK);
            height2 = 0.27;
            for(j = 1; j < nGanhadores; j++){
                DrawText(ganhadores[j].nome, LARGURATELA * 0.13, ALTURATELA*height2 + 20, 40, RED);
                DrawText(ganhadores[j].score, LARGURATELA * 0.8, ALTURATELA*height2 + 20, 40, RED);
                height2 += 0.17;
            }
            i++;
            height += 0.17;
        }
    DrawText("SCORE BOARD",
        LARGURATELA/2 - MeasureText("SCORE BOARD", 35)/2,
        ALTURATELA * 0.03,
        35,
        BLACK);

    DrawText("Aperte enter para voltar ao menu principal",
        LARGURATELA/2 - MeasureText("Aperte enter para voltar ao menu principal", 19)/2,
        ALTURATELA * 0.95,
        19,
        GRAY);
    EndDrawing();    
}

void readGanhadores()
{
    nGanhadores = -1;
    FILE *fganhadores = fopen("ganhadores.bin", "rb");
    int i = 0;
    do{
        fread(ganhadores[i].nome, sizeof(strlen(name)), 1, fganhadores);
        fread(ganhadores[i].score, sizeof(strlen(score)), 1, fganhadores);
        printf("%s\n", ganhadores[i].nome);
        i++;
        nGanhadores ++;
    }while(!feof(fganhadores) && i <= MAX_HIGHSCORES);
    fclose(fganhadores);
    printf("N DE GANHADORES: %d\n", nGanhadores);
}