#include <stdio.h>
#include "sistema_experiencia.h"

int main() {
    node *inicio = NULL;

    // Criar personagem principal
    criar_personagem(&inicio, "Lira Valen", 100, 50, 20, 15);

    // Simula��o de derrotar inimigos e ganhar experi�ncia
    int xp_ganho;
    for (int i = 1; i <= 5; i++) { // Simulando 5 inimigos derrotados
        xp_ganho = 80; // XP ganho por inimigo derrotado
        printf("Derrotando inimigo %d, ganhando %d XP...\n", i, xp_ganho);
        adicionar_experiencia(inicio, xp_ganho);
        ler_personagem(inicio); // L� e imprime os dados do personagem
    }

    // Liberar mem�ria (opcional, j� que o programa termina)
    // Libere a mem�ria alocada quando n�o precisar mais do personagem

    return 0;
}
