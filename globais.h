//arquivo contendo variáveis globais e constantes utilizadas no jogo
#include "raylib.h"
//constantes:
#define R_INICIO 30
#define ALTURATELA 550
#define LARGURATELA 1000
#define INIMIGOS_INICIO 75
#define MAX_INIMIGOS 110
#define menuSelect 0

Vector2 posicaojogador = { (float)LARGURATELA/2, (float)ALTURATELA/2 };

//structs:

typedef enum tela{
    MENU = 0,
    INSTRUCOES,
    GANHADORES,
    JOGAR,
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
    DIRECIONADA,
    PERSEGUIDORA
}IDMOV;

typedef struct jogador{
    int envenenado, vivo;
    float r;
}JOGADOR,
pJOGADOR;

typedef struct inimigo{
    Vector2 p;
    IDTIPO tipo;
    IDMOV mov;
    int vmodulo;
    float r;
}INIMIGO,
pINIMIGO;

typedef struct jogo{
    TELA telaAtual;
    int pausa, jogonovo;
    double tempodejogo, buffer;    
}JOGO;

//variáveis :
JOGO jogo;
JOGADOR jogador;
INIMIGO inimigos[MAX_INIMIGOS];
int inimigos_vivos;

int delay = 0;

