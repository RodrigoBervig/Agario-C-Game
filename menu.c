#include "raylib.h"
#include "raymath.h"
#include "physac.h"
#include "globais.h"
#include <stdlib.h>
#include "tela_jogar.h"

void chamaJogo()
{
    jogo.telaAtual = JOGAR;
    jogo.tempodejogo = 0;
    
    jogador.vivo = 1;
    jogador.r = R_INICIO;
    jogador.envenenado = 0;
    jogador.v = 2.5;
    
    inimigos_vivos = INIMIGOS_INICIO;
    int i;
    cria_novos = GetTime();
    
    for(i=0;i<inimigos_vivos;i++){
        cria_inimigo(i);
    }
    
    jogo.tempodejogo = GetTime();
    jogo.buffer = 0;
    jogo.pausa = 0;
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
                case 0: { //JOGAR
                    chamaJogo();
                } break;
                case 1: {
                    jogo.telaAtual = GANHADORES;
                }
                case 2: {
                    jogo.telaAtual = INSTRUCOES;
                }
                case 3: {
                    jogo.telaAtual = CARREGAR;
                }
                case 4: {                    
                    CloseWindow();
                } break;
            }
        }
    }


void TitleDraw()
{

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Agario", LARGURATELA/2 - MeasureText("Agario", 75)/2, ALTURATELA * 0.08, 75,  GREEN); 
        
        
        DrawText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), // O que é desenhado (ver condicionais ternários)
            LARGURATELA/2 - MeasureText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), 40)/2, //Posição x do texto
            ALTURATELA * 0.28, //posição y do texto
            40, //tamanho do texto
            (menuSelected == 0) ? BLUE : WHITE); //cor em que o texto vai estar
        DrawText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 40)/2, 
            ALTURATELA * 0.42, 
            40, 
            (menuSelected == 1) ? BLUE : WHITE);
        DrawText(((menuSelected == 2) ? "- Instructions -" : "Instructions"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 2) ? "- Instructions -" : "Instructions"), 40)/2, 
            ALTURATELA * 0.56, 
            40, 
            (menuSelected == 2) ? BLUE : WHITE);
        DrawText(((menuSelected == 3) ? "- Carregar Jogo -" : "Carregar Jogo"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 3) ? "- Carregar Jogo -" : "Carregar Jogo"), 40)/2, 
            ALTURATELA * 0.68, 
            40, 
            (menuSelected == 3) ? BLUE : WHITE);
        DrawText(((menuSelected == 4) ? "- Sair -" : "Sair"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 4) ? "- Sair -" : "Sair"), 40)/2, 
            ALTURATELA * 0.80, 
            40, 
            (menuSelected == 4) ? RED : WHITE);        

        //Instruções do menu
        DrawText("-SPACE- select    -W- up  -S- down", 
            LARGURATELA/2 - MeasureText("-SPACE- select    -W- up  -S- down", 20)/2, 
            ALTURATELA * 0.90, 20, WHITE);
        
        // Créditos
        DrawText("[Created by - João Pedro Ourique and Rodrigo Bervig - INF UFRGS]",
            LARGURATELA/2 - MeasureText("[Created by - João Pedro Ourique and Rodrigo Bervig - INF UFRGS]", 15)/2,
            ALTURATELA * 0.95,
            17,
            WHITE);
        
        EndDrawing();
    }
