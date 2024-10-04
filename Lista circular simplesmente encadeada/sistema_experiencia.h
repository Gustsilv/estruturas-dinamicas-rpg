#ifndef SISTEMA_EXPERIENCIA_H
#define SISTEMA_EXPERIENCIA_H

// Estrutura do nó que representa um personagem
struct Node {
    char nome[30];
    int hp;
    int mp;
    int poder_ataque;
    int poder_defesa;
    int nivel;
    int xp_total;
    int xp_necessario;
    struct Node *prox; // Ponteiro para o próximo nó
};

// Definindo um alias para simplificar o código
typedef struct Node node;

// Funções do sistema de experiência
void criar_personagem(node **inicio, const char *nome, int hp, int mp, int poder_ataque, int poder_defesa);
void adicionar_experiencia(node *personagem, int xp);
void atualizar_status(node *personagem);
void ler_personagem(node *personagem);

#endif
