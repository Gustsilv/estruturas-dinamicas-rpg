#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó que representa um personagem
struct Node {
    char nome[30];
    int hp;     // Pontos de vida
    int mp;     // Pontos de mana
    int classe; // 0: guerreiro, 1: mago
    struct Node *prox; // Ponteiro para o próximo nó
};

// Definindo um alias para simplificar o código
typedef struct Node node;

// Estrutura da lista circular simplesmente encadeada (apenas um ciclo)
struct lista {
    node *inicio; // Ponteiro para o início da lista
    int tamanho;  // Número de nós na lista
};

// Definindo um alias para simplificar a manipulação da lista
typedef struct lista LISTA;

// Funções para manipulação da lista
LISTA *lista_inicia();
void lista_insere(LISTA *lista, const char *nome, int hp, int mp, int classe);
void lista_imprime(LISTA *l);
void lista_remover(LISTA *l, const char *nome);
void lista_libera(LISTA *l);

LISTA *lista_inicia() {
    LISTA *nova_lista = (LISTA *)malloc(sizeof(LISTA));
    nova_lista->inicio = NULL;
    nova_lista->tamanho = 0; // Inicializa a lista como vazia
    return nova_lista;
}

void lista_insere(LISTA *l, const char *nome, int hp, int mp, int classe) {
    node *novo_nodo = (node *)malloc(sizeof(node));
    strcpy(novo_nodo->nome, nome);
    novo_nodo->hp = hp;
    novo_nodo->mp = mp;
    novo_nodo->classe = classe;

    if (l->tamanho == 0) {
        // Se a lista estiver vazia, o novo nó aponta para ele mesmo
        novo_nodo->prox = novo_nodo;
        l->inicio = novo_nodo;
    } else {
        // Insere o novo nó no final e ajusta o ponteiro
        node *ultimo = l->inicio;
        while (ultimo->prox != l->inicio) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo_nodo; // Último nó aponta para o novo nó
        novo_nodo->prox = l->inicio; // Novo nó aponta para o início
    }
    l->tamanho++; // Incrementa o tamanho da lista
}

void lista_imprime(LISTA *l) {
    if (l->tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }

    node *atual = l->inicio;
    do {
        printf("Nome: %s, HP: %d, MP: %d\n", atual->nome, atual->hp, atual->mp);
        atual = atual->prox;
    } while (atual != l->inicio);
}

void lista_remover(LISTA *l, const char *nome) {
    if (l->tamanho == 0) return; // Lista vazia

    node *atual = l->inicio;
    node *anterior = NULL;

    // Loop para encontrar o nó a ser removido
    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                // O nó a ser removido é o primeiro
                if (l->tamanho == 1) {
                    // Se é o único nó, a lista ficará vazia
                    free(atual);
                    l->inicio = NULL;
                } else {
                    // Ajusta o início da lista
                    node *ultimo = l->inicio;
                    while (ultimo->prox != l->inicio) {
                        ultimo = ultimo->prox;
                    }
                    l->inicio = atual->prox; // Muda o início
                    ultimo->prox = l->inicio; // Último aponta para o novo início
                    free(atual);
                }
            } else {
                // Remover um nó que não é o primeiro
                anterior->prox = atual->prox; // Conecta o anterior ao próximo
                free(atual);
            }
            l->tamanho--; // Decrementa o tamanho da lista
            return; // Sai após remover
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != l->inicio);
}

void lista_libera(LISTA *l) {
    if (l->inicio == NULL) return; // Lista vazia

    node *atual = l->inicio;
    node *proximo;

    do {
        proximo = atual->prox; // Armazena o próximo nó
        free(atual);           // Libera o nó atual
        atual = proximo;       // Move para o próximo nó
    } while (atual != l->inicio);

    free(l); // Libera a estrutura da lista
}

int main() {
    LISTA *lista = lista_inicia();

    // Inserir personagens
    lista_insere(lista, "Jogador", 100, 50, 0); // Guerreiro
    lista_insere(lista, "Inimigo1", 50, 30, 1); // Mago
    lista_insere(lista, "Inimigo2", 60, 20, 0); // Guerreiro

    // Imprimir a lista
    printf("Lista de Personagens:\n");
    lista_imprime(lista);

    // Remover um personagem
    lista_remover(lista, "Inimigo1");

    // Imprimir a lista após remoção
    printf("\nLista apos remocao:\n");
    lista_imprime(lista);

    // Liberar a memória
    lista_libera(lista);

    return 0;
}
