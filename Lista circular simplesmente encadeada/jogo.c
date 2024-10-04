#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

// Funções de Criação
Jogador criarJogador(char* nome) {
    Jogador jogador;
    strcpy(jogador.nome, nome);
    jogador.hp = 100;
    jogador.mp = 50;
    jogador.nivel = 1;
    jogador.xp = 0;
    return jogador;
}

Inimigo criarInimigo(char* nome, int hp, int poderAtaque, int xpGanho) {
    Inimigo inimigo;
    strcpy(inimigo.nome, nome);
    inimigo.hp = hp;
    inimigo.poderAtaque = poderAtaque;
    inimigo.xpGanho = xpGanho;
    return inimigo;
}

// Funções de Manipulação da Lista
Nodo* criarNodo(Jogador jogador, Inimigo inimigos[2]) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->jogador = jogador;
    novoNodo->inimigos[0] = inimigos[0];
    novoNodo->inimigos[1] = inimigos[1];
    novoNodo->anterior = NULL;
    novoNodo->proximo = NULL;
    return novoNodo;
}

void adicionarNodo(Nodo** inicio, Jogador jogador, Inimigo inimigos[2]) {
    Nodo* novoNodo = criarNodo(jogador, inimigos);
    if (*inicio == NULL) {
        *inicio = novoNodo;
        novoNodo->anterior = novoNodo;
        novoNodo->proximo = novoNodo;
    } else {
        Nodo* ultimo = (*inicio)->anterior;
        ultimo->proximo = novoNodo;
        novoNodo->anterior = ultimo;
        novoNodo->proximo = *inicio;
        (*inicio)->anterior = novoNodo;
    }
}

// Funções de Combate (definições anteriores omitidas)
void atacar(Nodo* jogadorNodo, int inimigoIndex) {
    printf("%s atacou %s e causou 10 de dano!\n", jogadorNodo->jogador.nome, jogadorNodo->inimigos[inimigoIndex].nome);
    jogadorNodo->inimigos[inimigoIndex].hp -= 10; // Dano fixo de 10
    if (jogadorNodo->inimigos[inimigoIndex].hp < 0) {
        jogadorNodo->inimigos[inimigoIndex].hp = 0; // Prevenir HP negativo
    }
}

// ... [Outras funções de combate e a função principal]

int main() {
    Nodo* jogadorNodo = NULL;

    // Criar jogador e inimigos
    Jogador jogador = criarJogador("Lira Valen");
    Inimigo inimigos[2];
    inimigos[0] = criarInimigo("Goblin", 30, 5, 50);
    inimigos[1] = criarInimigo("Esqueleto", 40, 7, 70);

    // Adicionar jogador e inimigos à lista
    adicionarNodo(&jogadorNodo, jogador, inimigos);

    // Iniciar combate
    combate(jogadorNodo);

    // Liberar memória
    free(jogadorNodo);

    return 0;
}
