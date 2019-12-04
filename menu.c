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
            menuSelected = (menuSelected + 1) % 4;
            
    }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed('W')){
            menuSelected = (menuSelected == 0)? menuSelected = 3 : --menuSelected; 

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
                    jogo.telaAtual = CARREGAR;
                }
                case 3: {                    
                    CloseWindow();
                } break;
            }
        }
    }


void TitleDraw()
{

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Agario", LARGURATELA/2 - MeasureText("Agario", 75)/2, ALTURATELA * 0.1, 75,  GREEN); 
        
        
        DrawText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), // O que é desenhado (ver condicionais ternários)
            LARGURATELA/2 - MeasureText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), 40)/2, //Posição x do texto
            ALTURATELA * 0.30, //posição y do texto
            40, //tamanho do texto
            (menuSelected == 0) ? BLUE : WHITE); //cor em que o texto vai estar
        DrawText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 40)/2, 
            ALTURATELA * 0.45, 
            40, 
            (menuSelected == 1) ? BLUE : WHITE);
        DrawText(((menuSelected == 2) ? "- Carregar Jogo -" : "Carregar Jogo"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 2) ? "- Carregar Jogo -" : "Carregar Jogo"), 40)/2, 
            ALTURATELA * 0.60, 
            40, 
            (menuSelected == 2) ? BLUE : WHITE);
        DrawText(((menuSelected == 3) ? "- Sair -" : "Sair"), 
            LARGURATELA/2 - MeasureText(((menuSelected == 3) ? "- Sair -" : "Sair"), 40)/2, 
            ALTURATELA * 0.75, 
            40, 
            (menuSelected == 3) ? RED : WHITE);        

        //Instruções do menu
        DrawText("-SPACE- select    -W- up  -S- down", 
            LARGURATELA/2 - MeasureText("-SPACE- select    -W- up  -S- down", 20)/2, 
            ALTURATELA * 0.90, 20, WHITE);
        
        // Créditos
        DrawText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]",
            LARGURATELA/2 - MeasureText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]", 15)/2,
            ALTURATELA * 0.95,
            15,
            WHITE);
        
        EndDrawing();
    }
