#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

int letraexiste(char letra)
{
    for (int j = 0; j < strlen(palavrasecreta); j++)
    {
        if(letra == palavrasecreta[j])
            return 1;
    }

    return 0;
}

int chuteserrados()
{
    int erros = 0;

    for (int i = 0; i < chutesdados; i++)
    {
        if(!letraexiste(chutes[i]))
            erros++;
    }

    return erros;
}

int enforcou()
{
    return chuteserrados() >= 5;
}

int ganhou()
{
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {
            return 0;
        }
    }

    return 1;
}

void abertura()
{
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta()
{
    char chute;
    char chute_orig;

    printf("> ");
    scanf(" %c", &chute_orig);
    chute = toupper(chute_orig);

    if (letraexiste(chute))
    {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    }
    else
    {
        printf("\nVocê errou: a palavra nao tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra)
{
    int achou = 0;

    for (int i = 0; i < chutesdados; i++)
    {
        if (chutes[i] == letra)
        {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca()
{
    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        if (jachutou(palavrasecreta[i]))
        {
            printf("%c ", palavrasecreta[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra()
{
    FILE* f;
    f = fopen("forca_palavras.txt", "r");
    if (f == 0)
    {
        printf("Nao foi possivel abrir o arquivo de palavras\n\n");
        exit(1);
    }

    int qtdedepalavras;
    fscanf(f, "%d", &qtdedepalavras);

    srand(time(0));
    int randomico = rand() % qtdedepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);

    // sprintf(palavrasecreta, "MELANCIA");
}

void adicionapalavra()
{
    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S')
    {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiusculas: ");
        scanf("%s", novapalavra);

        FILE* f;
        f = fopen("forca_palavras.txt", "r+");
        if (f == 0)
        {
            printf("Erro ao abrir arquivo de palavras\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

int main()
{
    int acertou = 0;

    escolhepalavra();
    abertura();

    do
    {
        printf("============================================================\n");
        desenhaforca();
        chuta();

    } while (!ganhou() && !enforcou());

    if (ganhou())
    {
        printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else
    {
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();

    return 0;
}
