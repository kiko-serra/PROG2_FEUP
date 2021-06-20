#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/
void imprime_vetor(vetor *vec)
{
    for (int i = 0; i < vec->tamanho; i++)
    {
        printf("%s\n", vec->elementos[i].str);
    }
}
/*** problema 2 ***/
int avalia_expressoes(FILE *ficheiro, vetor *expressoes)
{
    pilha *p;

    //imprime_vetor(expressoes);
    if (ficheiro == NULL || expressoes == NULL)
    {
        return 0;
    }
    FILE *f = ficheiro;

    int i = 0;
    for (int i = 0; i < vetor_tamanho(expressoes); i++)
    {
        int flag = 0;
        p = pilha_nova();

        int n = strlen(expressoes->elementos[i].str);
        for (int j = 0; j < n; j++)
        {
            if (expressoes->elementos[i].str[j] == '(')
            {
                pilha_push(p, "(");
            }
            else if (expressoes->elementos[i].str[j] == ')')
            {
                if (pilha_vazia(p) == 1)
                {
                    flag = 1;
                }
                pilha_pop(p);
            }
        }

        if (pilha_tamanho(p) > 0)
        {
            flag = 1;
        }
        if (flag == 0)
        {
            fprintf(f, " %s -> OK\n", expressoes->elementos[i].str, stdout);
        }
        if (flag == 1)
        {
            fprintf(f, "%s -> NOK\n", expressoes->elementos[i].str, stdout);
        }
        pilha_apaga(p);
    }

    return 1;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

vetor *lerFicheiro(FILE *ficheiro)
{
    char buffer[BUFFER], *charptr;
    vetor *v;
    v = vetor_novo();
    while (fgets(buffer, BUFFER, ficheiro) != NULL)
    {
        charptr = strchr(buffer, '\n');
        if (charptr)
            *charptr = '\0';
        charptr = strchr(buffer, '\t');
        if (charptr)
            *charptr = '\0';
        if (strcmp(charptr + 1, "infixa") == 0)
            vetor_insere(v, buffer, v->tamanho);
    }
    return v;
}

int main()
{
    FILE *fin, *fout;
    vetor *expressoes = NULL;

    fin = fopen("expressoes.txt", "r");
    if (fin == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
        return 1;
    }

    fout = fopen("avaliacao.txt", "w");
    if (fout == NULL)
    {
        printf("Erro ao abrir ficheiro.\n");
        return 1;
    }

    expressoes = lerFicheiro(fin);
    if (!expressoes)
    {
        printf("Erro ao ler ficheiro de expressoes.\n");
        return 1;
    }

    if (avalia_expressoes(fout, expressoes) == 1)
        printf("Funcao terminou corretamente - verificar ficheiro avaliacao.txt\n");
    else
        printf("Funcao retornou erro.\n");

    fclose(fin);
    fclose(fout);

    return 0;
}