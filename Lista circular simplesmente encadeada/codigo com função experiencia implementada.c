#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIVEL 99
#define XP_PARA_SUBIR 100

// Estrutura para o personagem
typedef struct {
    char nome[50];
    int hp;
    int mp;
    int nivel;
    int xp;
} Jogador;

// Estrutura para os inimigos
typedef struct {
    char nome[50];
    int hp;
    int poderAtaque;
    int xpGanho;
} Inimigo;

// Estrutura para o nó da lista
typedef struct Nodo {
    Jogador jogador;
    Inimigo inimigos[2]; // Array para 2 inimigos
    struct Nodo* anterior;
    struct Nodo* proximo;
} Nodo;

// Função para criar um novo jogador
Jogador criarJogador(char* nome) {
    Jogador jogador;
    strcpy(jogador.nome, nome);
    jogador.hp = 100;
    jogador.mp = 50;
    jogador.nivel = 1;
    jogador.xp = 0;
    return jogador;
}

// Função para criar um novo inimigo
Inimigo criarInimigo(char* nome, int hp, int poderAtaque, int xpGanho) {
    Inimigo inimigo;
    strcpy(inimigo.nome, nome);
    inimigo.hp = hp;
    inimigo.poderAtaque = poderAtaque;
    inimigo.xpGanho = xpGanho;
    return inimigo;
}

// Função para criar um novo nó
Nodo* criarNodo(Jogador jogador, Inimigo inimigos[2]) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->jogador = jogador;
    novoNodo->inimigos[0] = inimigos[0];
    novoNodo->inimigos[1] = inimigos[1];
    novoNodo->anterior = NULL;
    novoNodo->proximo = NULL;
    return novoNodo;
}

// Função para adicionar um nodo à lista
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

// Função para atacar um inimigo
void atacar(Nodo* jogadorNodo, int inimigoIndex) {
    printf("%s atacou %s e causou 10 de dano!\n", jogadorNodo->jogador.nome, jogadorNodo->inimigos[inimigoIndex].nome);
    jogadorNodo->inimigos[inimigoIndex].hp -= 10; // Dano fixo de 10
    if (jogadorNodo->inimigos[inimigoIndex].hp < 0) {
        jogadorNodo->inimigos[inimigoIndex].hp = 0; // Prevenir HP negativo
    }
}

// Função para usar magia
int usarMagia(Nodo* jogadorNodo, int inimigoIndex) {
    if (jogadorNodo->jogador.mp < 10) {
        printf("MP insuficiente para usar magia!\n");
        return 0;
    }

    int dano = 0;
    int custoMp = 0;
    int tipoMagia;

    printf("Escolha a magia (ou digite 0 para cancelar):\n");
    printf("1. Bola de Fogo (custa 10 MP, causa 20 de dano)\n");
    printf("2. Raio de Gelo (custa 8 MP, causa 15 de dano)\n");
    printf("0. Cancelar\n");
    scanf("%d", &tipoMagia);

    if (tipoMagia == 0) {
        return 0; // Cancela o uso da magia
    }

    if (tipoMagia == 1) { // Bola de Fogo
        dano = 20; // Dano da magia
        custoMp = 10; // Custo de MP
    } else if (tipoMagia == 2) { // Raio de Gelo
        dano = 15; // Dano da magia
        custoMp = 8; // Custo de MP
    } else {
        printf("Magia inválida!\n");
        return 0; // Cancela o uso da magia
    }

    jogadorNodo->jogador.mp -= custoMp; // Subtrai MP do jogador
    jogadorNodo->inimigos[inimigoIndex].hp -= dano;
    printf("%s usou magia e causou %d de dano em %s!\n", jogadorNodo->jogador.nome, dano, jogadorNodo->inimigos[inimigoIndex].nome);
    if (jogadorNodo->inimigos[inimigoIndex].hp < 0) {
        jogadorNodo->inimigos[inimigoIndex].hp = 0; // Prevenir HP negativo
    }

    return 1; // Uso de magia bem-sucedido
}

// Função para recuperar HP
void usarItem(Nodo* jogadorNodo) {
    jogadorNodo->jogador.hp += 20; // Recupera 20 de HP
    if (jogadorNodo->jogador.hp > 100) {
        jogadorNodo->jogador.hp = 100; // Limitar o HP máximo
    }
    printf("%s usou um item e recuperou 20 HP!\n", jogadorNodo->jogador.nome);
}

// Função para atacar o jogador
void ataqueInimigo(Nodo* jogadorNodo, Inimigo* inimigo) {
    printf("%s atacou %s e causou %d de dano!\n", inimigo->nome, jogadorNodo->jogador.nome, inimigo->poderAtaque);
    jogadorNodo->jogador.hp -= inimigo->poderAtaque; // Dano do inimigo
}

// Função para calcular experiência
void calcularXP(Nodo* jogadorNodo, Inimigo* inimigo) {
    jogadorNodo->jogador.xp += inimigo->xpGanho; // Ganha XP por inimigo derrotado
    printf("%s ganhou %d XP!\n", jogadorNodo->jogador.nome, inimigo->xpGanho);
    
    // Verifica se o jogador sobe de nível
    while (jogadorNodo->jogador.xp >= XP_PARA_SUBIR) {
        jogadorNodo->jogador.xp -= XP_PARA_SUBIR; // Remove XP para subir de nível
        if (jogadorNodo->jogador.nivel < MAX_NIVEL) {
            jogadorNodo->jogador.nivel++;
            printf("%s subiu para o nível %d!\n", jogadorNodo->jogador.nome, jogadorNodo->jogador.nivel);
        }
    }
}

// Função para mostrar HP do jogador e dos inimigos
void mostrarStatus(Nodo* jogadorNodo) {
    printf("\n--- Status ---\n");
    printf("%s: HP = %d, MP = %d, Nível = %d, XP = %d\n", jogadorNodo->jogador.nome, jogadorNodo->jogador.hp, jogadorNodo->jogador.mp, jogadorNodo->jogador.nivel, jogadorNodo->jogador.xp);
    int i;
    for (i = 0; i < 2; i++) {
        printf("%s: HP = %d\n", jogadorNodo->inimigos[i].nome, jogadorNodo->inimigos[i].hp);
    }
}

// Função principal para o combate
void combate(Nodo* jogadorNodo) {
    int opcao, inimigoIndex;

    while (jogadorNodo->jogador.hp > 0) {
        mostrarStatus(jogadorNodo);

        // Verifica se ambos os inimigos estão derrotados
        if (jogadorNodo->inimigos[0].hp <= 0 && jogadorNodo->inimigos[1].hp <= 0) {
            printf("Todos os inimigos foram derrotados! Fim do combate.\n");
            break; // Encerra o combate se ambos os inimigos estiverem mortos
        }

        printf("\nEscolha um inimigo para atacar (1 ou 2): ");
        scanf("%d", &inimigoIndex);
        inimigoIndex--; // Ajusta para o índice do array (0 ou 1)

        if (inimigoIndex < 0 || inimigoIndex > 1 || jogadorNodo->inimigos[inimigoIndex].hp <= 0) {
            printf("Inimigo inválido ou já derrotado!\n");
            continue;
        }

        printf("\nEscolha a ação:\n1. Atacar\n2. Usar Magia\n3. Usar Item\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atacar(jogadorNodo, inimigoIndex);
                break;
            case 2:
                if (usarMagia(jogadorNodo, inimigoIndex) == 0) {
                    printf("Uso de magia cancelado. Escolha outra ação.\n");
                    continue; // Retorna ao início do loop para escolher uma nova ação
                }
                break;
            case 3:
                usarItem(jogadorNodo);
                break;
            default:
                printf("Opção inválida!\n");
                continue;
        }

        // Ataque simultâneo dos inimigos
        int i;
        for (i = 0; i < 2; i++) {
            if (jogadorNodo->inimigos[i].hp > 0) {
                ataqueInimigo(jogadorNodo, &jogadorNodo->inimigos[i]);
            }
        }

        // Verifica se o inimigo foi derrotado
        if (jogadorNodo->inimigos[inimigoIndex].hp <= 0) {
            printf("%s foi derrotado!\n", jogadorNodo->inimigos[inimigoIndex].nome);
            calcularXP(jogadorNodo, &jogadorNodo->inimigos[inimigoIndex]); // Adiciona XP ao jogador
        }
    }

    if (jogadorNodo->jogador.hp <= 0) {
        printf("%s foi derrotado! Fim do jogo.\n", jogadorNodo->jogador.nome);
    }
}

// Função principal
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
