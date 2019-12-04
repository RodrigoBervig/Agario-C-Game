#include<stdio.h>
#include<stdlib.h>
#include "raylib.h"
#include "globais.h"
#include<math.h>
/*FALTA:
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

    do{
        inimigos[i].p.y = GetRandomValue(-20*jogador.r, 20*jogador.r);
    }while(abs(275 - inimigos[i].p.y)< 4*jogador.r && !CheckCollisionCircles(inimigos[i-1].p, inimigos[i-1].r, inimigos[i].p, inimigos[i].r));
    do{
        inimigos[i].p.x = GetRandomValue(-40*jogador.r, 40*jogador.r) ;
    }while(abs(500 - inimigos[i].p.x)< 4*jogador.r && !CheckCollisionCircles(inimigos[i-1].p, inimigos[i-1].r, inimigos[i].p, inimigos[i].r));    
    
    inimigos[i].r = (int)floor(GetRandomValue(0.4*jogador.r, 1.5*jogador.r));
    inimigos[i].tipo = GetRandomValue(0,2);
    inimigos[i].mov = GetRandomValue(0,6);
    inimigos[i].vmodulo = 1 + 0.5*((int)floor(GetTime() - jogo.tempodejogo + jogo.buffer)/30)
;      //o vmodulo dos inimigos criados é 2 + n, onde n é o piso do número de períodos de 20s que já foram jogados

}


void colisoes(){        //verifica se há alguma colisão entre o jogador e outro inimigo
    int i;
    for(i=0;i<inimigos_vivos;i++){
        if(abs(posicaojogador.x - inimigos[i].p.x)< 3*jogador.r || abs(posicaojogador.y - inimigos[i].p.y)< 3*jogador.r){     //verifica apenas para os inimigos que estão proximos do jogador
            if(CheckCollisionCircles(posicaojogador, jogador.r, inimigos[i].p, inimigos[i].r)){
                if(jogador.r<inimigos[i].r || inimigos[i].tipo == EXPLOSIVA)
                    jogador.vivo = 0;
                else{
                    if(!jogador.envenenado){
                        if(inimigos[i].tipo == VENENOSA){       //se jogador come um inimigo venenoso, é envenenado
                            jogador.envenenado = 1;
                            delay = GetTime();
                        }        
                        jogador.r += (inimigos[i].r/10);      //aumenta raio do jogador proporcionalmente à peça que ele comeu
                        cria_inimigo(i);
                    }                    
                }
            }
        }        
    }
}

void move_inimigos(){
    
    int i;
    
    for(i=0;i<inimigos_vivos;i++){
        switch(inimigos[i].mov){
            case(ALEATORIA):{
                switch((int)floor(GetRandomValue(1, 4))){
                    case 1:
                    inimigos[i].p.x += inimigos[i].vmodulo;
                    break;
                    case 2:
                        inimigos[i].p.y += inimigos[i].vmodulo;
                    break;
                    case 3:
                        inimigos[i].p.x -= inimigos[i].vmodulo;
                    break;
                    case 4:
                        inimigos[i].p.y -= inimigos[i].vmodulo;
                    break;
                }    
            }break;
            case(DIRECIONADA_N):{
                inimigos[i].p.y -= inimigos[i].vmodulo; 
            }break;
            case(DIRECIONADA_S):{
                inimigos[i].p.y += inimigos[i].vmodulo;
            }break;
            case(DIRECIONADA_L):{
                inimigos[i].p.x += inimigos[i].vmodulo;
            }break;
            case(DIRECIONADA_O):{
                inimigos[i].p.x -= inimigos[i].vmodulo; 
            }break;
            case(PERSEGUIDORA):{
                
                if(inimigos[i].p.x < posicaojogador.x)
                    inimigos[i].p.x += inimigos[i].vmodulo;
                else
                    inimigos[i].p.x -= inimigos[i].vmodulo;
                
                if(inimigos[i].p.y < posicaojogador.y)
                    inimigos[i].p.y += inimigos[i].vmodulo;
                else
                    inimigos[i].p.y -= inimigos[i].vmodulo;
            }break;            
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
        //double tzoom = 0;
        
        if(IsKeyDown(KEY_RIGHT)){       //movimenta jogo, se usuário aperta RIGHT
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.x -= jogador.v;
                if(inimigos[i].p.x < -2*LARGURATELA)        //reposiciona inimigos que ficarem longe demais
                    cria_inimigo(i);                    
            } 
        }
        
        
        if(IsKeyDown(KEY_LEFT)){        //movimenta jogo, se usuário aperta LEFT
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.x += jogador.v;
                if(inimigos[i].p.x > 2*LARGURATELA)     //reposiciona inimigos que ficarem longe demais
                    cria_inimigo(i);
                } 
        }
        
        
        if(IsKeyDown(KEY_UP)){      //movimenta jogo, se usuário aperta UP
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.y += jogador.v;
                if(inimigos[i].p.y > 2*ALTURATELA)      //reposiciona inimigos que ficarem longe demais
                    cria_inimigo(i);
            } 
        }
        
        
        if(IsKeyDown(KEY_DOWN)){        //movimenta jogo, se usuário aperta DOWN
            for(i=0;i<inimigos_vivos;i++){
                inimigos[i].p.y -= jogador.v;
                if(inimigos[i].p.y < -2*ALTURATELA)         //reposiciona inimigos que ficarem longe demais
                    cria_inimigo(i);
            } 
        }
        
        colisoes();         //verifica se jogador colidiu com algum inimigo
        
        if((GetTime() - jogo.tempodejogo + jogo.buffer) - cria_novos > 30){        //Cria um inimigo novo a cada 30s de jogo, enquanto não houverem MAX_INIMIGOS
            if(inimigos_vivos < MAX_INIMIGOS){
                cria_inimigo(inimigos_vivos);
                inimigos_vivos++;
            }                
            for(i=0;i<5;i++)
                cria_inimigo(GetRandomValue(0,inimigos_vivos));            
            cria_novos = GetTime();
        }
        
        if(jogador.envenenado){     //se jogador está envenenado
            if(GetTime() - delay > 3){     //quando se passam 3s desde que foi envenenado, passa o veneno e zera delay
                jogador.envenenado = 0;
            }
        }
        
        move_inimigos();
        
        jogador.v = 3 + 0.5*((int)floor(GetTime() - jogo.tempodejogo + jogo.buffer)/30);
        
        /*if(!((int)(GetTime() - jogo.tempodejogo + jogo.buffer)%30))     //Para aumentar v do jogador com o passar do tempo
            aumenta_v = 1;
        
        if(aumenta_v){
            jogador.v += 0.5;
            aumenta_v = 0;
            printf("%f", jogador.v);
        }*/
        
            
        
        /*if(jogador.r > 120){            
            conta_zoom = 1;
            tzoom = GetTime();         
        }
        
        if(conta_zoom){
            if(((GetTime() - tzoom) == 1)){
                for(i=0;i<inimigos_vivos;i++)
                    inimigos[i].r -= 30;
                jogador.r -= 30;
                
                conta_zoom++;
                if(conta_zoom = 4)
                    conta_zoom = 0;
                tzoom = GetTime();
            }            
        }*/           
        
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
        
        /*if(conta_zoom){
            DrawText("O mundo esta ficando pequeno para voce!", 250, 125, 25, BLACK);
            DrawText("(Zoom out)", 430, 160, 20, BLACK);
        }*/
        
        desenha_inimigos();
        if(jogo.pausa)
            desenha_pausa();
        else
            DrawText(FormatText("Score : %2.0f", GetTime() - jogo.tempodejogo + jogo.buffer), 910, 525, 15, BLACK);
        
     EndDrawing();
        //----------------------------------------------------------------------------------
    
}

int main(){
     // Inicializa
    //--------------------------------------------------------------------------------------
        
    InitWindow(LARGURATELA, ALTURATELA, "agario.c");
    
    jogo.telaAtual = MENU;      //inicializar telaatual do jogo como menu
    
    //--------------------------------------------------------------------------------------
    
    SetTargetFPS(60);               // Jogo roda a 60 FPS
    
    jogo.telaAtual = JOGAR;
    jogo.tempodejogo = 0;
    
    jogador.vivo = 1;
    jogador.r = R_INICIO;
    jogador.envenenado = 0;
    jogador.v = 2.5;
    
    inimigos_vivos = INIMIGOS_INICIO;
    int i;
    for(i=0;i<inimigos_vivos;i++){
        cria_inimigo(i);
    }
    
    cria_novos = GetTime();
    
    jogo.tempodejogo = GetTime();
    jogo.buffer = 0;
    jogo.pausa = 0;
    
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
