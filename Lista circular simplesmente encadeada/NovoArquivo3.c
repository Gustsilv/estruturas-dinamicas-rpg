#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do n� que representa um personagem
struct Node {
    char nome[30];
    int hp;     // Pontos de vida
    int mp;     // Pontos de mana
    int classe; // 0: guerreiro, 1: mago
    struct Node *prox; // Ponteiro para o pr�ximo n�
};

// Definindo um alias para simplificar o c�digo
typedef struct Node node;

// Ponteiro para o in�cio da lista
node *inicio = NULL;

// Fun��es para manipula��o da lista
void lista_cria(const char *nome, int hp, int mp, int classe); // Create
void lista_leitura(); // Read
void lista_atualiza(const char *nome, int novo_hp, int novo_mp); // Update
void lista_deleta(const char *nome); // Delete
void lista_libera(); // Libera mem�ria

// Fun��o para criar um novo personagem
void lista_cria(const char *nome, int hp, int mp, int classe) {
    node *novo_nodo = (node *)malloc(sizeof(node));
    strcpy(novo_nodo->nome, nome);
    novo_nodo->hp = hp;
    novo_nodo->mp = mp;
    novo_nodo->classe = classe;

    if (inicio == NULL) {
        // Se a lista estiver vazia, o novo n� aponta para ele mesmo
        novo_nodo->prox = novo_nodo;
        inicio = novo_nodo;
    } else {
        // Insere o novo n� no final e ajusta o ponteiro
        node *ultimo = inicio;
        while (ultimo->prox != inicio) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo_nodo; // �ltimo n� aponta para o novo n�
        novo_nodo->prox = inicio;  // Novo n� aponta para o in�cio
    }
}

// Fun��o para ler e imprimir todos os personagens
void lista_leitura() {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    node *atual = inicio;
    do {
        printf("Nome: %s, HP: %d, MP: %d\n", atual->nome, atual->hp, atual->mp);
        atual = atual->prox;
    } while (atual != inicio);
}

// Fun��o para atualizar HP e MP de um personagem
void lista_atualiza(const char *nome, int novo_hp, int novo_mp) {
    if (inicio == NULL) return; // Lista vazia

    node *atual = inicio;
    do {
        if (strcmp(atual->nome, nome) == 0) {
            atual->hp = novo_hp;
            atual->mp = novo_mp;
            printf("Personagem %s atualizado: HP = %d, MP = %d\n", nome, novo_hp, novo_mp);
            return; // Sai ap�s atualizar
        }
        atual = atual->prox;
    } while (atual != inicio);

    printf("Personagem %s n�o encontrado.\n", nome);
}

// Fun��o para deletar um personagem
void lista_deleta(const char *nome) {
    if (inicio == NULL) return; // Lista vazia

    node *atual = inicio;
    node *anterior = NULL;

    // Loop para encontrar o n� a ser removido
    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                // O n� a ser removido � o primeiro
                if (atual->prox == inicio) {
                    // Se � o �nico n�, a lista ficar� vazia
                    free(atual);
                    inicio = NULL;
                } else {
                    // Ajusta o in�cio da lista
                    node *ultimo = inicio;
                    while (ultimo->prox != inicio) {
                        ultimo = ultimo->prox;
                    }
                    inicio = atual->prox; // Muda o in�cio
                    ultimo->prox = inicio; // �ltimo aponta para o novo in�cio
                    free(atual);
                }
            } else {
                // Remover um n� que n�o � o primeiro
                anterior->prox = atual->prox; // Conecta o anterior ao pr�ximo
                free(atual);
            }
            printf("Personagem %s removido.\n", nome);
            return; // Sai ap�s remover
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != inicio);

    printf("Personagem %s n�o encontrado.\n", nome);
}

// Fun��o para liberar a mem�ria da lista
void lista_libera() {
    if (inicio == NULL) return; // Lista vazia

    node *atual = inicio;
    node *proximo;

    do {
        proximo = atual->prox; // Armazena o pr�ximo n�
        free(atual);           // Libera o n� atual
        atual = proximo;       // Move para o pr�ximo n�
    } while (atual != inicio);

    inicio = NULL; // Certifica-se de que o ponteiro de in�cio est� vazio
}

// Fun��o principal
int main() {
    // Criar personagens
    lista_cria("Jogador", 100, 50, 0); // Guerreiro
    lista_cria("Inimigo1", 50, 30, 1); // Mago
    lista_cria("Inimigo2", 60, 20, 0); // Guerreiro

    // Ler e imprimir a lista
    printf("Lista de Personagens:\n");
    lista_leitura();

    // Atualizar um personagem
    lista_atualiza("Jogador", 120, 70); // Atualizando HP e MP do Jogador

    // Remover um personagem
    lista_deleta("Inimigo1");

    // Ler e imprimir a lista ap�s remo��o
    printf("\nLista apos remocao:\n");
    lista_leitura();

    // Liberar a mem�ria
    lista_libera();

    return 0;
}
