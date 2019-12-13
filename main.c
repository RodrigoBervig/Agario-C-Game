#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "globais.h"
#include "tela_instrucoes.h"
#include "tela_jogar.h"
#include "menu.h"
#include "tela_ganhadores.h"
#include "tela_final.h"

//funções
void atualizadesenho();

int main(){
     
    InitWindow(LARGURATELA, ALTURATELA, "AGARIO.C");
    
    jogo.telaAtual = MENU;      //inicializar tela atual do jogo como menu
    readGanhadores();
    
    
    SetTargetFPS(60); // Jogo roda a 60 frames/segundo
    
    // Main loop game
    while (!WindowShouldClose()) // Executa loop enquanto usuário não apertar tecla Esc
    {                
        atualizadesenho();        
    }

    // Encerra
    CloseWindow();


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
            desenharGanhadores();
        } break;
        case(JOGAR):
        {   
            atualizajogo();
            desenhajogo();
        } break;
        case(FINAL):
        {
            drawFinal();
        } break;
    }   
}
