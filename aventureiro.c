#include <stdio.h>

#define TAM 10              // Tamanho fixo do tabuleiro (10x10)
#define NAVIO 3             // Valor que representa uma parte do navio
#define AGUA 0              // Valor que representa a água
#define TAMANHO_NAVIO 3     // Cada navio ocupa 3 posições

// Função auxiliar para verificar se uma posição está livre
int posicao_livre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return (tabuleiro[linha][coluna] == AGUA);
}

// Função para imprimir o tabuleiro formatado
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");
    printf("Legenda: 0 = Água | 3 = Navio\n\n");

    // Cabeçalho das colunas
    printf("   ");
    for (int c = 0; c < TAM; c++) printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i); // Índice da linha
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // ---------------------------
    // 1. Inicializar o tabuleiro
    // ---------------------------
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // ---------------------------------------------------
    // 2. Definir coordenadas iniciais dos quatro navios
    // ---------------------------------------------------
    // Navio 1 - Horizontal
    int linha_h = 2, coluna_h = 1;

    // Navio 2 - Vertical
    int linha_v = 5, coluna_v = 7;

    // Navio 3 - Diagonal principal (↘)
    int linha_d1 = 0, coluna_d1 = 0;

    // Navio 4 - Diagonal secundária (↙)
    int linha_d2 = 1, coluna_d2 = 8;

    // -------------------------------------------------------
    // 3. Posicionar o navio horizontal (verificação de limite)
    // -------------------------------------------------------
    if (coluna_h + TAMANHO_NAVIO <= TAM) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (posicao_livre(tabuleiro, linha_h, coluna_h + i))
                tabuleiro[linha_h][coluna_h + i] = NAVIO;
            else {
                printf("Erro: sobreposição detectada no navio horizontal!\n");
                return 1;
            }
        }
    } else {
        printf("Erro: o navio horizontal ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // -------------------------------------------------------
    // 4. Posicionar o navio vertical (verificação de limite)
    // -------------------------------------------------------
    if (linha_v + TAMANHO_NAVIO <= TAM) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (posicao_livre(tabuleiro, linha_v + i, coluna_v))
                tabuleiro[linha_v + i][coluna_v] = NAVIO;
            else {
                printf("Erro: sobreposição detectada no navio vertical!\n");
                return 1;
            }
        }
    } else {
        printf("Erro: o navio vertical ultrapassa os limites do tabuleiro!\n");
        return 1;
    }

    // --------------------------------------------------------------
    // 5. Posicionar o navio diagonal ↘ (linha e coluna crescem)
    // --------------------------------------------------------------
    if (linha_d1 + TAMANHO_NAVIO <= TAM && coluna_d1 + TAMANHO_NAVIO <= TAM) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (posicao_livre(tabuleiro, linha_d1 + i, coluna_d1 + i))
                tabuleiro[linha_d1 + i][coluna_d1 + i] = NAVIO;
            else {
                printf("Erro: sobreposição detectada no navio diagonal ↘!\n");
                return 1;
            }
        }
    } else {
        printf("Erro: o navio diagonal ↘ ultrapassa os limites!\n");
        return 1;
    }

    // --------------------------------------------------------------
    // 6. Posicionar o navio diagonal ↙ (linha cresce, coluna decresce)
    // --------------------------------------------------------------
    if (linha_d2 + TAMANHO_NAVIO <= TAM && coluna_d2 - (TAMANHO_NAVIO - 1) >= 0) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (posicao_livre(tabuleiro, linha_d2 + i, coluna_d2 - i))
                tabuleiro[linha_d2 + i][coluna_d2 - i] = NAVIO;
            else {
                printf("Erro: sobreposição detectada no navio diagonal ↙!\n");
                return 1;
            }
        }
    } else {
        printf("Erro: o navio diagonal ↙ ultrapassa os limites!\n");
        return 1;
    }

    // --------------------------------------------
    // 7. Exibir o tabuleiro completo
    // --------------------------------------------
    exibir_tabuleiro(tabuleiro);
    printf("\nNavios posicionados com sucesso!\n");

    return 0;
}
