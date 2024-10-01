#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar true e false

struct Node {
    char nome[30];
    int hp;     // Pontos de vida
    int mp;     // Pontos de mana
    int classe; // aqui é definido 0: guerreiro, 1: mago
    struct Node *prox; // Ponteiro para o próximo nó
    struct Node *ant; // Ponteiro para o nó anterior
};
// Definindo um alias para struct Node para simplificar o código
typedef struct Node node;

// Estrutura para a lista circular duplamente encadeada que gerencia os nós (personagens).
// A lista tem um início, um fim, e guarda o tamanho da lista.
struct lista{
	node * inicio; // Ponteiro para o início da lista
	node * fim; // Ponteiro para o final da lista
	int tamanho;    // Número de nós na lista
};
// Definindo um alias para simplificar a manipulação da lista
typedef struct lista LISTA;

LISTA * lista_inicia();
void lista_insere(LISTA *lista, const char *nome, int hp, int mp, int classe);
void lista_imprime(LISTA * l);
void brincadeira(LISTA * l);
void contar(LISTA *lista);
void lista_remover(LISTA * l, const char * nome);
node * atPos(LISTA * l, int index);
void lista_libera(LISTA * l); 
// Função que executa a ação de ataque entre dois personagens.
// O guerreiro causa mais dano que o mago.
void atacar(node *atacante, node *defensor) {
    // Implementar dano baseado na classe do atacante
    int dano = atacante->classe == 0 ? 10 : 5; // Guerreiro causa mais dano
    defensor->hp -= dano;
    printf("%s ataca %s causando %d de dano!\n", atacante->nome, defensor->nome, dano);
}
// Função que executa uma magia, usada apenas por magos.
// Verifica se o mago tem mana suficiente antes de realizar o ataque mágico.
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
// Função que simula o uso de um item de cura
// O personagem recupera uma quantidade fixa de HP (20 pontos).
void usarItem(node *personagem) {
    personagem->hp += 20; // Exemplo: cura 20 HP
    printf("%s usou uma poção de cura e recuperou 20 HP!\n", personagem->nome);
}
// Função que inicia a batalha entre os personagens.
// O jogador escolhe ações (atacar, usar magia ou item) e os inimigos atacam automaticamente.
void iniciarBatalha(LISTA *lista) {
    node *atual = lista->inicio; // Começa o turno pelo primeiro personagem

    while (1) {
        // Verificar se o personagem atual está vivo antes de agir
        if (atual->hp <= 0) {
            printf("%s foi derrotado!\n", atual->nome);
            node *proximo = atual->prox;  // Armazenar o próximo antes de remover
            lista_remover(lista, atual->nome);

            if (lista->tamanho == 1) {
                printf("%s venceu a batalha!\n", lista->inicio->nome);// Se restar apenas um, ele é o vencedor
                break;
            }

            atual = proximo;  // Passa o turno para o próximo personagem
            continue; // Voltar ao início do laço para o próximo turno
        }

       // Se o personagem atual for o jogador, ele escolhe uma ação
        if (strcmp(atual->nome, "Jogador") == 0) {
            int escolha;
            printf("Escolha sua ação: 1) Atacar 2) Usar Magia 3) Usar Item\n");
            scanf("%d", &escolha);

            node *inimigo = atual->prox; // O próximo personagem é o inimigo
            if (escolha == 1) atacar(atual, inimigo);
            else if (escolha == 2) usarMagia(atual, inimigo);
            else usarItem(atual);
        } else {
            // Os inimigos atacam automaticamente
            atacar(atual, atual->prox); // Ataque simples por padrão
        }

        atual = atual->prox; // Passar para o próximo personagem
    }
}

// Função que inicializa a lista circular duplamente encadeada
// Aloca memória para a lista e configura os ponteiros de início e fim como NULL.
LISTA * lista_inicia(){
	LISTA * new = (LISTA *)malloc(sizeof(LISTA));// Aloca espaço para a lista
	new->inicio = NULL;
	new->fim = NULL;
	new->tamanho = 0;  // Lista começa vazia
	return new; // Retorna o ponteiro para a lista inicializada
}
// Função que insere um novo nó na lista
// Adiciona um personagem com nome, hp, mp e classe na lista circular.
void lista_insere(LISTA *l, const char *nome, int hp, int mp, int classe) {
    node *new = (node *)malloc(sizeof(node));
    new->hp = hp;
    new->mp = mp;
    new->classe = classe;
    memcpy(new->nome, nome, strlen(nome) + 1); // Copia o nome do personagem para o nó
    if (l->tamanho == 0) {
        // Se a lista estiver vazia, o novo nó será o início e o fim
        l->inicio = new;
        l->fim = new;
        new->prox = new;// A lista circular aponta para o próprio nó
        new->ant = new;
    } else {
        // Insere o novo nó no final da lista e ajusta os ponteiros
        new->prox = l->inicio;
        new->ant = l->fim;
        l->fim->prox = new;
        l->inicio->ant = new;
        l->fim = new;
    }
    l->tamanho++; // Incrementa o tamanho da lista
}

// Função que imprime o estado atual da lista.
// Ela percorre todos os nós, começando pelo início, e imprime os atributos de cada personagem.
void lista_imprime(LISTA *l) {
    node *percorre = l->inicio;
    printf("%s (HP: %d, MP: %d)\n", percorre->nome, percorre->hp, percorre->mp);
    percorre = percorre->prox;
    // Continua imprimindo até voltar ao nó inicial, completando a lista circular
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

// Função que remove um nó (personagem) da lista circular.
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
            l->tamanho--; // Diminui o tamanho da lista
            free(aux); // Libera a memória do nó removido
            return;
        }
        percorre = percorre->prox;
    } while (percorre != l->inicio); // Continua até encontrar o nó ou voltar ao início
}


node * atPos(LISTA * l, int index){
	int i;
	node * percorre = l->inicio;
	for(i=1;i<index;i++) percorre=percorre->prox;
	return percorre;
}

// Função que libera a memória de toda a lista, nó por nó.
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