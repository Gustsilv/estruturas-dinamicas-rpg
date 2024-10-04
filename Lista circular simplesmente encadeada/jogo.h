#ifndef JOGO_H
#define JOGO_H

// Definições de constantes
#define MAX_NIVEL 99
#define XP_PARA_SUBIR 100

// Estrutura para o personagem
typedef struct {
    char nome[50];
    int hp;
    int mp;
    int nivel;
    int xp;
} Jogador;

// Estrutura para os inimigos
typedef struct {
    char nome[50];
    int hp;
    int poderAtaque;
    int xpGanho;
} Inimigo;

// Estrutura para o nó da lista
typedef struct Nodo {
    Jogador jogador;
    Inimigo inimigos[2]; // Array para 2 inimigos
    struct Nodo* anterior;
    struct Nodo* proximo;
} Nodo;

// Funções de Criação
Jogador criarJogador(char* nome);
Inimigo criarInimigo(char* nome, int hp, int poderAtaque, int xpGanho);

// Funções de Manipulação da Lista
Nodo* criarNodo(Jogador jogador, Inimigo inimigos[2]);
void adicionarNodo(Nodo** inicio, Jogador jogador, Inimigo inimigos[2]);

// Funções de Combate
void atacar(Nodo* jogadorNodo, int inimigoIndex);
int usarMagia(Nodo* jogadorNodo, int inimigoIndex);
void usarItem(Nodo* jogadorNodo);
void ataqueInimigo(Nodo* jogadorNodo, Inimigo* inimigo);
void calcularXP(Nodo* jogadorNodo, Inimigo* inimigo);
void mostrarStatus(Nodo* jogadorNodo);
void combate(Nodo* jogadorNodo);

#endif // JOGO_H
