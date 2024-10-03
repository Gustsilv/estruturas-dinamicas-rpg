#include "filaComNoDescritor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

// Função para deletar o nó do começo da lista
No deleta_no_comeco_e_retorna_dados(No_descritor* ponteiroNoDescritor) {
    No* deletar = ponteiroNoDescritor->primeiro; // Ponteiro para o nó que será deletado
    No temp = (*deletar); // guarda os dados desse nó
    ponteiroNoDescritor->primeiro = ponteiroNoDescritor->primeiro->prox; // Atualiza o primeiro nó
    free(deletar); // Libera a memória do nó deletado
    ponteiroNoDescritor->tamanho--; // Decrementa o tamanho da lista
    return temp; // retorna os dados para serem usados na main
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
    if(atual == NULL) printf("\nLista apagada!!!! GAME OVER\n");
    enderecoNoDescritor->primeiro=NULL;
    enderecoNoDescritor->ultimo=NULL;
    enderecoNoDescritor->tamanho=0;
    }
}

void inicializa_cenarios(No_descritor* mapa){
    Dados cenario, bau, turno, oasis;

    cenario = constructor("Era uma vez...", "Em um mundo onde a magia flui dos elementos, o reino de Eldorion esconde nas profundezas de suas ruínas a JOIA DE SERAPHEL.\nAquele que a possuir terá o poder de controlar todos os elementos da natureza, um segredo perdido e cobiçado por forças sombrias...\n", 0, 0, 0);
    insere_no_final(mapa, cenario);
    cenario = constructor("Sua Missão:", "Você é Lira Valen, uma maga enviada pela Guilda dos Arcanos para recuperar a joia de Seraphel.\nVocê deve atravessar a FLORESTA DE SYLVARIM, enfrentar as criaturas da CAVERNA DO ÉTER e desvendar os mistérios das RUÍNAS DE ELDORION antes que as forças sombrias a obtenham.", 1, 0, 0);
    insere_no_final(mapa, cenario);
    // nesse de cima a gente poderia dropar as armas da Lira e já colocar no inventário. Tipo: "Você recebeu uma espada!\n" "Você recebeu 1 poção de hp\n" etc. todo o starter pack. E depois fazer assim: "seus itens foram adicionados ao inventário."
    
    cenario = constructor("Floresta", "Você adentra a floresta de Sylvarim, onde a luz filtra-se pelas copas das árvores, criando padrões místicos no chão. O ar é denso com magia antiga, e criaturas espreitam nas sombras. Druidas observam de longe, sussurrando feitiços enquanto a vegetação parece ter vida própria.",0,0,0);
    insere_no_final(mapa, cenario);
    turno = constructor("Há algo errado...", "À medida que avança, o ar se torna pesado, e um som gutural ecoa pela escuridão. Sussurros de perigo te cercam. Das sombras, criaturas surgem, olhos brilhando com intenção predatória. Seu coração acelera. Você está prestes a enfrentar monstros perigosos.", 0,1,0);
    insere_no_final(mapa, turno);
    bau = constructor("Bau", "Diante de você, um baú antigo emite um leve brilho. O som das dobradiças rangendo ecoa pela sala quando você o abre lentamente. Dentro, reluzem itens valiosos. A sensação de descoberta é palpável. Você encontrou um tesouro raro!", 1, 0, 0);
    insere_no_final(mapa, bau);
    oasis = constructor("Pelos deuses!", "Você encontra uma fonte mágica cercada por cristais reluzentes. A água iridescente brilha sob a luz, emanando uma energia tranquilizadora. Ao se agachar para beber, uma onda de vitalidade envolve seu corpo, restaurando rapidamente seus HP e MP. É um verdadeiro elixir da vida!", 0,0,1);
    insere_no_final(mapa, oasis);

    cenario = constructor("Caverna do Eter", "Ao cruzar o limiar da Caverna do Éter, a realidade se distorce. O tempo parece hesitar, o chão pulsa com uma energia etérea, e as paredes brilham com runas flutuantes. Cada passo ecoa em múltiplas direções, como se você estivesse em mais de um lugar ao mesmo tempo.", 0, 0, 0);
    insere_no_final(mapa, cenario);
    turno = constructor("O que é isso?", "O chão vibra sob seus pés, e um grito agudo corta o silêncio. De repente, monstros emergem da terra, com garras afiadas e presas prontas para atacar. Não há escapatória: é lutar ou perecer. Prepare-se para o combate.", 0,1,0);
    insere_no_final(mapa, turno);

    cenario = constructor("Ruinas de Eldorion", "As ruínas de Eldorion emergem da névoa, uma cidade antiga tomada pelo silêncio. Pedras quebradas e colunas caídas escondem segredos ancestrais. Armadilhas mágicas ativam ao menor toque, enquanto sussurros ecoam pelas paredes, lembrando de um poder perdido há eras.", 0, 0, 0);
    insere_no_final(mapa, cenario);
    bau = constructor("Bau", "Ao explorar um canto esquecido, você tropeça em um baú enferrujado, com inscrições antigas. Com um esforço, você consegue abri-lo. Dentro, reluzem itens preciosos que poderiam mudar o rumo de sua aventura. Um sorriso surge em seu rosto ? a sorte sorriu para você!", 1, 0, 0);
    insere_no_final(mapa, bau);
    turno = constructor("Você continua caminhando, até que...", "Ao dobrar a esquina, uma presença sombria se faz sentir. Criaturas monstruosas aparecem, bloqueando seu caminho, seus corpos deformados pelas energias malignas. O ar vibra com tensão, e você sabe que não há como evitar a batalha.", 0,1,0);
    insere_no_final(mapa, turno);
}