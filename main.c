#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"
#include "globais.h"

//funções
void atualizadesenho();

int main(){
     // Inicializa
    //--------------------------------------------------------------------------------------
        
    InitWindow(LarguraTela, AlturaTela, "agario.c");
    
    jogo.telaAtual = MENU;
    jogo.sairjogo = 0;
    
    //--------------------------------------------------------------------------------------
    
    SetTargetFPS(60);               // Jogo roda a 60 FPS
    
    //inicializar telaatual do jogo como menu
    
     // Main game loop
    while (!WindowShouldClose() && !jogo.sairjogo)    // Detecta se fecha a janela de jogo ou aperta tecla Esc
    {                
        atualizadesenho();        
    }

    // Encerra
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void atualizadesenho(){
    
    /*switch(jogo.telaAtual){
        case(MENU):
        {
            funçao
        } break;
        case(INSTRUCOES):
        {
            funçao
        } break;
        case(GANHADORES):
        {
            funçao
        } break;
        case(JOGAR):
        {
            funçao:
                       
            .
            .
            .
        } break;
        case(FINAL):
        {
            funçao
        } break;
    }*/    
}