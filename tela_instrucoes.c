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

        ClearBackground(BLACK);
        
        DrawRectangle(50, 25, 900, 500,RAYWHITE);
        DrawRectangleLines( 50, 25, 900, 500, BLUE);
        
        DrawText("Instructions - How to Play", 300, 50, 30, RED);
        DrawText("Use your arrow keys to move:", 130, 100, 15, BLACK);
        DrawText("- UP (North)", 150, 120, 12, BLACK);
        DrawText("- DOWN (South)", 150, 140, 12, BLACK);
        DrawText("- LEFT (West)", 150, 160, 12, BLACK);
        DrawText("- RIGHT (East)", 150, 180, 12, BLACK);
        DrawText("Game control functions:", 130, 210, 15, BLACK);
        DrawText("- ENTER (Pause)", 150, 230, 12, BLACK);
        DrawText("- S (Save)", 150, 250, 12, BLACK);        
        DrawText("- M (Go back to Menu)", 150, 270, 12, BLACK);
        DrawText("- ESC (Leave Game)", 150, 290, 12, BLACK);
        DrawText("Pay attention to the types of enemies you'll face :", 130, 320, 15, BLACK);
        DrawText("  - (Explosive). Eat it, and you'll explode!", 160, 343, 12, BLACK);          
        DrawRectangle(150, 340, 15, 15,EXPLOSIVE_COLOR);
        DrawText("  - (Poisonous) Eat it, and you'll get poisoned for a while!", 160, 363, 12, BLACK);        
        DrawRectangle(150, 360, 15, 15, POISON_GREEN);
        DrawText("  - (Poisoned) When poisoned, you can't eat!", 160, 383, 12, BLACK);     
        DrawRectangle(150, 380, 15, 15,PLAYER_POISONED_COLOR);
        DrawText("Eat smaller enemies and try to escape larger ones! Good luck!", 100, 410, 20, BLACK);
        DrawText("Press ENTER to go back to Menu", 270, 450, 25, BLACK);       
            
    EndDrawing();    
}
