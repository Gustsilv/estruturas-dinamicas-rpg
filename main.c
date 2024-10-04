#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "filaComNoDescritor.h"



int main(){
    setlocale(LC_ALL, "");
    No_descritor mapa; // minha lista é uma variável tipo nó descritor
    No cenario;
    cria_lista(&mapa);
    inicializa_cenarios(&mapa);

    //a gente poderia perguntar o nome do jogador aqui, e inserir no nome do personagem ao invés de "Lira Valen".

    
    while(mapa.tamanho){
        cenario = deleta_no_comeco_e_retorna_dados(&mapa);

        printf("\n| %s |\n", cenario.dados.nome);
        printf("\n%s\n", cenario.dados.descricao);
        
        if(cenario.dados.dropaItem){
            //codigo referente à dropagem de item
        }
        if(cenario.dados.temMonstro){
            //codigo referente ao turno
        }
        if(cenario.dados.recuperaStatus){
            //codigo referente ao oasis
        }
    }
    
    
    
    deleta_lista_completa(&mapa);

    return 0;
}