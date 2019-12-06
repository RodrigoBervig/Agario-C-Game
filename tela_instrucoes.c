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
        
        DrawText("Instructions - How to Play", 100, 70, 20, BLACK);
        DrawText("Use your arrow keys to move:", 130, 100, 15, WHITE);
        DrawText("- UP (North)", 150, 120, 12, WHITE);
        DrawText("- DOWN (South)", 150, 140, 12, WHITE);
        DrawText("- LEFT (West)", 150, 160, 12, WHITE);
        DrawText("- RIGHT (East)", 150, 180, 12, WHITE);
        DrawText("Game control functions:", 130, 210, 15, WHITE);
        DrawText("- ENTER (Pause)", 150, 230, 12, WHITE);
        DrawText("- S (Save)", 150, 250, 12, WHITE);        
        DrawText("- M (Go back to Menu)", 150, 270, 12, WHITE);
        DrawText("- ESC (Leave Game)", 150, 290, 12, WHITE);
        DrawText("Pay attention to the types of enemies you'll face :", 130, 320, 15, WHITE);
        DrawText("  - (Explosive). Eat it, and you'll explode!", 160, 343, 12, WHITE);          
        DrawRectangle(150, 340, 15, 15,BLACK);
        DrawText("  - (Poisonous) Eat it, and you'll get poisoned for a while!", 160, 363, 12, WHITE);        
        DrawRectangle(150, 360, 15, 15,LIME);
        DrawText("  - (Poisoned) When poisoned, you can't eat!", 160, 383, 12, WHITE);     
        DrawRectangle(150, 380, 15, 15,MAGENTA);
        DrawText("Eat smaller enemies and try to escape larger ones! Good luck!", 100, 410, 20, BLACK);
        DrawText("Press ENTER to go back to Menu", 100, 450, 15, WHITE);       
            
    EndDrawing();    
}
