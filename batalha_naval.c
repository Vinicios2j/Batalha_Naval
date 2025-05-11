#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10
#define AGUA '~'
#define NAVIO '#'
#define ACERTO '*'
#define ERRO 'X'

char tabuleiroJogador[TAM][TAM];
char tabuleiroComputador[TAM][TAM];

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibirTabuleiro(char tabuleiro[TAM][TAM], int ocultar) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (ocultar && tabuleiro[i][j] == NAVIO)
                printf("%c ", AGUA);
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavio(char tabuleiro[TAM][TAM], int tamanho) {
    int x, y, orientacao;
    int valido;
    do {
        valido = 1;
        x = rand() % TAM;
        y = rand() % TAM;
        orientacao = rand() % 2; // 0 = horizontal, 1 = vertical

        if (orientacao == 0 && y + tamanho > TAM) valido = 0;
        if (orientacao == 1 && x + tamanho > TAM) valido = 0;

        if (valido) {
            for (int i = 0; i < tamanho; i++) {
                if (tabuleiro[x + (orientacao ? i : 0)][y + (!orientacao ? i : 0)] != AGUA) {
                    valido = 0;
                    break;
                }
            }
        }

        if (valido) {
            for (int i = 0; i < tamanho; i++) {
                tabuleiro[x + (orientacao ? i : 0)][y + (!orientacao ? i : 0)] = NAVIO;
            }
        }
    } while (!valido);
    return 1;
}

void posicionarTodosNavios(char tabuleiro[TAM][TAM]) {
    posicionarNavio(tabuleiro, 5); // Porta-aviões
    posicionarNavio(tabuleiro, 4); // Navio-tanque
    posicionarNavio(tabuleiro, 3); // Contratorpedeiro
    posicionarNavio(tabuleiro, 2); // Submarino
}

int realizarTiro(char tabuleiro[TAM][TAM], int x, int y) {
    if (tabuleiro[x][y] == NAVIO) {
        tabuleiro[x][y] = ACERTO;
        printf("Acertou!\n");
        return 1;
    } else if (tabuleiro[x][y] == AGUA) {
        tabuleiro[x][y] = ERRO;
        printf("Errou!\n");
    } else {
        printf("Já atirou aqui.\n");
    }
    return 0;
}

int verificarFim(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == NAVIO) return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));
    int x, y;

    inicializarTabuleiro(tabuleiroJogador);
    inicializarTabuleiro(tabuleiroComputador);

    posicionarTodosNavios(tabuleiroJogador);
    posicionarTodosNavios(tabuleiroComputador);

    while (1) {
        printf("\n--- Seu tabuleiro ---\n");
        exibirTabuleiro(tabuleiroJogador, 0);
        printf("\n--- Tabuleiro do computador ---\n");
        exibirTabuleiro(tabuleiroComputador, 1);

        printf("Digite a coordenada para atirar (linha coluna): ");
        scanf("%d %d", &x, &y);
        realizarTiro(tabuleiroComputador, x, y);

        if (verificarFim(tabuleiroComputador)) {
            printf("\nParabéns! Você venceu!\n");
            break;
        }

        x = rand() % TAM;
        y = rand() % TAM;
        printf("Computador atira em %d %d\n", x, y);
        realizarTiro(tabuleiroJogador, x, y);

        if (verificarFim(tabuleiroJogador)) {
            printf("\nVocê perdeu. O computador venceu.\n");
            break;
        }
    }

    return 0;
}