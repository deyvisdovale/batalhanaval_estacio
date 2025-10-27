#include <stdio.h>

#define TAM 10       // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3      // Valor que representa uma parte do navio
#define AGUA 0       // Valor que representa a água
#define TAMANHO_NAVIO 3 // Cada navio ocupa 3 posições

int main() {
    int tabuleiro[TAM][TAM]; // Matriz que representa o tabuleiro
    int i, j;

    // ---------------------------
    // 1. Inicializar o tabuleiro
    // ---------------------------
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA; // Preenche todas as posições com 0 (água)
        }
    }

    // -----------------------------------
    // 2. Definir coordenadas dos navios
    // -----------------------------------
    // Coordenadas iniciais do navio horizontal
    int linha_h = 2; // Linha onde o navio horizontal começa
    int coluna_h = 4; // Coluna inicial do navio horizontal

    // Coordenadas iniciais do navio vertical
    int linha_v = 5; // Linha onde o navio vertical começa
    int coluna_v = 7; // Coluna inicial do navio vertical

    // -------------------------------------------------
    // 3. Posicionar o navio horizontal (3 posições)
    // -------------------------------------------------
    // Verifica se cabe no tabuleiro (coluna + tamanho <= limite)
    if (coluna_h + TAMANHO_NAVIO <= TAM) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_h][coluna_h + i] = NAVIO;
        }
    } else {
        printf("Erro: o navio horizontal ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // -------------------------------------------------
    // 4. Posicionar o navio vertical (3 posições)
    // -------------------------------------------------
    // Verifica se cabe no tabuleiro (linha + tamanho <= limite)
    if (linha_v + TAMANHO_NAVIO <= TAM) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            // Garante que não haja sobreposição com o navio horizontal
            if (tabuleiro[linha_v + i][coluna_v] == AGUA) {
                tabuleiro[linha_v + i][coluna_v] = NAVIO;
            } else {
                printf("Erro: sobreposição detectada! Navios se cruzam.\n");
                return 1;
            }
        }
    } else {
        printf("Erro: o navio vertical ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // --------------------------------------------
    // 5. Exibir o tabuleiro no console
    // --------------------------------------------
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");
    printf("Legenda: 0 = Água | 3 = Navio\n\n");

    // Imprime a matriz completa (10x10)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nNavios posicionados com sucesso!\n");
    return 0;
}
