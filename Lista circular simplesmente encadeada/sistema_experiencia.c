#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_experiencia.h"

// Função para criar um novo personagem
void criar_personagem(node **inicio, const char *nome, int hp, int mp, int poder_ataque, int poder_defesa) {
    node *novo_nodo = (node *)malloc(sizeof(node));
    strcpy(novo_nodo->nome, nome);
    novo_nodo->hp = hp;
    novo_nodo->mp = mp;
    novo_nodo->poder_ataque = poder_ataque;
    novo_nodo->poder_defesa = poder_defesa;
    novo_nodo->nivel = 1;
    novo_nodo->xp_total = 0;
    novo_nodo->xp_necessario = 100; // XP necessário para subir de nível
    novo_nodo->prox = *inicio;

    if (*inicio == NULL) {
        // Se a lista estiver vazia, o novo nó aponta para ele mesmo
        *inicio = novo_nodo;
        novo_nodo->prox = novo_nodo;
    } else {
        // Insere o novo nó no final da lista
        node *ultimo = *inicio;
        while (ultimo->prox != *inicio) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo_nodo;
    }
}

// Função para adicionar experiência ao personagem
void adicionar_experiencia(node *personagem, int xp) {
    if (personagem == NULL) return;

    personagem->xp_total += xp;

    while (personagem->xp_total >= personagem->xp_necessario) {
        personagem->xp_total -= personagem->xp_necessario;
        personagem->nivel++;

        if (personagem->nivel < 99) {
            // Aumenta os status do personagem a cada nível
            personagem->hp += (personagem->hp * 0.015); // Aumento de 1.5% em HP
            personagem->mp += (personagem->mp * 0.015); // Aumento de 1.5% em MP
            personagem->poder_ataque += (personagem->poder_ataque * 0.015); // Aumento de 1.5% em Poder de Ataque
            personagem->poder_defesa += (personagem->poder_defesa * 0.015); // Aumento de 1.5% em Poder de Defesa

            // Atualiza o XP necessário para o próximo nível
            personagem->xp_necessario += (personagem->xp_necessario * 0.3); // Aumento de 30% no XP necessário
        }
    }
}

// Função para ler e imprimir os dados do personagem
void ler_personagem(node *personagem) {
    if (personagem == NULL) return;

    printf("Nome: %s\n", personagem->nome);
    printf("Nivel: %d\n", personagem->nivel);
    printf("HP: %d\n", personagem->hp);
    printf("MP: %d\n", personagem->mp);
    printf("Poder de Ataque: %d\n", personagem->poder_ataque);
    printf("Poder de Defesa: %d\n", personagem->poder_defesa);
    printf("XP Total: %d\n", personagem->xp_total);
    printf("XP Necessário para o próximo nível: %d\n\n", personagem->xp_necessario);
}
