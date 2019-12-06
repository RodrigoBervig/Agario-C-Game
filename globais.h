//arquivo contendo variáveis globais e constantes utilizadas no jogo
#include "raylib.h"
//constantes:
#define R_INICIO 30
#define ALTURATELA 550
#define LARGURATELA 1000
#define INIMIGOS_INICIO 25
#define MAX_INIMIGOS 50

/*COLORS*/
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

//structs:

typedef enum tela{
    MENU = 0,
    INSTRUCOES,
    GANHADORES,
    JOGAR,
    CARREGAR,
    FINAL
}TELA;

typedef enum idtipo{
    NORMAL = 0,       //BLUE = NORMAL
    VENENOSA,       //LIME = VENENOSA
    EXPLOSIVA       //BLACK = EXPLOSIVA
}IDTIPO;

typedef enum idmov{
    ESTATICA = 0,
    ALEATORIA,
    DIRECIONADA_N,
    DIRECIONADA_S,
    DIRECIONADA_L,
    DIRECIONADA_O,
    PERSEGUIDORA
}IDMOV;

typedef struct jogador{
    int envenenado, vivo, delay;
    float r, v;
}JOGADOR,
pJOGADOR;

typedef struct inimigo{
    Vector2 p;
    IDTIPO tipo;
    IDMOV mov;
    int envenenado, delay;
    float vmodulo;
    float r;
}INIMIGO,
pINIMIGO;

typedef struct jogo{
    TELA telaAtual;
    int pausa, jogonovo, cria_novos;
    double tempodejogo, buffer;    
}JOGO;

//variáveis :
JOGO jogo;
JOGADOR jogador;
INIMIGO inimigos[MAX_INIMIGOS];
int inimigos_vivos;

static int menuSelected = 0;
static Vector2 posicaojogador = { (float)LARGURATELA/2, (float)ALTURATELA/2 };

//int conta_zoom = 0;

