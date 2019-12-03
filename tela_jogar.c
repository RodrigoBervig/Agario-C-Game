#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"
#include "globais.h"
#include<math.h>
/*FALTA:
- Fazer inimigos se movimentarem
- Arrumar onde os inimigos aparecem para não aparecer em cima do jogador(e se der não aparecerem um em cima do outro)
- Avaliar se muda a proporção normais/explosivas/venenosas
- Poder salvar
- Conferir variáveis
- ?
*/
void desenha_inimigos(){
    int i;
    for(i=0;i<inimigos_vivos;i++){
        switch(inimigos[i].tipo){
            case 0:
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, BLUE);
            break;
            case 1:
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, LIME);
            break;
            case 2:
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, BLACK);
            break;           
        }
    }    
}


void cria_inimigo(int i){       //Cria novo inimigo, chamada periodicamente e quando jogador come um inimigo

    inimigos[i].p.y = GetRandomValue(-ALTURATELA, ALTURATELA);
    inimigos[i].p.x = GetRandomValue(-LARGURATELA, LARGURATELA) ;
    inimigos[i].r = (int)floor(GetRandomValue(jogador.r/2, 2*jogador.r));
    inimigos[i].tipo = GetRandomValue(0,2);
    inimigos[i].mov = GetRandomValue(0,3);
    inimigos[i].vmodulo = 2 + (int)floor((GetTime() - jogo.tempodejogo + jogo.buffer)/20);      //o vmodulo dos inimigos criados é 2 + n, onde n é o piso do número de períodos de 20s que já foram jogados

}


void colisoes(){        //verifica se há alguma colisão entre o jogador e outro inimigo
    int i;
    for(i=0;i<inimigos_vivos;i++){
        if(abs(posicaojogador.x - inimigos[i].p.x)<15){     //verifica apenas para os inimigos que estão proximos do jogador
            if(CheckCollisionCircles(posicaojogador, jogador.r, inimigos[i].p, inimigos[i].r)){
                if(jogador.r<inimigos[i].r || inimigos[i].tipo == EXPLOSIVA)
                    jogador.vivo = 0;
                else{
                    if(!jogador.envenenado){
                        if(inimigos[i].tipo == VENENOSA){       //se jogador come um inimigo venenoso, é envenenado
                            jogador.envenenado = 1;
                            delay = GetTime();
                        }        
                        jogador.r += (int)floor(inimigos[i].r/10);      //aumenta raio do jogador proporcionalmente à peça que ele comeu
                        cria_inimigo(i);
                    }                    
                }
            }
        }        
    }
}


void desenha_pausa(){
    
    DrawRectangle(250, 130, 400, 240,RED);
    DrawRectangleLines(250, 130, 400, 240, BLACK);

    DrawText("Jogo Pausado!", 350, 150, 20, WHITE);
    DrawText("- S (Salvar)", 270, 190, 15, WHITE);
    DrawText("- ENTER (Voltar ao jogo)", 270, 240, 15, WHITE);
    DrawText("- M (Voltar ao Menu)", 270, 290, 15, WHITE);
    DrawText("- ESC (Sair do jogo)", 270, 340, 15, WHITE);
    
}


void atualizajogo(){
    
    if(IsKeyPressed(KEY_ENTER)){
        if(!jogo.pausa){        //se jogo não está pausado, pausa
            jogo.pausa = 1;
            jogo.buffer += GetTime() - jogo.tempodejogo;      //armazena em buffer o tempo já jogado
        }
        else{
            jogo.pausa = 0;
            jogo.tempodejogo = GetTime();       //retoma jogo e ajusta o tempo
        }              
    }
    
    if(jogo.pausa){     //se jogo está pausado
        if(IsKeyPressed(KEY_S))
            //salvar  -      EDITAR
        if(IsKeyPressed(KEY_M))
            jogo.telaAtual = MENU;
    }
    
    
    else if(jogador.vivo && !jogo.pausa){
        int i;        
        
        if(IsKeyDown(KEY_RIGHT)){       //movimenta jogo, se usuário aperta RIGHT
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.x -= 3.0f;
                if(inimigos[i].p.x < -2*LARGURATELA)        //reposiciona inimigos que ficarem longe demais
                    inimigos[i].p.x = GetRandomValue(-LARGURATELA, LARGURATELA);                    
            } 
        }
        
        
        if(IsKeyDown(KEY_LEFT)){        //movimenta jogo, se usuário aperta LEFT
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.x += 3.0f;
                if(inimigos[i].p.x > 2*LARGURATELA)     //reposiciona inimigos que ficarem longe demais
                    inimigos[i].p.x = GetRandomValue(-LARGURATELA, LARGURATELA); 
            } 
        }
        
        
        if(IsKeyDown(KEY_UP)){      //movimenta jogo, se usuário aperta UP
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.y += 3.0f;
                if(inimigos[i].p.y > 2*ALTURATELA)      //reposiciona inimigos que ficarem longe demais
                    inimigos[i].p.y = GetRandomValue(-ALTURATELA, ALTURATELA);
            } 
        }
        
        
        if(IsKeyDown(KEY_DOWN)){        //movimenta jogo, se usuário aperta DOWN
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.y -= 3.0f;
                if(inimigos[i].p.y < -2*ALTURATELA)         //reposiciona inimigos que ficarem longe demais
                    inimigos[i].p.y = GetRandomValue(-ALTURATELA, ALTURATELA);
            } 
        }
        
        colisoes();         //verifica se jogador colidiu com algum inimigo
        
        if(((int)GetTime() - (int)jogo.tempodejogo + (int)jogo.buffer)%30 && inimigos_vivos < MAX_INIMIGOS){        //Cria um inimigo novo a cada 30s, enquanto não houverem MAX_INIMIGOS
            cria_inimigo(inimigos_vivos);
            inimigos_vivos++;
        }
        
        if(jogador.envenenado){     //enquanto jogador está envenenado, incremnta delay a cada 2s
            if(GetTime() - delay > 3){     //quando se passam 3s desde que foi envenenado, passa o veneno e zera delay
                jogador.envenenado = 0;
                delay = 0;
            }
        }            
        
    }  
    else if(!jogador.vivo){
        jogo.telaAtual = FINAL;
        jogo.tempodejogo = GetTime() - jogo.tempodejogo + jogo.buffer;
    }
}

void desenhajogo(){
    BeginDrawing();
               
        ClearBackground(RAYWHITE);
        if(!jogador.envenenado)
            DrawCircleV(posicaojogador, jogador.r, MAROON);
        else
            DrawCircleV(posicaojogador, jogador.r, MAGENTA);
        
        desenha_inimigos();
        if(jogo.pausa)
            desenha_pausa();
        if(!jogo.pausa)
            DrawText(FormatText("Score : %2.0f", GetTime() - jogo.tempodejogo + jogo.buffer), 910, 525, 15, BLACK);
        
     EndDrawing();
        //----------------------------------------------------------------------------------
    
}

int main(){
    // Inicializa
    //--------------------------------------------------------------------------------------
        
    InitWindow(LARGURATELA, ALTURATELA, "tela_jogar.c");
    
    jogo.telaAtual = MENU;
    jogo.tempodejogo = 0;
    
    jogador.vivo = 1;
    jogador.r = R_INICIO;
    jogador.envenenado = 0;
    
    inimigos_vivos = INIMIGOS_INICIO;
   
    jogo.tempodejogo = GetTime();
    jogo.buffer = 0;
    jogo.pausa = 0;
    //--------------------------------------------------------------------------------------
    
    SetTargetFPS(60);               // Jogo roda a 60 FPS
    
    
     // Main game loop
    while (!WindowShouldClose())    // Detecta se fecha a janela de jogo ou aperta tecla Esc
    {                
        atualizajogo();
        desenhajogo();
    }

    // Encerra
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}