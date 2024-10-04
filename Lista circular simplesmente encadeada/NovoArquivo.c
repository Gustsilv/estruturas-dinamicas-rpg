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

// Estrutura da lista circular simplesmente encadeada (apenas um ciclo)
struct lista {
    node *inicio; // Ponteiro para o in�cio da lista
    int tamanho;  // N�mero de n�s na lista
};

// Definindo um alias para simplificar a manipula��o da lista
typedef struct lista LISTA;

// Fun��es para manipula��o da lista
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
        // Se a lista estiver vazia, o novo n� aponta para ele mesmo
        novo_nodo->prox = novo_nodo;
        l->inicio = novo_nodo;
    } else {
        // Insere o novo n� no final e ajusta o ponteiro
        node *ultimo = l->inicio;
        while (ultimo->prox != l->inicio) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo_nodo; // �ltimo n� aponta para o novo n�
        novo_nodo->prox = l->inicio; // Novo n� aponta para o in�cio
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

    // Loop para encontrar o n� a ser removido
    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                // O n� a ser removido � o primeiro
                if (l->tamanho == 1) {
                    // Se � o �nico n�, a lista ficar� vazia
                    free(atual);
                    l->inicio = NULL;
                } else {
                    // Ajusta o in�cio da lista
                    node *ultimo = l->inicio;
                    while (ultimo->prox != l->inicio) {
                        ultimo = ultimo->prox;
                    }
                    l->inicio = atual->prox; // Muda o in�cio
                    ultimo->prox = l->inicio; // �ltimo aponta para o novo in�cio
                    free(atual);
                }
            } else {
                // Remover um n� que n�o � o primeiro
                anterior->prox = atual->prox; // Conecta o anterior ao pr�ximo
                free(atual);
            }
            l->tamanho--; // Decrementa o tamanho da lista
            return; // Sai ap�s remover
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
        proximo = atual->prox; // Armazena o pr�ximo n�
        free(atual);           // Libera o n� atual
        atual = proximo;       // Move para o pr�ximo n�
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

    // Imprimir a lista ap�s remo��o
    printf("\nLista apos remocao:\n");
    lista_imprime(lista);

    // Liberar a mem�ria
    lista_libera(lista);

    return 0;
}
