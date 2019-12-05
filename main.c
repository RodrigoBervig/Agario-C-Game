#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "globais.h"
#include "tela_instrucoes.h"
#include "tela_jogar.h"
#include "menu.h"

//funções
void atualizadesenho();

int main(){
     // Inicializa
    //--------------------------------------------------------------------------------------
        
    InitWindow(LARGURATELA, ALTURATELA, "agario.c");
    
    jogo.telaAtual = MENU;      //inicializar telaatual do jogo como menu
    
    //--------------------------------------------------------------------------------------
    
    SetTargetFPS(60);               // Jogo roda a 60 FPS
    
        
     // Main game loop
    while (!WindowShouldClose())    // Detecta se fecha a janela de jogo ou aperta tecla Esc
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
    switch(jogo.telaAtual){
        case(MENU):
        {
            TitleDraw();
            TitleUpdate();
        } break;
        case(INSTRUCOES):
        {
            desenhar_instrucoes();
            atualizar_instrucoes();
        } break;
        case(GANHADORES):
        {
            //
        } break;
        case(CARREGAR):
        {
            //
        } break;
        case(JOGAR):
        {   
            atualizajogo();
            desenhajogo();
        } break;
        case(FINAL):
        {
            //
        } break;
    }   
}
