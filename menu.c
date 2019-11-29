#include "raylib.h"
#include "raymath.h"
#include "physac.h"

#include "defines.h"


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
            menuSelected = (menuSelected == 0) ? 1 : 0;
            
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed('W')){
            menuSelected = (menuSelected == 1) ? 0 : 1;

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

        DrawText("Agario", screenWidth/2 - MeasureText("Agario", 60)/2, screenHeight * 0.1, 60,  WHITE); 
        
        
        DrawText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), screenWidth/2 - MeasureText(((menuSelected == 0) ? "- Jogar -" : "Jogar"), 40)/2, screenHeight * 0.35, 40, (menuSelected == 0) ? RED : WHITE);
        
        DrawText(((menuSelected == 1) ? "- Sair -" : "Sair"), screenWidth/2 - MeasureText(((menuSelected == 1) ? "- Sair -" : "Sair"), 40)/2, screenHeight * 0.50, 40, (menuSelected == 1) ? RED : WHITE);
    
    

        DrawText("-SPACE- select    -W- up  -S- down", screenWidth/2 - MeasureText("-SPACE- select    -W- up  -S- down", 20)/2 , screenHeight * 0.8, 20, WHITE);
    
        // Draw credits
        DrawText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]", screenWidth/2 - MeasureText("[Criado por - João Pedro Ourique e Rodrigo Bervig - INF UFRGS]", 15)/2 , screenHeight * 0.95  , 15, WHITE);
        

        EndDrawing();
    }

    /*Vector2 vetor = (Vector2){screenWidth / 2 - MeasureTextEx(fontTexto, "Agario-se", 60, FONT_SPACING).x / 2,
            screenHeight * 0.15};*/

    while (!WindowShouldClose())
    {

        TitleDraw();
        TitleUpdate();

        /*DrawText(fontTexto, "Agario-se", (Vector2){screenWidth / 2 - MeasureTextEx(fontTexto, "Agario-se", 60, FONT_SPACING).x / 2,
            screenHeight * 0.15},
            60,
            FONT_SPACING, WHITE);
        */
        /*DrawText(fontTexto, "agario-se", (Vector2){0,0},
            60,
            FONT_SPACING, WHITE);*/
        //DrawText(fontTexto, "Agario", (Vector2){0,0}, 60, 1, WHITE);
        //DrawText("Agario", 40, 40,  20,  WHITE);
        //DrawText("Agario", screenWidth / 2 - MeasureTextEx(fontTexto, "Agario-se", 60, FONT_SPACING).x / 2, screenHeight * 0.15,  20,  WHITE);

        /*DrawText( "ray mario", (Vector2){screenWidth / 2 - MeasureTextEx( "ray mario", 60, FONT_SPACING).x / 2, screenHeight * 0.15f}, 60, FONT_SPACING, WHITE);*/

    }

    CloseWindow();

    return 0;
}