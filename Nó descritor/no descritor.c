#include <stdio.h>
#include <stdlib.h>

// Estrutura que representa os dados que serão armazenados nos nós da lista
typedef struct {
    int numero; // Coloquei um int aqui só pra representar, mas isso vai mudar
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

// Função para inicializar a lista
void cria_lista(No_descritor* novaLista) {
    novaLista->tamanho = 0; // Inicializa o tamanho da lista como 0
    novaLista->primeiro = NULL; // A lista começa vazia
    novaLista->ultimo = NULL; // Não há último nó na lista vazia
}

// Função para criar um novo nó com dados fornecidos
No* cria_no(Dados novoDado) {
    No* novoNo = (No*) malloc(sizeof(No)); // Aloca memória para um novo nó
    if (novoNo) {
        novoNo->dados = novoDado; // Armazena os dados no novo nó
        novoNo->prox = NULL; // Inicializa o ponteiro para o próximo nó como NULL
        return novoNo; // Retorna o novo nó criado
    }
    else return NULL; // Retorna NULL se a alocação falhar
}

// Função para inserir um nó em uma lista que está vazia
void insere_no_na_lista_vazia(No* novoNo, No_descritor* ponteiroNoDescritor) {
    ponteiroNoDescritor->primeiro = novoNo; // O novo nó se torna o primeiro
    ponteiroNoDescritor->ultimo = novoNo; // O novo nó se torna o último
    ponteiroNoDescritor->tamanho = 1; // Atualiza o tamanho da lista
}

// Função para inserir um nó no início da lista
void insere_no_comeco(No_descritor* ponteiroNoDescritor, Dados novoDado) {
    No* novoNo = cria_no(novoDado); // Cria um novo nó
    if (novoNo) { // Verifica se o novo nó foi criado com sucesso
        if (ponteiroNoDescritor->tamanho == 0) { // Se a lista estiver vazia
            insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere no nó vazio
        } else { // Se a lista não estiver vazia
            No* primeiroNo = ponteiroNoDescritor->primeiro; // Salva o primeiro nó atual
            ponteiroNoDescritor->primeiro = novoNo; // O novo nó se torna o primeiro
            novoNo->prox = primeiroNo; // O novo nó aponta para o antigo primeiro nó
            ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
        }
    }
}

// Função para inserir um nó no final da lista
void insere_no_final(No_descritor* ponteiroNoDescritor, Dados novoDado) {
    No* novoNo = cria_no(novoDado); // Cria um novo nó
    if (novoNo) { // Verifica se o novo nó foi criado com sucesso
        if (ponteiroNoDescritor->tamanho == 0) { // Se a lista estiver vazia
            insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere no nó vazio
        } else { // Se a lista não estiver vazia
            ponteiroNoDescritor->ultimo->prox = novoNo; // O atual último nó aponta para o novo nó
            ponteiroNoDescritor->ultimo = novoNo; // O novo nó se torna o último
            ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
        }
    }
}


// Função para inserir um nó em uma posição específica (meio da lista)
void insere_no_meio(No_descritor* ponteiroNoDescritor, Dados novoDado, int indice) {
    // Se a lista estiver vazia, insira o nó como o único elemento
    if (ponteiroNoDescritor->tamanho == 0) {
        No* novoNo = cria_no(novoDado); // Cria um novo nó
        if (novoNo) insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere na lista vazia
    } else if ((ponteiroNoDescritor->tamanho - 1) < indice) { // Se o índice for maior que o tamanho
        insere_no_final(ponteiroNoDescritor, novoDado); // Insere no final
    } else if (indice == 0) { // Se o índice for 0, insira no início
        insere_no_comeco(ponteiroNoDescritor, novoDado); // Insere no começo
    } else { // Para inserção no meio
        No* novoNo = cria_no(novoDado); // Cria um novo nó
        No* anterior = ponteiroNoDescritor->primeiro; // Começa do primeiro nó
        int i = 1; // Contador para percorrer a lista
        while (i < indice) { // Enquanto não chegar ao índice desejado
            anterior = anterior->prox; // Move para o próximo nó
            i++;
        }
        novoNo->prox = anterior->prox; // O novo nó aponta para o nó na posição desejada
        anterior->prox = novoNo; // O nó anterior aponta para o novo nó
        ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
    }
}

// Função para substituir os dados de um nó em uma posição específica
void substitui_no_indice(No_descritor* ponteiroNoDescritor, Dados novoDado, int indice) {
    if (indice < ponteiroNoDescritor->tamanho) { // Verifica se o índice é válido
        No* atual = ponteiroNoDescritor->primeiro; // Começa do primeiro nó
        for (int i = 0; i < indice; i++) { // Percorre até o índice desejado
            atual = atual->prox; // Move para o próximo nó
        }
        atual->dados = novoDado; // Substitui os dados do nó atual
    }
}

// Função para mostrar todos os nós da lista
void mostra_lista_completa(No_descritor* enderecoNoDescritor) {
    No* atual = enderecoNoDescritor->primeiro; // Começa do primeiro nó
    int i = 0; // Contador de índice
    printf("Temos %d campos\n", enderecoNoDescritor->tamanho); // Mostra a quantidade de nós
    while (atual != NULL) { // Enquanto houver nós
        printf("Índice %d: %d\n", i, atual->dados.numero); // Mostra o índice e o valor
        atual = atual->prox; // Move para o próximo nó
        i++;
    }
}

// Função para mostrar o nó em um índice específico
void mostra_no_indice(No_descritor* ponteiroNoDescritor, int indice) {
    if (indice < ponteiroNoDescritor->tamanho) { // Verifica se o índice é válido
        No* atual = ponteiroNoDescritor->primeiro; // Começa do primeiro nó
        int i = 0; // Contador de índice
        while (i < indice) { // Percorre até o índice desejado
            atual = atual->prox; // Move para o próximo nó
            i++;
        }
        printf("Índice %d: %d\n", i, atual->dados.numero); // Mostra o índice e o valor do nó
    }
}

// Função para deletar o nó do começo da lista
void deleta_no_comeco(No_descritor* ponteiroNoDescritor) {
    No* deletar = ponteiroNoDescritor->primeiro; // Ponto para o nó que será deletado
    ponteiroNoDescritor->primeiro = ponteiroNoDescritor->primeiro->prox; // Atualiza o primeiro nó
    free(deletar); // Libera a memória do nó deletado
    ponteiroNoDescritor->tamanho--; // Decrementa o tamanho da lista
}

// Função para deletar o nó do final da lista
void deleta_no_final(No_descritor* ponteiroNoDescritor){
    No* anterior = ponteiroNoDescritor->primeiro;
    No* temp;
    for(int i=0; i<(ponteiroNoDescritor->tamanho-2); i++){
        anterior=anterior->prox;
    }
    ponteiroNoDescritor->ultimo=anterior;
    temp = anterior->prox;
    anterior->prox = NULL;
    free(temp);
    ponteiroNoDescritor->tamanho--;
}

// Função para deletar o nó num indice específico da lista
void deleta_no_indice(No_descritor* ponteiroNoDescritor, int indice){
    if(indice<ponteiroNoDescritor->tamanho){
        if(indice==0) deleta_no_comeco(ponteiroNoDescritor);
        else if(indice == (ponteiroNoDescritor->tamanho-1)) deleta_no_final(ponteiroNoDescritor);
        else { // se for entre o primeiro e o ultimo
            No* anterior = ponteiroNoDescritor->primeiro;
            No* deletar;
            for(int i=0; i<(indice-1); i++){
            anterior=anterior->prox;
            }
            deletar = anterior->prox;
            anterior->prox = deletar->prox;
            free(deletar);
            ponteiroNoDescritor->tamanho--;
        }
    }
}

// Função para deletar todos os nós da lista
void deleta_lista_completa(No_descritor* enderecoNoDescritor){ // recebe o ponteiro do Nó Descritor
    if(enderecoNoDescritor->tamanho>0) {
    No* atual = enderecoNoDescritor->primeiro; //cria um ponteiro auxiliar que recebe o primeiro item da lista
    No* deletar; 
    for(int i=0; i<enderecoNoDescritor->tamanho; i++){
        deletar = atual;  // guarda o atual num ponteiro auxiliar chamado deletar
        atual = atual->prox; // o atual vira o próximo
        free(deletar);
    }
    if(atual == NULL) printf("\nLista apagada!!!!\n");
    enderecoNoDescritor->primeiro=NULL;
    enderecoNoDescritor->ultimo=NULL;
    enderecoNoDescritor->tamanho=0;
    }
}


int main(){
    No_descritor lista; // minha lista é uma variável tipo nó descritor
    Dados dados, teste;
    dados.numero = 10000;
    teste.numero = 50;
    //No no;

    /*
    CRUD significa Create(criar), Read(ler), Update(atualizar), Delete(deletar). Logo, preciso criar funções para cada uma dessas opções.
    */
   
   // c
   cria_lista(&lista); //ok
   // r
   //mostra_no_indice();
   // u
   insere_no_comeco(&lista, dados); //ok
   insere_no_comeco(&lista, dados);
   insere_no_comeco(&lista, teste);
   insere_no_final(&lista, teste); //ok
   insere_no_meio(&lista, teste, 2); //ok
   insere_no_meio(&lista, dados, 1);
   
   mostra_lista_completa(&lista);
   //deleta_no_indice(&lista, 5);  //ok
    deleta_no_final(&lista);
   // d
    mostra_lista_completa(&lista); //ok
    mostra_no_indice(&lista, 3); //ok
   //deleta_no_comeco();
   //deleta_no_final();
   //deleta_no_indice();
   deleta_lista_completa(&lista); //ok
   printf("\nentrou\n");
   mostra_lista_completa(&lista);
    printf("\nsaiu\n");


    return 0;
}