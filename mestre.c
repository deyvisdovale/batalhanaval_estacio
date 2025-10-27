#include <stdio.h>

#define TAM 10              // Tamanho do tabuleiro
#define NAVIO 3             // Valor representando navio
#define AGUA 0              // Valor representando água
#define HABILIDADE 5        // Valor representando área de efeito
#define TAM_HABILIDADE 5    // Tamanho das matrizes de habilidade (5x5)

// Função auxiliar para verificar se a posição está dentro do tabuleiro
int dentro_tabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Função auxiliar para imprimir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n===== TABULEIRO COM HABILIDADES =====\n\n");
    printf("Legenda: 0=Água | 3=Navio | 5=Área de Habilidade\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar a matriz de habilidade Cone (↘)
void criar_cone(int cone[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i))
                cone[i][j] = 1; // Dentro do cone
            else
                cone[i][j] = 0; // Fora do cone
        }
    }
}

// Função para criar a matriz de habilidade Cruz
void criar_cruz(int cruz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == meio || j == meio)
                cruz[i][j] = 1; // Parte da cruz
            else
                cruz[i][j] = 0; // Fora da cruz
        }
    }
}

// Função para criar a matriz de habilidade Octaedro (losango)
void criar_octaedro(int octa[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if ((i + j >= meio) && (j - i <= meio) && (i - j <= meio) && (i + j <= 3*meio))
                octa[i][j] = 1; // Dentro do octaedro
            else
                octa[i][j] = 0; // Fora do octaedro
        }
    }
}

// Função para aplicar a habilidade sobre o tabuleiro
void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha_tab = origem_linha + (i - meio);
            int col_tab = origem_coluna + (j - meio);
            if (dentro_tabuleiro(linha_tab, col_tab) && habilidade[i][j] == 1) {
                // Marca a área de habilidade sem substituir navios
                if (tabuleiro[linha_tab][col_tab] == AGUA)
                    tabuleiro[linha_tab][col_tab] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // ---------------------------
    // 1. Inicializar o tabuleiro
    // ---------------------------
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    // ---------------------------
    // 2. Posicionar navios
    // ---------------------------
    // Horizontal
    int linha_h = 2, coluna_h = 1;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha_h][coluna_h + i] = NAVIO;

    // Vertical
    int linha_v = 5, coluna_v = 7;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha_v + i][coluna_v] = NAVIO;

    // Diagonal ↘
    int linha_d1 = 0, coluna_d1 = 0;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha_d1 + i][coluna_d1 + i] = NAVIO;

    // Diagonal ↙
    int linha_d2 = 1, coluna_d2 = 8;
    for (int i = 0; i < 3; i++)
        tabuleiro[linha_d2 + i][coluna_d2 - i] = NAVIO;

    // ---------------------------
    // 3. Criar matrizes de habilidade
    // ---------------------------
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);

    // ---------------------------
    // 4. Definir pontos de origem das habilidades
    // ---------------------------
    int origem_cone_l = 2, origem_cone_c = 5;
    int origem_cruz_l = 6, origem_cruz_c = 2;
    int origem_octa_l = 4, origem_octa_c = 7;

    // ---------------------------
    // 5. Aplicar habilidades
    // ---------------------------
    aplicar_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);
    aplicar_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);
    aplicar_habilidade(tabuleiro, octaedro, origem_octa_l, origem_octa_c);

    // ---------------------------
    // 6. Exibir tabuleiro final
    // ---------------------------
    exibir_tabuleiro(tabuleiro);

    return 0;
}
