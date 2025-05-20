#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Funções para inicialização e exibição do tabuleiro
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n  ");
    for (int j = 0; j < TAMANHO; j++) printf("%2d", j);
    printf("\n");
    
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    printf("\nLegenda:\n");
    printf("%d - Água\n", AGUA);
    printf("%d - Navio\n", NAVIO);
    printf("%d - Área de habilidade\n", HABILIDADE);
}

// Funções para criar matrizes de habilidades
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cone apontando para baixo (formato triangular)
            habilidade[i][j] = (j >= centro - i && j <= centro + i) ? 1 : 0;
        }
    }
}

void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz com centro no meio
            habilidade[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Formato de losango (octaedro visto de frente)
            int dist = abs(i - centro) + abs(j - centro);
            habilidade[i][j] = (dist <= centro) ? 1 : 0;
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                      int linha, int coluna) {
    int offset = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tab_i = linha - offset + i;
            int tab_j = coluna - offset + j;
            
            // Verifica se está dentro do tabuleiro e se a habilidade afeta esta posição
            if (tab_i >= 0 && tab_i < TAMANHO && 
                tab_j >= 0 && tab_j < TAMANHO && 
                habilidade[i][j] == 1) {
                // Marca apenas se não for navio (para visualização)
                if (tabuleiro[tab_i][tab_j] != NAVIO) {
                    tabuleiro[tab_i][tab_j] = HABILIDADE;
                }
            }
        }
    }
}

// Funções para posicionar navios (do exercício anterior)
bool posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna,
                    int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        
        if (!(nova_linha >= 0 && nova_linha < TAMANHO &&
              nova_coluna >= 0 && nova_coluna < TAMANHO)) {
            return false;
        }
        
        if (tabuleiro[nova_linha][nova_coluna] != AGUA) {
            return false;
        }
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int nova_linha = linha + i * delta_linha;
        int nova_coluna = coluna + i * delta_coluna;
        tabuleiro[nova_linha][nova_coluna] = NAVIO;
    }
    
    return true;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona alguns navios (como no exercício anterior)
    posicionarNavio(tabuleiro, 2, 3, 0, 1);  // Horizontal
    posicionarNavio(tabuleiro, 5, 7, 1, 0);  // Vertical
    posicionarNavio(tabuleiro, 1, 1, 1, 1);   // Diagonal principal
    posicionarNavio(tabuleiro, 0, 7, 1, -1);  // Diagonal secundária
    
    // Cria as matrizes de habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 7, 4);      // Cone no centro inferior
    aplicarHabilidade(tabuleiro, cruz, 3, 5);      // Cruz no meio do tabuleiro
    aplicarHabilidade(tabuleiro, octaedro, 5, 2);  // Octaedro à esquerda
    
    // Exibe o tabuleiro com navios e áreas de habilidade
    exibirTabuleiro(tabuleiro);
    
    return 0;
}