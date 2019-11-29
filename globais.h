//arquivo contendo variáveis globais e constantes utilizadas no jogo

//constantes:
#define MAX_INIMIGOS 100
#define INIMIGOS_INICIO 10

int LarguraTela = 1000;
int AlturaTela = 550;
Vector2 posicaojogador = { (float)LarguraTela/2, (float)AlturaTela/2 };

//structs:

typedef enum tela{
    MENU = 0,
    INSTRUCOES,
    GANHADORES
    JOGAR,
    FINAL
}TELA;

typedef struct pos{
    int x, y;
}POS,
pPOS;

typedef struct jogador{
    int estado, vivo, vmodulo;
    float r;
}JOGADOR,
pJOGADOR;

typedef struct inimigo{
    POS p;
    int idtipo, idmov, vmodulo;
    float r;
}INIMIGO,
pINIMIGO;

typedef struct jogo{
    TELA telaAtual;
    int sairjogo, jogonovo;
    double tempodejogo;    
}JOGO;

//variáveis :
JOGO jogo;
JOGADOR jogador;
INIMIGO inimigos[MAX_INIMIGOS];
int inimigos_vivos;

