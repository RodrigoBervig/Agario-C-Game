
//file containing global variables and constants used in the game
#include "raylib.h"

#define INITIAL_RADIUS 30
#define SCREEN_HEIGHT 550
#define SCREEN_WIDTH 1000
#define INITIAL_ENEMIES 25
#define MAX_ENEMIES 50
#define MAX_INPUT_CHARS 17

//Colors of pieces
#define POISON_GREEN CLITERAL(Color){115,222,73,255}
#define POISON_GREEN_BORDER CLITERAL(Color){52,185,0,200}

#define PLAYER_COLOR CLITERAL(Color){251,60,60,255}
#define PLAYER_COLOR_BORDER CLITERAL(Color){217,9,9,200}

#define EXPLOSIVE_COLOR CLITERAL(Color){30,30,30,255}
#define EXPLOSIVE_COLOR_BORDER CLITERAL(Color){198,1,23,200}

#define NORMAL_COLOR CLITERAL(Color){0,120,255,255}
#define NORMAL_COLOR_BORDER CLITERAL(Color){0,94,200,255}

#define PLAYER_POISONED_COLOR CLITERAL(Color){176,0,234,255}
#define PLAYER_POISONED_COLOR_BORDER CLITERAL(Color){148,120,197,255}

#define GRID_COLOR CLITERAL(Color){200, 200, 200, 150}
#define MAX_HIGHSCORES 5

typedef enum screen{
    MENU = 0,
    INSTRUCTIONS,
    WINNERS,
    PLAY,
    LOAD,
    FINAL
}SCREEN;

typedef enum type_id{
    NORMAL = 0,       
    POISONOUS,       
    EXPLOSIVE       
}TYPE_ID;

typedef enum idmov{
    STATIC = 0,
    RANDOM,
    TARGETED_N,
    TARGETED_S,
    TARGETED_L,
    TARGETED_O,
    CHASER
}IDMOV;

typedef struct player{
    int poisoned, alive, delay;
    float r, v;
}PLAYER,
pPLAYER;

typedef struct enemy{
    Vector2 p;
    TYPE_ID type;
    IDMOV mov;
    int poisoned, delay;
    float modular_velocity;
    float r;
}ENEMY,
pENEMY;

typedef struct game{
    SCREEN currentScreen;
    int pause, newGame, create_new;
    double gameTime, buffer;    
}GAME;

typedef struct ganhador{
    char name[19];
    char score[10];
}WINNER;

GAME game;
PLAYER player;
ENEMY enemies[MAX_ENEMIES];
int alive_enemies;

WINNER winners[5];

static int menuSelected = 0;
static Vector2 player_position = { (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2 };
static int framesCounter = 0;
static char name[MAX_INPUT_CHARS + 1] = "\0"; 
static int letterCount = 0;
static char score[10] = "\0";
static char messageScore[50] = "\0";
