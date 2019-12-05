#include "raylib.h"
#include "globais.h"
#include  <stdio.h>

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
        DrawText("- M (Voltar ao Menu)", 150, 270, 12, WHITE);
        DrawText("- ESC (Sair)", 150, 290, 12, WHITE);
        DrawText("Os tipos de inimigos especiais podem ser identificados por cores :", 130, 320, 15, WHITE);
        DrawText("  - (Explosiva)", 160, 343, 12, WHITE);          
        DrawRectangle(150, 340, 15, 15,BLACK);
        DrawText("  - (Venenosa)", 160, 363, 12, WHITE);        
        DrawRectangle(150, 360, 15, 15,LIME);
        DrawText("  - (Envenenada)", 160, 383, 12, WHITE);     
        DrawRectangle(150, 380, 15, 15,MAGENTA);
        DrawText("Coma os inimigos menores que voce e fuja dos maiores!", 100, 410, 20, BLACK);
        DrawText("Pressione ENTER para voltar ao menu principal", 100, 450, 15, WHITE);       
            
    EndDrawing();    
}
