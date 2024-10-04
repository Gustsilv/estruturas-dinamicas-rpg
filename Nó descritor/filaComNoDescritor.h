#ifndef FILACOMNODESCRITOR_H
#define FILACOMNODESCRITOR_H

// Estrutura que representa os dados que serão armazenados nos nós da lista
typedef struct {
    char nome[100];
    char descricao[300];
    int dropaItem; //0 para não e 1 para sim
    int temMonstro; //0 para não e 1 para sim
    int recuperaStatus; //0 para não e 1 para sim
} Dados;

// Estrutura que representa um nó da lista encadeada
typedef struct No {
    Dados dados; // Dados contidos no nó
    struct No* prox; // Ponteiro para o próximo nó na lista
} No;

// Estrutura que atua como descritor da lista encadeada
typedef struct {
    int tamanho; // Quantidade de nós ativos na lista
    No* primeiro; // Ponteiro para o primeiro nó (cabeça da lista)
    No* ultimo; // Ponteiro para o último nó (cauda da lista)
} No_descritor;

// função para inicializar dados;
Dados constructor(char nome[], char descricao[], int dropaItem, int temMonstro, int recuperaStatus);

// Função para inicializar a lista
void cria_lista(No_descritor* novaLista);

// Função para criar um novo nó com dados fornecidos
No* cria_no(Dados novoDado);

// Função para inserir um nó em uma lista que está vazia
void insere_no_na_lista_vazia(No* novoNo, No_descritor* ponteiroNoDescritor);

// Função para enfileirar (enqueue)
void insere_no_final(No_descritor* ponteiroNoDescritor, Dados novoDado);

// Função para desenfileirar (dequeue)
No deleta_no_comeco_e_retorna_dados(No_descritor* ponteiroNoDescritor);

// Função para deletar todos os nós da lista e liberar a memória
void deleta_lista_completa(No_descritor* enderecoNoDescritor);

// função para enfileirar no mapa os cenários já previamente definidos
void inicializa_cenarios(No_descritor* mapa);

#endif