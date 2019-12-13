#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "globais.h"
#include <math.h>
/*FALTA:
- Considerar se inimigos estão envenenados na desenha_inimigos
- Carregar jogo (Menu). Obs: quando carregar, jogo.buffer tem que ser igual ao jogo.tempodejogo armazenado, e jogo.tempodejogo = GetTime
- Conferir variáveis
- ?
*/

void desenha_inimigos(){
    int i;
    for(i=0;i<inimigos_vivos;i++){
        switch(inimigos[i].tipo){
            case 0:     //CONSIDERAR, PARA CADA INIMIGO, O CASO DELE ESTAR ENVENENADO, EM FUNÇÃO DO DELAY 
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r + inimigos[i].r * 0.1, NORMAL_COLOR_BORDER);
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, NORMAL_COLOR);
            break;
            case 1:
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r + inimigos[i].r * 0.1, POISON_GREEN_BORDER);
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, POISON_GREEN);
            break;
            case 2:
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r + inimigos[i].r * 0.1, EXPLOSIVE_COLOR_BORDER);                                
                DrawCircle(inimigos[i].p.x, inimigos[i].p.y, inimigos[i].r, EXPLOSIVE_COLOR);
            break;           
        }
    }    
}


void cria_inimigo(int i){       //Cria novo inimigo, chamada periodicamente e um inimigo é consumido

    do{
        inimigos[i].p.y = GetRandomValue(-20*jogador.r, 20*jogador.r);
    }while(abs(ALTURATELA/2 - inimigos[i].p.y) < (4*jogador.r));
    do{
        inimigos[i].p.x = GetRandomValue(-40*jogador.r, 40*jogador.r) ;
    }while(abs(LARGURATELA/2 - inimigos[i].p.x)< (4*jogador.r));
    
    inimigos[i].envenenado = 0;
    inimigos[i].delay = 0;
    inimigos[i].r = (int)floor(GetRandomValue(0.4*jogador.r, 1.5*jogador.r)); //Seta o raio do inimigo proporcional ao raio atual do Jogador
    inimigos[i].tipo = GetRandomValue(0,2);
    inimigos[i].mov = GetRandomValue(0,6);
    inimigos[i].vmodulo = 1 + 0.5*((int)floor(GetTime() - jogo.tempodejogo + jogo.buffer)/30); 
    //a velocidade modulo (vmodulo) dos inimigos criados é (1 + 0,5*n), onde n é o piso do número de períodos de 30s que já foram jogados
}


void colisoes(){        
    int i, j;
    for(i=0;i<inimigos_vivos;i++){
        if(abs(posicaojogador.x - inimigos[i].p.x)< 3*jogador.r || abs(posicaojogador.y - inimigos[i].p.y)< 3*jogador.r){     //verifica, para os inimigos que estão proximos do jogador, se há alguma colisão
            if(CheckCollisionCircles(posicaojogador, jogador.r, inimigos[i].p, inimigos[i].r)){
                if(jogador.r<inimigos[i].r || inimigos[i].tipo == EXPLOSIVA)
                    jogador.vivo = 0;
                else{
                    if(!jogador.envenenado){
                        if(inimigos[i].tipo == VENENOSA){       //se jogador come um inimigo venenoso, é envenenado
                            jogador.envenenado = 1;
                            jogador.delay = GetTime();
                        }        
                        jogador.r += (inimigos[i].r/10);      //aumenta raio do jogador proporcionalmente à peça que ele comeu
                        cria_inimigo(i);
                    }                    
                }
            }
        }
        
        for(j=0;j<inimigos_vivos;j++){      //verifica se há alguma colisão entre dois inimigos próximos 
            if(j!= i){
                if(abs(inimigos[j].p.x - inimigos[i].p.x)< 3*inimigos[i].r || abs(inimigos[j].p.x - inimigos[i].p.y)< 3*inimigos[i].r)
                    if(CheckCollisionCircles(inimigos[j].p, inimigos[j].r, inimigos[i].p, inimigos[i].r)){
                        if(inimigos[j].tipo == EXPLOSIVA || inimigos[i].tipo == EXPLOSIVA){
                            cria_inimigo(i);
                            cria_inimigo(j);
                        }
                        else if(inimigos[i].r<inimigos[j].r && !inimigos[j].envenenado)
                            cria_inimigo(i);
                        else if(!inimigos[i].envenenado){
                            if(inimigos[j].tipo == VENENOSA){       //se um inimigo come um inimigo venenoso, é envenenado
                                inimigos[i].envenenado = 1;
                                inimigos[i].delay = GetTime();
                            }
                            inimigos[i].r += (inimigos[j].r/10);
                            cria_inimigo(j);
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
    DrawRectangleGradientV(250, 150, 500, 250, RED, LIGHTGRAY);
    DrawRectangleLines(250, 150, 500, 250, BLACK);

    DrawText("Jogo Pausado!", LARGURATELA/2 - MeasureText("Jogo Pausado!", 25)/2, 160, 25, WHITE);
    DrawText("- S (Salvar)", LARGURATELA/2 - MeasureText("- S (Salvar)", 17)/2, 210, 17, WHITE);
    DrawText("- ENTER (Pausar)", LARGURATELA/2 - MeasureText("- ENTER (Pausar)", 17)/2, 260, 17, WHITE);
    DrawText("- M (Voltar ao Menu)", LARGURATELA/2 - MeasureText("- M (Voltar ao Menu)", 17)/2, 310, 17, WHITE);
    DrawText("- ESC (Sair do jogo)", LARGURATELA/2 - MeasureText("- ESC (Sair do jogo)", 17)/2, 360, 17, WHITE);
}

void salva_jogo(){
    FILE *arquivo;
    if(!(arquivo = fopen("meu_agario.bin","wb")))
        DrawText("Erro ao abrir arquivo", LARGURATELA/2, ALTURATELA/2, 25, WHITE);     //Informa erro na abertura de arquivo, caso aconteça
    else {   
        fwrite(&jogo, sizeof(JOGO),1,arquivo);
    
        fwrite(&jogador, sizeof(JOGADOR),1,arquivo);
    
        fwrite(&inimigos_vivos, sizeof(int),1,arquivo);
        
        fwrite(inimigos, sizeof(INIMIGO), inimigos_vivos, arquivo);
    }

    fclose(arquivo);        //Fecha arquivo
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
            salva_jogo();
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
        
        if((GetTime() - jogo.tempodejogo + jogo.buffer) - jogo.cria_novos > 30){        //Cria um inimigo novo a cada 30s de jogo, enquanto não houverem MAX_INIMIGOS
            if(inimigos_vivos < MAX_INIMIGOS){
                cria_inimigo(inimigos_vivos);
                inimigos_vivos++;
            }                
            for(i=0;i<5;i++)
                cria_inimigo(GetRandomValue(0,inimigos_vivos));            
            jogo.cria_novos = GetTime();
        }
        
        if(jogador.envenenado){     //se jogador está envenenado
            if(GetTime() - jogador.delay > 3){     //quando se passam 3s desde que foi envenenado, passa o veneno
                jogador.envenenado = 0;
            }
        }
        
        move_inimigos();
        
        jogador.v = 3 + 0.5*((int)floor(GetTime() - jogo.tempodejogo + jogo.buffer)/30);        //a velocidade modulo (vmodulo) do jogador é (3 + 0,5*n), onde n é o piso do número de períodos de 30s que já foram jogados
                
        
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

void makeGrid()
{
    int i;
    for(i = 0; i < ALTURATELA; i += ALTURATELA/10){
        DrawLineEx((Vector2){0,i}, (Vector2){LARGURATELA,i}, 1, GRID_COLOR);   
    }
    for(i = 0; i < LARGURATELA; i += LARGURATELA/15){
        DrawLineEx((Vector2){i,0}, (Vector2){i,ALTURATELA}, 1, GRID_COLOR);   
    }

}

void desenhajogo(){
    BeginDrawing();
               
    ClearBackground(RAYWHITE);

    makeGrid();

    if(!jogador.envenenado){
        DrawCircle(posicaojogador.x, posicaojogador.y, jogador.r + jogador.r * 0.1, PLAYER_COLOR_BORDER);
        DrawCircleV(posicaojogador, jogador.r, PLAYER_COLOR);
    }else{
        DrawCircle(posicaojogador.x, posicaojogador.y, jogador.r + jogador.r * 0.1, PLAYER_POISONED_COLOR_BORDER);
        DrawCircleV(posicaojogador, jogador.r, PLAYER_POISONED_COLOR);
    }
        
    /*if(conta_zoom){
        DrawText("O mundo esta ficando pequeno para voce!", 250, 125, 25, BLACK);
        DrawText("(Zoom out)", 430, 160, 20, BLACK);
    }*/
        
    desenha_inimigos();
    if(jogo.pausa)
            desenha_pausa();
    else
        DrawText(FormatText("Score : %2.0f", GetTime() - jogo.tempodejogo + jogo.buffer), 880, 525, 20, BLACK);
        
    EndDrawing();
}
