#include "raylib.h"
#include "globais.h"
#include<stdio.h>

void atualizar_instrucoes(){
    if(jogo.telaAtual == INSTRUCOES)
        if(IsKeyPressed(KEY_ENTER))
            jogo.telaAtual = MENU;    
}

void desenhar_instrucoes(){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawRectangle(80, 50, 800, 450,RED);
        DrawRectangleLines( 80, 50, 800, 450, BLUE);
        
        DrawText("Instrucoes - Como Jogar", 100, 70, 20, BLACK);
        DrawText("Para se movimentar use as teclas:", 130, 100, 15, WHITE);
        DrawText("- UP (Norte)", 150, 120, 12, WHITE);
        DrawText("- DOWN (Sul)", 150, 140, 12, WHITE);
        DrawText("- LEFT (oeste)", 150, 160, 12, WHITE);
        DrawText("- RIGHT (leste)", 150, 180, 12, WHITE);
        DrawText("Para controle do jogo use as teclas:", 130, 210, 15, WHITE);
        DrawText("- S (Salvar)", 150, 230, 12, WHITE);
        DrawText("- ENTER (Pausa)", 150, 250, 12, WHITE);
        DrawText("- ESC (Voltar ao menu principal)", 150, 270, 12, WHITE);
        DrawText("Os tipos de inimigos especiais podem ser identificados por:", 130, 300, 15, WHITE);
        DrawText("- EDITAR (Explosiva)", 150, 320, 12, WHITE);          //EDITAR
        DrawText("- EDITAR (Venenosa)", 150, 340, 12, WHITE);        //EDITAR
        DrawText("- EDITAR (Envenenada)", 150, 360, 12, WHITE);     //EDITAR
        DrawText("Coma os inimigos menores que voce e fuja dos maiores!", 100, 390, 20, BLACK);
        DrawText("Pressione ENTER para voltar ao menu principal", 100, 430, 15, WHITE);       
            
    
    EndDrawing();    
}
