#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar true e false

struct Node {
    char nome[30];
    int hp;     // Health points
    int mp;     // Mana points
    int classe; // 0: guerreiro, 1: mago
    struct Node *prox;
    struct Node *ant;
};

typedef struct Node node;

struct lista{
	node * inicio;
	node * fim;
	int tamanho;
};

typedef struct lista LISTA;

/* LISTA * lista_inicia();
void lista_insere(LISTA * lista, const char * nome, int valor);
void lista_imprime(LISTA * l);
void brincadeira(LISTA * l);
void contar(LISTA * lista, int qnt);
void lista_remover(LISTA * l, const char * nome);
node * atPos(LISTA * l, int index);
void lista_libera(LISTA * l); */

void atacar(node *atacante, node *defensor) {
    // Implementar dano baseado na classe do atacante
    int dano = atacante->classe == 0 ? 10 : 5; // Guerreiro causa mais dano
    defensor->hp -= dano;
    printf("%s ataca %s causando %d de dano!\n", atacante->nome, defensor->nome, dano);
}

void usarMagia(node *mago, node *defensor) {
    if (mago->mp >= 10) {
        int danoMagico = 15;
        defensor->hp -= danoMagico;
        mago->mp -= 10; // Consome MP
        printf("%s usa magia em %s causando %d de dano!\n", mago->nome, defensor->nome, danoMagico);
    } else {
        printf("%s não tem mana suficiente!\n", mago->nome);
    }
}

void usarItem(node *personagem) {
    personagem->hp += 20; // Exemplo: cura 20 HP
    printf("%s usou uma poção de cura e recuperou 20 HP!\n", personagem->nome);
}

#include <stdbool.h> // Para usar true e false

void iniciarBatalha(LISTA *lista) {
    node *atual = lista->inicio;

    while (1) {
        // Verificar se o personagem atual está vivo antes de agir
        if (atual->hp <= 0) {
            printf("%s foi derrotado!\n", atual->nome);
            node *proximo = atual->prox;  // Armazenar o próximo antes de remover
            lista_remover(lista, atual->nome);

            if (lista->tamanho == 1) {
                printf("%s venceu a batalha!\n", lista->inicio->nome);
                break;
            }

            atual = proximo;  // Passa o turno para o próximo personagem
            continue; // Voltar ao início do laço para o próximo turno
        }

        // Menu de ações para o jogador
        if (strcmp(atual->nome, "Jogador") == 0) {
            int escolha;
            printf("Escolha sua ação: 1) Atacar 2) Usar Magia 3) Usar Item\n");
            scanf("%d", &escolha);

            node *inimigo = atual->prox; // O próximo personagem é o inimigo
            if (escolha == 1) atacar(atual, inimigo);
            else if (escolha == 2) usarMagia(atual, inimigo);
            else usarItem(atual);
        } else {
            // Ações dos inimigos (pode ser automático)
            atacar(atual, atual->prox); // Ataque simples por padrão
        }

        atual = atual->prox; // Passar para o próximo personagem
    }
}


LISTA * lista_inicia(){
	LISTA * new = (LISTA *)malloc(sizeof(LISTA));
	new->inicio = NULL;
	new->fim = NULL;
	new->tamanho = 0;
	return new;
}

void lista_insere(LISTA *l, const char *nome, int hp, int mp, int classe) {
    node *new = (node *)malloc(sizeof(node));
    new->hp = hp;
    new->mp = mp;
    new->classe = classe;
    memcpy(new->nome, nome, strlen(nome) + 1);
    if (l->tamanho == 0) {
        l->inicio = new;
        l->fim = new;
        new->prox = new;
        new->ant = new;
    } else {
        new->prox = l->inicio;
        new->ant = l->fim;
        l->fim->prox = new;
        l->inicio->ant = new;
        l->fim = new;
    }
    l->tamanho++;
}

// Função para imprimir a lista
void lista_imprime(LISTA *l) {
    node *percorre = l->inicio;
    printf("%s (HP: %d, MP: %d)\n", percorre->nome, percorre->hp, percorre->mp);
    percorre = percorre->prox;
    while (percorre != l->inicio) {
        printf("%s (HP: %d, MP: %d)\n", percorre->nome, percorre->hp, percorre->mp);
        percorre = percorre->prox;
    }
    printf("\nInicio: %s\nFim: %s\n\n", l->inicio->nome, l->fim->nome);
}

void contar(LISTA * lista) {
    if (lista->tamanho == 1) {
        printf("Vencedor(a): %s\n", lista->inicio->nome);
        return;
    }

    node *percorre = lista->inicio;

    while (lista->tamanho > 1) {
        if (percorre->hp <= 0) {
            printf("%s foi derrotado!\n", percorre->nome);
            lista_remover(lista, percorre->nome);
            printf("Lista Atual: \n");
            lista_imprime(lista);

            // Se restar apenas um personagem, este é o vencedor
            if (lista->tamanho == 1) {
                printf("Vencedor(a): %s\n", lista->inicio->nome);
                break;
            }
        }

        // Progredir para o próximo personagem
        percorre = percorre->prox;
    }
}

// Função para remover um nó da lista
void lista_remover(LISTA *l, const char *nome) {
    if (l->tamanho == 0) return; // Lista vazia
    node *percorre = l->inicio;
    node *aux;

    do {
        if (strcmp(percorre->nome, nome) == 0) {
            aux = percorre; // Armazena o nó a ser removido
            if (l->tamanho == 1) {
                l->inicio = l->fim = NULL;
            } else if (percorre == l->inicio) {
                l->inicio = percorre->prox;
                l->fim->prox = l->inicio;
                l->inicio->ant = l->fim;
            } else if (percorre == l->fim) {
                l->fim = percorre->ant;
                l->fim->prox = l->inicio;
                l->inicio->ant = l->fim;
            } else {
                percorre->ant->prox = percorre->prox;
                percorre->prox->ant = percorre->ant;
            }
            l->tamanho--;
            free(aux); // Libera o nó armazenado em aux
            return;
        }
        percorre = percorre->prox;
    } while (percorre != l->inicio);
}


node * atPos(LISTA * l, int index){
	int i;
	node * percorre = l->inicio;
	for(i=1;i<index;i++) percorre=percorre->prox;
	return percorre;
}

void lista_libera(LISTA * l){
    if (l->inicio == NULL) return; // Verifica se a lista está vazia

    node * percorre = l->inicio;
    node * proximo;

    do {
        proximo = percorre->prox; // Armazena o próximo nó
        free(percorre);           // Libera o nó atual
        percorre = proximo;       // Move para o próximo nó
    } while (percorre != l->inicio); // Continua até voltar ao início

    free(l); // Libera a estrutura da lista
}

int main() {
    LISTA *lista = lista_inicia();

    // Inserir jogadores e inimigos
    lista_insere(lista, "Jogador", 100, 50, 0);  // Guerreiro
    lista_insere(lista, "Inimigo1", 50, 30, 1);  // Mago
    lista_insere(lista, "Inimigo2", 60, 20, 0);  // Guerreiro

    // Imprimir lista após inserção
    printf("Lista inicial:\n");
    lista_imprime(lista);

    // Iniciar a batalha
    iniciarBatalha(lista);

    // Libera a memória alocada
    lista_libera(lista);

    return 0;
}