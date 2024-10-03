#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura que representa os dados que ser�o armazenados nos n�s da lista
typedef struct {
    char nome[100];
    char descricao[300];
    int dropaItem; //0 para n�o e 1 para sim
    int temMonstro; //0 para n�o e 1 para sim
    int recuperaStatus; //0 para n�o e 1 para sim
} Dados;

// Estrutura que representa um n� da lista encadeada
typedef struct No {
    Dados dados; // Dados contidos no n�
    struct No* prox; // Ponteiro para o pr�ximo n� na lista
} No;

// Estrutura que atua como descritor da lista encadeada
typedef struct {
    int tamanho; // Quantidade de n�s ativos na lista
    No* primeiro; // Ponteiro para o primeiro n� (cabe�a da lista)
    No* ultimo; // Ponteiro para o �ltimo n� (cauda da lista)
} No_descritor;

// fun��o para inicializar dados;
Dados constructor(char nome[], char descricao[], int dropaItem, int temMonstro, int recuperaStatus){
    Dados temp;
    strcpy(temp.nome, nome);
    strcpy(temp.descricao, descricao);
    temp.dropaItem = dropaItem;
    temp.temMonstro = temMonstro;
    temp.recuperaStatus = recuperaStatus;
    return temp;
}

// Fun��o para inicializar a lista
void cria_lista(No_descritor* novaLista) {
    novaLista->tamanho = 0; // Inicializa o tamanho da lista como 0
    novaLista->primeiro = NULL; // A lista come�a vazia
    novaLista->ultimo = NULL; // N�o h� �ltimo n� na lista vazia
}

// Fun��o para criar um novo n� com dados fornecidos
No* cria_no(Dados novoDado) {
    No* novoNo = (No*) malloc(sizeof(No)); // Aloca mem�ria para um novo n�
    if (novoNo) {
        novoNo->dados = novoDado; // Armazena os dados no novo n�
        novoNo->prox = NULL; // Inicializa o ponteiro para o pr�ximo n� como NULL
        return novoNo; // Retorna o novo n� criado
    }
    else return NULL; // Retorna NULL se a aloca��o falhar
}

// Fun��o para inserir um n� em uma lista que est� vazia
void insere_no_na_lista_vazia(No* novoNo, No_descritor* ponteiroNoDescritor) {
    ponteiroNoDescritor->primeiro = novoNo; // O novo n� se torna o primeiro
    ponteiroNoDescritor->ultimo = novoNo; // O novo n� se torna o �ltimo
    ponteiroNoDescritor->tamanho = 1; // Atualiza o tamanho da lista
}

// Fun��o para inserir um n� no in�cio da lista
void insere_no_comeco(No_descritor* ponteiroNoDescritor, Dados novoDado) {
    No* novoNo = cria_no(novoDado); // Cria um novo n�
    if (novoNo) { // Verifica se o novo n� foi criado com sucesso
        if (ponteiroNoDescritor->tamanho == 0) { // Se a lista estiver vazia
            insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere no n� vazio
        } else { // Se a lista n�o estiver vazia
            No* primeiroNo = ponteiroNoDescritor->primeiro; // Salva o primeiro n� atual
            ponteiroNoDescritor->primeiro = novoNo; // O novo n� se torna o primeiro
            novoNo->prox = primeiroNo; // O novo n� aponta para o antigo primeiro n�
            ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
        }
    }
}

// Fun��o para inserir um n� no final da lista
void insere_no_final(No_descritor* ponteiroNoDescritor, Dados novoDado) {
    No* novoNo = cria_no(novoDado); // Cria um novo n�
    if (novoNo) { // Verifica se o novo n� foi criado com sucesso
        if (ponteiroNoDescritor->tamanho == 0) { // Se a lista estiver vazia
            insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere no n� vazio
        } else { // Se a lista n�o estiver vazia
            ponteiroNoDescritor->ultimo->prox = novoNo; // O atual �ltimo n� aponta para o novo n�
            ponteiroNoDescritor->ultimo = novoNo; // O novo n� se torna o �ltimo
            ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
        }
    }
}


// Fun��o para inserir um n� em uma posi��o espec�fica (meio da lista)
void insere_no_meio(No_descritor* ponteiroNoDescritor, Dados novoDado, int indice) {
    // Se a lista estiver vazia, insira o n� como o �nico elemento
    if (ponteiroNoDescritor->tamanho == 0) {
        No* novoNo = cria_no(novoDado); // Cria um novo n�
        if (novoNo) insere_no_na_lista_vazia(novoNo, ponteiroNoDescritor); // Insere na lista vazia
    } else if ((ponteiroNoDescritor->tamanho - 1) < indice) { // Se o �ndice for maior que o tamanho
        insere_no_final(ponteiroNoDescritor, novoDado); // Insere no final
    } else if (indice == 0) { // Se o �ndice for 0, insira no in�cio
        insere_no_comeco(ponteiroNoDescritor, novoDado); // Insere no come�o
    } else { // Para inser��o no meio
        No* novoNo = cria_no(novoDado); // Cria um novo n�
        No* anterior = ponteiroNoDescritor->primeiro; // Come�a do primeiro n�
        int i = 1; // Contador para percorrer a lista
        while (i < indice) { // Enquanto n�o chegar ao �ndice desejado
            anterior = anterior->prox; // Move para o pr�ximo n�
            i++;
        }
        novoNo->prox = anterior->prox; // O novo n� aponta para o n� na posi��o desejada
        anterior->prox = novoNo; // O n� anterior aponta para o novo n�
        ponteiroNoDescritor->tamanho++; // Incrementa o tamanho da lista
    }
}

// Fun��o para substituir os dados de um n� em uma posi��o espec�fica
void substitui_no_indice(No_descritor* ponteiroNoDescritor, Dados novoDado, int indice) {
    if (indice < ponteiroNoDescritor->tamanho) { // Verifica se o �ndice � v�lido
        No* atual = ponteiroNoDescritor->primeiro; // Come�a do primeiro n�
        for (int i = 0; i < indice; i++) { // Percorre at� o �ndice desejado
            atual = atual->prox; // Move para o pr�ximo n�
        }
        atual->dados = novoDado; // Substitui os dados do n� atual
    }
}

// Fun��o para mostrar todos os n�s da lista
void mostra_lista_completa(No_descritor* enderecoNoDescritor) {
    No* atual = enderecoNoDescritor->primeiro; // Come�a do primeiro n�
    int i = 0; // Contador de �ndice
    printf("Temos %d campos\n", enderecoNoDescritor->tamanho); // Mostra a quantidade de n�s
    while (atual != NULL) { // Enquanto houver n�s
        printf("Indice %d: %s\n%s\n\n", i, atual->dados.nome, atual->dados.descricao); // Mostra o �ndice e o valor
        atual = atual->prox; // Move para o pr�ximo n�
        i++;
    }
}

// Fun��o para mostrar o n� em um �ndice espec�fico
void mostra_no_indice(No_descritor* ponteiroNoDescritor, int indice) {
    if (indice < ponteiroNoDescritor->tamanho) { // Verifica se o �ndice � v�lido
        No* atual = ponteiroNoDescritor->primeiro; // Come�a do primeiro n�
        int i = 0; // Contador de �ndice
        while (i < indice) { // Percorre at� o �ndice desejado
            atual = atual->prox; // Move para o pr�ximo n�
            i++;
        }
        printf("Indice %d: %s\n%s\n\n", i, atual->dados.nome, atual->dados.descricao); // Mostra o �ndice e o valor do n�
    }
}

// Fun��o para deletar o n� do come�o da lista
void deleta_no_comeco(No_descritor* ponteiroNoDescritor) {
    No* deletar = ponteiroNoDescritor->primeiro; // Ponto para o n� que ser� deletado
    ponteiroNoDescritor->primeiro = ponteiroNoDescritor->primeiro->prox; // Atualiza o primeiro n�
    free(deletar); // Libera a mem�ria do n� deletado
    ponteiroNoDescritor->tamanho--; // Decrementa o tamanho da lista
}

// Fun��o para deletar o n� do final da lista
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

// Fun��o para deletar o n� num indice espec�fico da lista
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

// Fun��o para deletar todos os n�s da lista
void deleta_lista_completa(No_descritor* enderecoNoDescritor){ // recebe o ponteiro do N� Descritor
    if(enderecoNoDescritor->tamanho>0) {
    No* atual = enderecoNoDescritor->primeiro; //cria um ponteiro auxiliar que recebe o primeiro item da lista
    No* deletar; 
    for(int i=0; i<enderecoNoDescritor->tamanho; i++){
        deletar = atual;  // guarda o atual num ponteiro auxiliar chamado deletar
        atual = atual->prox; // o atual vira o pr�ximo
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
    No_descritor mapa; // minha lista � uma vari�vel tipo n� descritor
    cria_lista(&mapa);
    // mo
    Dados cenario, bau, turno, oasis;
    cenario = constructor("Era uma vez...", "Em um mundo onde a magia flui dos elementos, o reino de Eldorion esconde nas profundezas de suas ru�nas a JOIA DE SERAPHEL. Aquele que a possuir ter� o poder de controlar todos os elementos da natureza, um segredo perdido e cobi�ado por for�as sombrias.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    cenario = constructor("Sua Miss�o:", "Voc� � Lira Valen, uma maga que domina luz e sombras, enviada pela Guilda dos Arcanos para recuperar a joia de Seraphel. Voc� deve atravessar Sylvarim, enfrentar as criaturas da Caverna do �ter e desvendar os mist�rios das ru�nas de Eldorion antes que for�as sombrias a obtenham.", 1, 0, 0);
    insere_no_final(&mapa, cenario);
    // nesse de cima a gente poderia dropar as armas da Lira e j� colocar no invent�rio. Tipo: "Voc� recebeu uma espada!\n" "Voc� recebeu 1 po��o de hp\n" etc. todo o starter pack. E depois fazer assim: "seus itens foram adicionados ao invent�rio."
    
    cenario = constructor("Sylvarim", "Voc� adentra a floresta de Sylvarim, onde a luz filtra-se pelas copas das �rvores, criando padr�es m�sticos no ch�o. O ar � denso com magia antiga, e criaturas espreitam nas sombras. Druidas observam de longe, sussurrando feiti�os enquanto a vegeta��o parece ter vida pr�pria.",0,0,0);
    insere_no_final(&mapa, cenario);
    turno = constructor("H� algo errado...", "� medida que avan�a, o ar se torna pesado, e um som gutural ecoa pela escurid�o. Sussurros de perigo te cercam. Das sombras, criaturas surgem, olhos brilhando com inten��o predat�ria. Seu cora��o acelera. Voc� est� prestes a enfrentar monstros perigosos.", 0,1,0);
    insere_no_final(&mapa, turno);

    bau = constructor("Bau", "Diante de voc�, um ba� antigo emite um leve brilho. O som das dobradi�as rangendo ecoa pela sala quando voc� o abre lentamente. Dentro, reluzem itens valiosos. A sensa��o de descoberta � palp�vel. Voc� encontrou um tesouro raro!", 1, 0, 0);
    insere_no_final(&mapa, bau);
    oasis = constructor("Pelos deuses!", "Voc� encontra uma fonte m�gica cercada por cristais reluzentes. A �gua iridescente brilha sob a luz, emanando uma energia tranquilizadora. Ao se agachar para beber, uma onda de vitalidade envolve seu corpo, restaurando rapidamente seus HP e MP. � um verdadeiro elixir da vida!", 0,0,1);
    insere_no_final(&mapa, oasis);

    cenario = constructor("Caverna do Eter", "Ao cruzar o limiar da Caverna do �ter, a realidade se distorce. O tempo parece hesitar, o ch�o pulsa com uma energia et�rea, e as paredes brilham com runas flutuantes. Cada passo ecoa em m�ltiplas dire��es, como se voc� estivesse em mais de um lugar ao mesmo tempo.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    turno = constructor("O que � isso?", "O ch�o vibra sob seus p�s, e um grito agudo corta o sil�ncio. De repente, monstros emergem da terra, com garras afiadas e presas prontas para atacar. N�o h� escapat�ria: � lutar ou perecer. Prepare-se para o combate.", 0,1,0);
    insere_no_final(&mapa, turno);

    cenario = constructor("Ruinas de Eldorion", "As ru�nas de Eldorion emergem da n�voa, uma cidade antiga tomada pelo sil�ncio. Pedras quebradas e colunas ca�das escondem segredos ancestrais. Armadilhas m�gicas ativam ao menor toque, enquanto sussurros ecoam pelas paredes, lembrando de um poder perdido h� eras.", 0, 0, 0);
    insere_no_final(&mapa, cenario);
    bau = constructor("Bau", "Ao explorar um canto esquecido, voc� trope�a em um ba� enferrujado, com inscri��es antigas. Com um esfor�o, voc� consegue abri-lo. Dentro, reluzem itens preciosos que poderiam mudar o rumo de sua aventura. Um sorriso surge em seu rosto ? a sorte sorriu para voc�!", 1, 0, 0);
    insere_no_final(&mapa, bau);
    turno = constructor("Voc� continua caminhando, at� que...", "Ao dobrar a esquina, uma presen�a sombria se faz sentir. Criaturas monstruosas aparecem, bloqueando seu caminho, seus corpos deformados pelas energias malignas. O ar vibra com tens�o, e voc� sabe que n�o h� como evitar a batalha.", 0,1,0);
    insere_no_final(&mapa, turno);
    
    mostra_lista_completa(&mapa);


    return 0;
}