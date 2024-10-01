#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char nome[30];
	int valor;
	struct Node * prox;
	struct Node * ant;
};

typedef struct Node node;

struct lista{
	node * inicio;
	node * fim;
	int tamanho;
};

typedef struct lista LISTA;

LISTA * lista_inicia();
void lista_insere(LISTA * lista, const char * nome, int valor);
void lista_imprime(LISTA * l);
void brincadeira(LISTA * l);
void contar(LISTA * lista, int qnt);
void lista_remover(LISTA * l, const char * nome);
node * atPos(LISTA * l, int index);
void lista_libera(LISTA * l);


int main() {
    int n;
    char nome[30];
    int valor;    

    LISTA * lista = lista_inicia();

    // Teste de inserção
    printf("Quantos elementos deseja inserir? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Insira o nome e o valor (formato: nome valor): ");
        scanf(" %s %d", nome, &valor);
        lista_insere(lista, nome, valor);
    }

    // Imprime a lista após as inserções
    printf("Lista após inserções:\n");
    lista_imprime(lista);

    // Teste de remoção
    printf("Nome do elemento a ser removido: ");
    scanf(" %s", nome);
    lista_remover(lista, nome);
    printf("Lista após remoção:\n");
    lista_imprime(lista);

    // Teste da função contar
    if (lista->tamanho > 0) {
        contar(lista, lista->inicio->valor);
    }

    lista_libera(lista);

    return 0;
}

LISTA * lista_inicia(){
	LISTA * new = (LISTA *)malloc(sizeof(LISTA));
	new->inicio = NULL;
	new->fim = NULL;
	new->tamanho = 0;
	return new;
}

void lista_insere(LISTA * l, const char * nome, int valor){
	node * new = (node*)malloc(sizeof(node));
	new->valor = valor;
	memcpy(new->nome, nome, strlen(nome));
	if(l->tamanho == 0){
		l->inicio = new;
		l->fim = new;
		l->tamanho++;
	}
	else if(l->tamanho == 1){
		l->inicio->prox = new;
		l->inicio->ant = new;
		l->fim = new;
		new->ant = l->inicio;
		new->prox = l->inicio;
		l->tamanho++;
	}else{
		l->inicio->ant = new;
		new->prox = l->inicio;
		new->ant = l->fim;
		l->fim->prox = new;
		l->fim = new;
		l->tamanho++;
	}
}

void lista_imprime(LISTA * l){
	node * percorre = l->inicio;
	printf("%s %d\n", percorre->nome, percorre->valor);
	percorre = percorre->prox;
	while(percorre!=l->inicio){
		printf("%s %d\n", percorre->nome, percorre->valor);
		percorre = percorre->prox;
	}
	printf("\nInicio: %s\nFim: %s\n\n", l->inicio->nome, l->fim->nome);
}

void contar(LISTA * lista, int qnt){
    int i;
    node * percorre = lista->inicio;
    if(lista->tamanho == 1){
        printf("Vencedor(a) : %s\n", lista->inicio->nome);
        return;
    }
    if(qnt % 2 == 0){
        for(i = 1; i <= qnt; i++){
            percorre = percorre->ant; // HORARIO
            printf("Ciclo nº: %d\n%s %d\n", i, percorre->nome, percorre->valor);
        }
        int numero = percorre->valor;
        printf("Parou no: %s\n", percorre->nome);
        lista_remover(lista, percorre->nome);
        printf("Lista Atual: \n");
        lista_imprime(lista);
        contar(lista, numero);
    } else {
        for(i = 1; i <= qnt; i++){
            percorre = percorre->prox; // ANTI-HORARIO
            printf("Ciclo nº: %d\n%s %d\n", i, percorre->nome, percorre->valor);
        }
        int numero = percorre->valor;
        printf("Parou no: %s %d\n", percorre->nome, numero);
        lista_remover(lista, percorre->nome);
        printf("\nLista Atual: \n");
        lista_imprime(lista);
        contar(lista, numero);
    }
}

void lista_remover(LISTA * l, const char * nome){
    node * percorre = l->inicio, * aux;
    while (percorre->prox != l->inicio) {
        if (strcmp(percorre->nome, nome) == 0) {
            aux = percorre; // Armazena o nó a ser removido
            if (percorre == l->inicio) {
                l->inicio = percorre->prox;
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
    }
    // Verifica se o nó a ser removido é o último
    if ((strcmp(percorre->nome, nome) == 0) && (percorre == l->fim)) {
        aux = percorre; // Armazena o nó a ser removido
        l->inicio->ant = l->fim->ant;
        l->fim = l->inicio->ant;
        l->fim->prox = l->inicio;
        l->tamanho--;
        free(aux); // Libera o nó armazenado em aux
        return;
    }
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