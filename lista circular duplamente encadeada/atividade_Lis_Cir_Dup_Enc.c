#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char nome[30];
    int hp;     // Pontos de vida
    int mp;     // Pontos de mana
    int classe; // 0: guerreiro, 1: mago
    struct Node *prox; // Ponteiro para o próximo nó
    struct Node *ant; // Ponteiro para o nó anterior
};

// Estrutura para a magia
struct Magia {
    char nome[30];
    int custoMp;
    int dano;
};

// Definindo um alias para struct Node para simplificar o código
typedef struct Node node;

// Estrutura para a lista circular duplamente encadeada que gerencia os nós (personagens).
struct lista {
    node *inicio; // Ponteiro para o início da lista
    node *fim; // Ponteiro para o final da lista
    int tamanho;    // Número de nós na lista
};

// Definindo um alias para simplificar a manipulação da lista
typedef struct lista LISTA;

LISTA *lista_inicia();
void lista_insere(LISTA *lista, const char *nome, int hp, int mp, int classe);
void lista_imprime(LISTA *l);
void brincadeira(LISTA *l);
void contar(LISTA *lista);
void lista_remover(LISTA *l, const char *nome);
node *atPos(LISTA *l, int index);
void lista_libera(LISTA *l);

// Função que executa a ação de ataque entre dois personagens.
void atacar(node *atacante, node *defensor) {
    int dano = atacante->classe == 0 ? 10 : 5; // Guerreiro causa mais dano
    defensor->hp -= dano;
    printf("%s ataca %s causando %d de dano!\n", atacante->nome, defensor->nome, dano);
}

// Função que executa uma magia, usada apenas por magos.
void usarMagia(node *mago, node *defensor, struct Magia magia) {
    if (mago->mp >= magia.custoMp) {
        defensor->hp -= magia.dano;
        mago->mp -= magia.custoMp; // Consome MP
        printf("%s usa %s em %s causando %d de dano!\n", mago->nome, magia.nome, defensor->nome, magia.dano);
    } else {
        printf("%s não tem mana suficiente para usar %s!\n", mago->nome, magia.nome);
    }
}

// Função que simula o uso de um item de cura
void usarItem(node *personagem) {
    printf("%s (HP: %d, MP: %d)\n", personagem->nome, personagem->hp, personagem->mp);
    printf("Deseja usar um item para curar? 1) Sim 2) Não\n");
    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
        personagem->hp += 20; // Exemplo: cura 20 HP
        printf("%s usou uma poção de cura e recuperou 20 HP!\n", personagem->nome);
    } else {
        printf("Você escolheu não usar o item.\n");
    }
}

// Função para exibir os inimigos disponíveis
void exibirInimigos(LISTA *lista) {
    node *temp = lista->inicio;
    int contador = 1;

    printf("\nInimigos disponíveis:\n");
    do {
        if (strcmp(temp->nome, "Jogador") != 0) {  // Exibir apenas os inimigos
            printf("%d) %s - HP: %d\n", contador, temp->nome, temp->hp);
        }
        temp = temp->prox;
        contador++;
    } while (temp != lista->inicio);
}

// Função para selecionar um inimigo específico
node *selecionarInimigo(LISTA *lista) {
    exibirInimigos(lista);
    int escolha;
    printf("Escolha o inimigo que deseja atacar: ");
    scanf("%d", &escolha);

    node *temp = lista->inicio;
    int contador = 1;
    do {
        if (strcmp(temp->nome, "Jogador") != 0) {  // Ignorar o jogador
            if (contador == escolha) {
                return temp;  // Retorna o inimigo escolhido
            }
        }
        temp = temp->prox;
        contador++;
    } while (temp != lista->inicio);

    return NULL;  // Caso nenhuma escolha seja válida
}

void iniciarBatalha(LISTA *lista) {
    node *atual = lista->inicio;
    struct Magia magias[2] = { {"Bola de Fogo", 10, 15}, {"Raio de Gelo", 8, 12} };
    int acao, escolhaMagia;

    while (1) {
        // Verificar se o personagem atual está vivo
        if (atual->hp <= 0) {
            printf("%s foi derrotado!\n", atual->nome);
            node *proximo = atual->prox;
            lista_remover(lista, atual->nome);

            if (lista->tamanho == 1) {
                printf("%s venceu a batalha!\n", lista->inicio->nome);
                break;
            }

            atual = proximo;
            continue;
        }

        // Se for a vez do joga
        if (strcmp(atual->nome, "Jogador") == 0) {
            node *inimigo = NULL;
            do {
                printf("Escolha sua ação: 1) Atacar 2) Usar Magia 3) Usar Item\n");
                scanf("%d", &acao);

                switch (acao) {
                    case 1:  // Atacar
                        inimigo = selecionarInimigo(lista);
                        if (inimigo != NULL) {
                            atacar(atual, inimigo);
                        }
                        break;

                    case 2:  // Usar Magia
                        if (atual->classe == 1) {
                            printf("Escolha a magia:\n");
                            for (int i = 0; i < 2; i++) {
                                printf("%d) %s (Custo MP: %d, Dano: %d)\n", i + 1, magias[i].nome, magias[i].custoMp, magias[i].dano);
                            }
                            printf("Selecione a magia ou 0 para voltar: ");
                            scanf("%d", &escolhaMagia);

                            if (escolhaMagia > 0 && escolhaMagia <= 2) {
                                inimigo = selecionarInimigo(lista);
                                if (inimigo != NULL) {
                                    usarMagia(atual, inimigo, magias[escolhaMagia - 1]);
                                }
                            }
                        } else {
                            printf("Você não pode usar magia.\n");
                        }
                        break;

                    case 3:  // Usar Item
                        usarItem(atual);  // Usar item no jogador
                        break;

                    default:
                        printf("Ação inválida.\n");
                }
            } while (acao < 1 || acao > 3);
        } else {
            // Os inimigos atacam automaticamente o jogador
            node *jogador = lista->inicio;
            while (strcmp(jogador->nome, "Jogador") != 0) {
                jogador = jogador->prox;
            }
            atacar(atual, jogador);
        }

        // Avançar para o próximo personagem
        atual = atual->prox;
    }
}





// Função que inicializa a lista circular duplamente encadeada
LISTA *lista_inicia() {
    LISTA *new = (LISTA *)malloc(sizeof(LISTA));
    new->inicio = NULL;
    new->fim = NULL;
    new->tamanho = 0;  // Lista começa vazia
    return new; // Retorna o ponteiro para a lista inicializada
}

// Função que insere um novo nó na lista
void lista_insere(LISTA *l, const char *nome, int hp, int mp, int classe) {
    node *new = (node *)malloc(sizeof(node));
    new->hp = hp;
    new->mp = mp;
    new->classe = classe;
    strcpy(new->nome, nome);
    
    // Se a lista estiver vazia, inicializa o nó como o primeiro
    if (l->inicio == NULL) {
        l->inicio = new;
        l->fim = new;
        new->prox = new; // Ponteiro para si mesmo
        new->ant = new; // Ponteiro para si mesmo
    } else {
        // Insere no final da lista
        new->prox = l->inicio; // O próximo do novo nó será o primeiro
        new->ant = l->fim; // O anterior do novo nó será o último
        l->fim->prox = new; // O próximo do último nó agora será o novo nó
        l->inicio->ant = new; // O anterior do primeiro nó agora será o novo nó
        l->fim = new; // Atualiza o fim da lista
    }
    l->tamanho++; // Incrementa o tamanho da lista
}

// Função que imprime os dados de todos os nós da lista
void lista_imprime(LISTA *l) {
    if (l->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    
    node *temp = l->inicio;
    do {
        printf("Nome: %s, HP: %d, MP: %d, Classe: %d\n", temp->nome, temp->hp, temp->mp, temp->classe);
        temp = temp->prox;
    } while (temp != l->inicio);
}

// Função que remove um nó da lista
void lista_remover(LISTA *l, const char *nome) {
    if (l->inicio == NULL) return; // Lista vazia, nada a remover

    node *temp = l->inicio;
    do {
        if (strcmp(temp->nome, nome) == 0) {
            if (temp == l->inicio) {
                l->inicio = temp->prox; // Atualiza o início da lista
            }
            if (temp == l->fim) {
                l->fim = temp->ant; // Atualiza o fim da lista
            }
            temp->ant->prox = temp->prox; // Atualiza o próximo do anterior
            temp->prox->ant = temp->ant; // Atualiza o anterior do próximo
            free(temp); // Libera a memória do nó removido
            l->tamanho--; // Decrementa o tamanho da lista
            return; // Sai da função após remover o nó
        }
        temp = temp->prox;
    } while (temp != l->inicio);
}

// Função que retorna o nó na posição especificada
node *atPos(LISTA *l, int index) {
    if (index < 1 || index > l->tamanho) return NULL; // Índice inválido

    node *temp = l->inicio;
int i;
    for (i = 1; i < index; i++) {
        temp = temp->prox;
    }
    return temp; // Retorna o nó na posição especificada
}

// Função que libera a memória da lista
void lista_libera(LISTA *l) {
    while (l->inicio != NULL) {
        lista_remover(l, l->inicio->nome); // Remove o primeiro nó até a lista ficar vazia
    }
    free(l); // Libera a memória da lista
}

int main() {
    LISTA *lista = lista_inicia();
    
    // Adiciona personagens à lista
    lista_insere(lista, "Jogador", 100, 50, 1); // O jogador é um guerreiro
    lista_insere(lista, "Goblin", 30, 0, 0); // Goblin é um guerreiro
    lista_insere(lista, "Orc", 50, 0, 0); // Orc é um guerreiro
    
    // Inicia a batalha
    iniciarBatalha(lista);
    
    // Libera a memória da lista
    lista_libera(lista);
    return 0;
}
