#include "raylib.h"
#include "raymath.h"
#include "physac.h"
#include <stdlib.h>

//#include "defines.h"


int main()
{
    Font fontTexto = GetFontDefault();
    fontTexto.baseSize = 16;
    fontTexto.charsCount = 95;

    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "teste");

    SetTargetFPS(60);

    static int menuSelected = 0;

    void TitleUpdate()
    {

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed('S')){
            menuSelected = (menuSelected + 1) % 4;
            
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed('W')){
            menuSelected = (menuSelected == 0)? menuSelected = 3 : --menuSelected; 

        }
        if (IsKeyPressed(KEY_SPACE)){
            switch (menuSelected)
            {
                case 0:
                { 
                    //game.framesCounter = 0;
                    //game.currentScreen = LOADING;
                    
                    //LoadLevel(game.currentLevel);
                } break;
                case 1:
                {
                    //game.framesCounter = 0;
                    
                    //game.QuitGame = true;
                } break;
            }
        }
    }




    void TitleDraw()
    {

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Agario", screenWidth/2 - MeasureText("Agario", 75)/2, screenHeight * 0.1, 75,  GREEN); 
        
        
        DrawText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), // O que é desenhado (ver condicionais ternários)
            screenWidth/2 - MeasureText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), 40)/2, //Posição x do texto
            screenHeight * 0.30, //posição y do texto
            40, //tamanho do texto
            (menuSelected == 0) ? BLUE : WHITE); //cor em que o texto vai estar
        DrawText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 
            screenWidth/2 - MeasureText(((menuSelected == 1) ? "- Score Board -" : "Score Board"), 40)/2, 
            screenHeight * 0.45, 
            40, 
            (menuSelected == 1) ? BLUE : WHITE);
        DrawText(((menuSelected == 2) ? "- Carregar Jogo -" : "Carregar Jogo"), 
            screenWidth/2 - MeasureText(((menuSelected == 2) ? "- Carregar Jogo -" : "Carregar Jogo"), 40)/2, 
            screenHeight * 0.60, 
            40, 
            (menuSelected == 2) ? BLUE : WHITE);
        DrawText(((menuSelected == 3) ? "- Sair -" : "Sair"), 
            screenWidth/2 - MeasureText(((menuSelected == 3) ? "- Sair -" : "Sair"), 40)/2, 
            screenHeight * 0.75, 
            40, 
            (menuSelected == 3) ? RED : WHITE);        

        //Instruções do menu
        DrawText("-SPACE- select    -W- up  -S- down", 
            screenWidth/2 - MeasureText("-SPACE- select    -W- up  -S- down", 20)/2, 
            screenHeight * 0.90, 20, WHITE);
        
        // Créditos
        DrawText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]",
            screenWidth/2 - MeasureText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]", 15)/2,
            screenHeight * 0.95,
            15,
            WHITE);
        
        EndDrawing();
    }

    /*Vector2 vetor = (Vector2){screenWidth / 2 - MeasureTextEx(fontTexto, "Agario-se", 60, FONT_SPACING).x / 2,
            screenHeight * 0.15};*/

    while (!WindowShouldClose())
    {

        TitleDraw();
        TitleUpdate();

    }

    CloseWindow();

    return 0;
}
