#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
Dados constructor(char nome[], char descricao[], int dropaItem, int temMonstro, int recuperaStatus){
    Dados temp;
    strcpy(temp.nome, nome);
    strcpy(temp.descricao, descricao);
    temp.dropaItem = dropaItem;
    temp.temMonstro = temMonstro;
    temp.recuperaStatus = recuperaStatus;
    return temp;
}

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
        printf("Indice %d: %s\n%s\n\n", i, atual->dados.nome, atual->dados.descricao); // Mostra o índice e o valor
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
        printf("Indice %d: %s\n%s\n\n", i, atual->dados.nome, atual->dados.descricao); // Mostra o índice e o valor do nó
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
    setlocale(LC_ALL, "");
    No_descritor mapa; // minha lista é uma variável tipo nó descritor
    cria_lista(&mapa);
    // mo
    Dados cenario, bau, turno, oasis;
    cenario = constructor("Era uma vez...", "Em um mundo onde a magia flui dos elementos, o reino de Eldorion esconde nas profundezas de suas ruínas a JOIA DE SERAPHEL. Aquele que a possuir terá o poder de controlar todos os elementos da natureza, um segredo perdido e cobiçado por forças sombrias.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    cenario = constructor("Sua Missão:", "Você é Lira Valen, uma maga que domina luz e sombras, enviada pela Guilda dos Arcanos para recuperar a joia de Seraphel. Você deve atravessar Sylvarim, enfrentar as criaturas da Caverna do Éter e desvendar os mistérios das ruínas de Eldorion antes que forças sombrias a obtenham.", 1, 0, 0);
    insere_no_final(&mapa, cenario);
    // nesse de cima a gente poderia dropar as armas da Lira e já colocar no inventário. Tipo: "Você recebeu uma espada!\n" "Você recebeu 1 poção de hp\n" etc. todo o starter pack. E depois fazer assim: "seus itens foram adicionados ao inventário."
    
    cenario = constructor("Sylvarim", "Você adentra a floresta de Sylvarim, onde a luz filtra-se pelas copas das árvores, criando padrões místicos no chão. O ar é denso com magia antiga, e criaturas espreitam nas sombras. Druidas observam de longe, sussurrando feitiços enquanto a vegetação parece ter vida própria.",0,0,0);
    insere_no_final(&mapa, cenario);
    turno = constructor("Há algo errado...", "À medida que avança, o ar se torna pesado, e um som gutural ecoa pela escuridão. Sussurros de perigo te cercam. Das sombras, criaturas surgem, olhos brilhando com intenção predatória. Seu coração acelera. Você está prestes a enfrentar monstros perigosos.", 0,1,0);
    insere_no_final(&mapa, turno);

    bau = constructor("Bau", "Diante de você, um baú antigo emite um leve brilho. O som das dobradiças rangendo ecoa pela sala quando você o abre lentamente. Dentro, reluzem itens valiosos. A sensação de descoberta é palpável. Você encontrou um tesouro raro!", 1, 0, 0);
    insere_no_final(&mapa, bau);
    oasis = constructor("Pelos deuses!", "Você encontra uma fonte mágica cercada por cristais reluzentes. A água iridescente brilha sob a luz, emanando uma energia tranquilizadora. Ao se agachar para beber, uma onda de vitalidade envolve seu corpo, restaurando rapidamente seus HP e MP. É um verdadeiro elixir da vida!", 0,0,1);
    insere_no_final(&mapa, oasis);

    cenario = constructor("Caverna do Eter", "Ao cruzar o limiar da Caverna do Éter, a realidade se distorce. O tempo parece hesitar, o chão pulsa com uma energia etérea, e as paredes brilham com runas flutuantes. Cada passo ecoa em múltiplas direções, como se você estivesse em mais de um lugar ao mesmo tempo.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    turno = constructor("O que é isso?", "O chão vibra sob seus pés, e um grito agudo corta o silêncio. De repente, monstros emergem da terra, com garras afiadas e presas prontas para atacar. Não há escapatória: é lutar ou perecer. Prepare-se para o combate.", 0,1,0);
    insere_no_final(&mapa, turno);

    cenario = constructor("Ruinas de Eldorion", "As ruínas de Eldorion emergem da névoa, uma cidade antiga tomada pelo silêncio. Pedras quebradas e colunas caídas escondem segredos ancestrais. Armadilhas mágicas ativam ao menor toque, enquanto sussurros ecoam pelas paredes, lembrando de um poder perdido há eras.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    bau = constructor("Bau", "Ao explorar um canto esquecido, você tropeça em um baú enferrujado, com inscrições antigas. Com um esforço, você consegue abri-lo. Dentro, reluzem itens preciosos que poderiam mudar o rumo de sua aventura. Um sorriso surge em seu rosto ? a sorte sorriu para você!", 1, 0, 0);
    insere_no_final(&mapa, bau);
    turno = constructor("Você continua caminhando, até que...", "Ao dobrar a esquina, uma presença sombria se faz sentir. Criaturas monstruosas aparecem, bloqueando seu caminho, seus corpos deformados pelas energias malignas. O ar vibra com tensão, e você sabe que não há como evitar a batalha.", 0,1,0);
    insere_no_final(&mapa, turno);
    
    mostra_lista_completa(&mapa);


    return 0;
}