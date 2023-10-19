#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS 3

void comecarTabuleiro(char tabuleiro[][TAMANHO_TABULEIRO])
{
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            tabuleiro[linha][coluna] = '~';
        }
    }
}

void mostraTab(char tabuleiro[][TAMANHO_TABULEIRO])
{
    printf("\t");
    for (int coluna = 1; coluna <= TAMANHO_TABULEIRO; coluna++)
    {
        printf("%d\t", coluna);
    }
    printf("\n");

    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        printf("%d", linha + 1);
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            printf("\t%c", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    printf("\nLegenda:\n");
    printf("N - Navio\n");
    printf("O - Navio atingido\n");
    printf("~ - Agua\n");
}

void colocarNavManual(char tabuleiro[][TAMANHO_TABULEIRO], int jogador)
{
    int linha, coluna;

    printf("Jogador %d, posicione seus navios:\n", jogador);

    for (int navio = 0; navio < NUM_NAVIOS; navio++)
    {
        printf("Posicione o Navio %d (linha e coluna inicial): ", navio + 1);
        scanf("%d %d", &linha, &coluna);

        if (linha < 1 || linha > TAMANHO_TABULEIRO || coluna < 1 || coluna > TAMANHO_TABULEIRO || tabuleiro[linha - 1][coluna - 1] == 'O')
        {
            printf("Posicao invalida. Tente novamente.\n");
            navio--;
        }
        else
        {
            tabuleiro[linha - 1][coluna - 1] = 'N'; // 'N' representa um navio
        }
    }
}

void Tiroo(int tiro[2])
{
    printf("Linha: ");
    scanf("%d", &tiro[0]);
    tiro[0]--;

    printf("Coluna: ");
    scanf("%d", &tiro[1]);
    tiro[1]--;
}

int acertou(int tiro[2], char tabuleiro[][TAMANHO_TABULEIRO])
{
    if (tabuleiro[tiro[0]][tiro[1]] == 'N')
    {
        printf("Voce acertou o tiro (%d, %d)\n", tiro[0] + 1, tiro[1] + 1);
        tabuleiro[tiro[0]][tiro[1]] = 'O'; // 'O' representa um navio atingido
        return 1;
    }
    return 0;
}

void dica(int tiro[2], char tabuleiro[][TAMANHO_TABULEIRO], int tentativa)
{
    int linha = 0, coluna = 0;

    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        if (tabuleiro[tiro[0]][i] == 'N')
            linha++;
        if (tabuleiro[i][tiro[1]] == 'N')
            coluna++;
    }

    printf("\nDica %d:\nlinha %d -> %d navios\ncoluna %d -> %d navios\n", tentativa, tiro[0] + 1, linha, tiro[1] + 1, coluna);
}

int jogadorVenceu(char tabuleiro[][TAMANHO_TABULEIRO])
{
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++)
    {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++)
        {
            if (tabuleiro[linha][coluna] == 'N')
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    char tabuleiroJogador1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiroJogador2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tiro[2];
    int tentativasJogador1 = 0, acertosJogador1 = 0;
    int tentativasJogador2 = 0, acertosJogador2 = 0;

    comecarTabuleiro(tabuleiroJogador1);
    comecarTabuleiro(tabuleiroJogador2);

    colocarNavManual(tabuleiroJogador1, 1);
    colocarNavManual(tabuleiroJogador2, 2);

    int jogadorAtual = 1;

    while (1)
    {
        printf("Tabuleiro do Jogador %d:\n", jogadorAtual);
        mostraTab(jogadorAtual == 1 ? tabuleiroJogador1 : tabuleiroJogador2);
        Tiroo(tiro);

        if (jogadorAtual == 1)
        {
            tentativasJogador1++;
            if (acertou(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1))
            {
                dica(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1, tentativasJogador1);
                acertosJogador1++;
            }
            else
            {
                dica(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1, tentativasJogador1);
            }

            if (jogadorVenceu(jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1))
            {
                printf("Jogador 1 venceu! Voce afundou todos os navios do jogador 2 em %d tentativas\n", tentativasJogador1);
                break;
            }

            jogadorAtual = 2;
        }
        else if (jogadorAtual == 2)
        {
            tentativasJogador2++;
            if (acertou(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1))
            {
                dica(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1, tentativasJogador2);
                acertosJogador2++;
            }
            else
            {
                dica(tiro, jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1, tentativasJogador2);
            }

            if (jogadorVenceu(jogadorAtual == 1 ? tabuleiroJogador2 : tabuleiroJogador1))
            {
                printf("Jogador 2 venceu! Voce afundou todos os navios do jogador 1 em %d tentativas\n", tentativasJogador2);
                break;
            }

            jogadorAtual = 1;
        }
    }

    return 0;
}