#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "globals.h"
#include "final_screen.h"
#include <math.h>

/*Still missing
- Consider whether or not poisoned are in draw_enemies
*/

/* Draw enemies according to their type. Normal enemies might be poisoned, which alters their color */
void desenha_enemies(){
    int i;
    for(i=0;i< alive_enemies;i++){
        switch(enemies[i].type){
            case 0:     
                if(!enemies[i].poisoned){
                    DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r + enemies[i].r * 0.1, NORMAL_COLOR_BORDER);     
                    DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r, NORMAL_COLOR);   
                }else{
                    DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r + enemies[i].r * 0.1, NORMAL_COLOR_BORDER);
                    DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r, NORMAL_COLOR);
                }                
            break;
            case 1:
                DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r + enemies[i].r * 0.1, POISON_GREEN_BORDER);
                DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r, POISON_GREEN);
            break;
            case 2:
                DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r + enemies[i].r * 0.1, EXPLOSIVE_COLOR_BORDER);                                
                DrawCircle(enemies[i].p.x, enemies[i].p.y, enemies[i].r, EXPLOSIVE_COLOR);
            break;           
        }
    }    
}

 
 /* Create new enemy, called periodically when alive enemies is increased and when and enemy is killed */
void createEnemy(int i){      
     
    do{
        enemies[i].p.y = GetRandomValue(-20*player.r, 20*player.r); 
    }while(abs(SCREEN_HEIGHT/2 - enemies[i].p.y) < (4*player.r)); //in order of enemies show up not too far and not too close from the player          
    do{
        enemies[i].p.x = GetRandomValue(-40*player.r, 40*player.r) ;
    }while(abs(SCREEN_WIDTH/2 - enemies[i].p.x)< (4*player.r));
    
    enemies[i].poisoned = 0;
    enemies[i].delay = 0;
    enemies[i].r = (int)floor(GetRandomValue(0.4*player.r, 1.5*player.r)); //enemy radius is proporcional to player radius
    enemies[i].type = GetRandomValue(0,2);
    enemies[i].mov = GetRandomValue(0,6);
    enemies[i].modular_velocity = 1 + 0.5*((int)floor(GetTime() - game.gameTime + game.buffer)/30); 
    //enemies modular velocity is (1 + 50% of the number of 30s already played)
}


/* Checks if any collisions are happening between player/enemies and enemies/enemies */
void collisions(){        
    int i, j;
    for(i=0;i<alive_enemies;i++){
        if(abs(player_position.x - enemies[i].p.x)< 3*player.r || abs(player_position.y - enemies[i].p.y)< 3*player.r){  
            if(CheckCollisionCircles(player_position, player.r, enemies[i].p, enemies[i].r)){
                if(player.r<enemies[i].r || enemies[i].type == EXPLOSIVE) //collisions with explosive enemies end the game
                    player.alive = 0;
                else{
                    if(!player.poisoned){
                        if(enemies[i].type == POISONOUS){ 
                            player.poisoned = 1;
                            player.delay = GetTime();
                        }        
                        player.r += (enemies[i].r/10); 
                        createEnemy(i);  
                    }                    
                }
            }
        }
        
        for(j=0;j<alive_enemies;j++){  
            if(j!= i){
                if(abs(enemies[j].p.x - enemies[i].p.x)< 3*enemies[i].r || abs(enemies[j].p.x - enemies[i].p.y)< 3*enemies[i].r)
                    if(CheckCollisionCircles(enemies[j].p, enemies[j].r, enemies[i].p, enemies[i].r)){
                        if(enemies[j].type == EXPLOSIVE || enemies[i].type == EXPLOSIVE){ 
                            createEnemy(i);  
                            createEnemy(j);
                        }
                        else if(enemies[i].r<enemies[j].r && !enemies[j].poisoned)    
                            createEnemy(i);
                        else if(enemies[i].r>=enemies[j].r && !enemies[i].poisoned){     
                            if(enemies[j].type == POISONOUS && enemies[i].type != POISONOUS){     
                                enemies[i].poisoned = 1;
                                enemies[i].delay = GetTime();
                            }
                            enemies[i].r += (enemies[j].r/10);      
                            createEnemy(j);   
                        }
                    }                
            }
        }        
    }
}


/* Checks whether the player and the enemies are poisoned, causing the poison effect when true*/
void passa_veneno(){
    int i;
    if(player.poisoned){ 
            if(GetTime() - player.delay > 3){ //effect fades after 3s
                player.poisoned = 0;
            }
    }
    for(i=0;i<alive_enemies;i++){
        if(enemies[i].poisoned){  
            if(GetTime() - enemies[i].delay > 3){  
                enemies[i].poisoned = 0;
            }
        }
    }
}

/* Moves enemies according to their type. Static enemies do not move */
void move_enemies(){
    
    int i;
    
    for(i=0;i<alive_enemies;i++){
        switch(enemies[i].mov){
            case(RANDOM):{
                switch((int)floor(GetRandomValue(1, 5))){
                    case 1:
                    case 5:
                    enemies[i].p.x += enemies[i].modular_velocity;
                    break;
                    case 2:
                        enemies[i].p.y += enemies[i].modular_velocity;
                    break;
                    case 3:
                        enemies[i].p.x -= enemies[i].modular_velocity;
                    break;
                    case 4:
                        enemies[i].p.y -= enemies[i].modular_velocity;
                    break;
                }    
            }break;
            case(TARGETED_N):{
                enemies[i].p.y -= enemies[i].modular_velocity; 
            }break;
            case(TARGETED_S):{
                enemies[i].p.y += enemies[i].modular_velocity;
            }break;
            case(TARGETED_L):{
                enemies[i].p.x += enemies[i].modular_velocity;
            }break;
            case(TARGETED_O):{
                enemies[i].p.x -= enemies[i].modular_velocity; 
            }break;
            case(CHASER):{
                
                if(enemies[i].p.x < player_position.x)
                    enemies[i].p.x += enemies[i].modular_velocity;
                else
                    enemies[i].p.x -= enemies[i].modular_velocity;
                
                if(enemies[i].p.y < player_position.y)
                    enemies[i].p.y += enemies[i].modular_velocity;
                else
                    enemies[i].p.y -= enemies[i].modular_velocity;
            }break;            
        }
    }
    
}

/* Draw pause menu */
void desenha_pause(){
    DrawRectangleGradientV(250, 150, 500, 250, RED, LIGHTGRAY);
    DrawRectangleLines(250, 150, 500, 250, BLACK);

    DrawText("Paused Game!", SCREEN_WIDTH/2 - MeasureText("Paused Game!", 25)/2, 160, 25, WHITE);
    DrawText("- S (Save)", SCREEN_WIDTH/2 - MeasureText("- S (Save)", 17)/2, 210, 17, WHITE);
    DrawText("- ENTER (Pause)", SCREEN_WIDTH/2 - MeasureText("- ENTER (Pause)", 17)/2, 260, 17, WHITE);
    DrawText("- M (Back to Menu)", SCREEN_WIDTH/2 - MeasureText("- M (Back to Menu)", 17)/2, 310, 17, WHITE);
    DrawText("- ESC (Leave Game)", SCREEN_WIDTH/2 - MeasureText("- ESC (Leave Game)", 17)/2, 360, 17, WHITE);
}

/* Saves the current state of the game */
void salva_game(){
    FILE *arquivo;
    if(!(arquivo = fopen("meu_agario.bin","wb")))
        DrawText("Error in opening file", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 25, WHITE); 
    else {   
        fwrite(&game, sizeof(GAME),1,arquivo);
    
        fwrite(&player, sizeof(PLAYER),1,arquivo);
    
        fwrite(&alive_enemies, sizeof(int),1,arquivo);
        
        fwrite(enemies, sizeof(ENEMY), alive_enemies, arquivo);
    }

    fclose(arquivo); 
}

/* A grid for better perspective of the player in the screen */
void makeGrid()
{
    int i;
    for(i = 0; i < SCREEN_HEIGHT; i += SCREEN_HEIGHT/10){
        DrawLineEx((Vector2){0,i}, (Vector2){SCREEN_WIDTH,i}, 1, GRID_COLOR);   
    }
    for(i = 0; i < SCREEN_WIDTH; i += SCREEN_WIDTH/15){
        DrawLineEx((Vector2){i,0}, (Vector2){i,SCREEN_HEIGHT}, 1, GRID_COLOR);   
    }

}

void updateScreen(){
    
    if(IsKeyPressed(KEY_ENTER)){
        if(!game.pause){        
            game.pause = 1;
            game.buffer += GetTime() - game.gameTime; //Stores in buffer the time already played
        }
        else{
            game.pause = 0;
            game.gameTime = GetTime();  //Continues game from where it stoped and
        }              
    }
    
    if(game.pause){  
        if(IsKeyPressed(KEY_S))
            salva_game();
        if(IsKeyPressed(KEY_M))
            game.currentScreen = MENU;
    }
    
    
    else if(player.alive && !game.pause){
        int i;        
               
        if(IsKeyDown(KEY_RIGHT)){      
            for(i=0;i<alive_enemies;i++){
                enemies[i].p.x -= player.v;
                if(enemies[i].p.x < -2*SCREEN_WIDTH) //reposition enemies that are to far
                    createEnemy(i);                    
            } 
        }        
        
        if(IsKeyDown(KEY_LEFT)){      
            for(i=0;i<alive_enemies;i++){
                enemies[i].p.x += player.v;
                if(enemies[i].p.x > 2*SCREEN_WIDTH)    
                    createEnemy(i);
                } 
        }
                
        if(IsKeyDown(KEY_UP)){   
            for(i=0;i<alive_enemies;i++){
                enemies[i].p.y += player.v;
                if(enemies[i].p.y > 2*SCREEN_HEIGHT)     
                    createEnemy(i);
            } 
        }
                
        if(IsKeyDown(KEY_DOWN)){   
            for(i=0;i<alive_enemies;i++){
                enemies[i].p.y -= player.v;
                if(enemies[i].p.y < -2*SCREEN_HEIGHT)     
                    createEnemy(i);
            } 
        }
        
        collisions();         
        //Creates a new enemy every 30s, while the number of enemies is not MAX_ENEMIES
        if((GetTime() - game.gameTime + game.buffer) - game.create_new > 30){        
            if(alive_enemies < MAX_ENEMIES){
                createEnemy(alive_enemies);
                alive_enemies++;
            }                
                       
            game.create_new = GetTime();
        }
        
        passa_veneno();
                
        move_enemies();
        //player modular velocity is (3 + 50% of the number of 30s already played)
        player.v = 3 + 0.5*((int)floor(GetTime() - game.gameTime + game.buffer)/30); 
        
    }  
    else if(!player.alive){
        game.currentScreen = FINAL;
        resetFinalVariables();
        game.gameTime = GetTime() - game.gameTime + game.buffer;
        setFinalVariables();
    }
}

void drawGame(){
    BeginDrawing();
               
    ClearBackground(RAYWHITE);

    makeGrid();

    if(!player.poisoned){
        DrawCircle(player_position.x, player_position.y, player.r + player.r * 0.1, PLAYER_COLOR_BORDER);
        DrawCircleV(player_position, player.r, PLAYER_COLOR);
    }else{
        DrawCircle(player_position.x, player_position.y, player.r + player.r * 0.1, PLAYER_POISONED_COLOR_BORDER);
        DrawCircleV(player_position, player.r, PLAYER_POISONED_COLOR);
    }        
            
    desenha_enemies();
    
    if(game.pause)
            desenha_pause();
    else
        DrawText(FormatText("Score : %2.0f", GetTime() - game.gameTime + game.buffer), 880, 525, 20, BLACK);
        
    EndDrawing();
}
