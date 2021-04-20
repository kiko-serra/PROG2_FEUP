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
    pilha *p = pilha_nova();
    vetor *vec=vetor_novo();
    vetor *vec2=vetor_novo();
    for (int i = 0; i < expressoes->tamanho; i++)
    {
        vetor_insere(vec, expressoes->elementos[i].str, -1);
    }
    for (int i = 0; i < expressoes->tamanho; i++)
    {
        vetor_insere(vec2, expressoes->elementos[i].str, -1);
    }
    
    //imprime_vetor(expressoes);
    if (ficheiro == NULL || expressoes == NULL)
    {
        return 0;
    }
    FILE *f = ficheiro;

    int flag = 0;
    int i = 0;
    for (int i = 0; i < vetor_tamanho(expressoes); i++)
    {
        //nao esta a inserir nada na pilha provavelmente porque
        //nao esta a ler bem
        char *token = strtok(expressoes->elementos[i].str, "(");

        while (token != NULL)
        {
            if (!strcmp(token, "("))
            {
                pilha_push(p, token);
            }

            token = strtok(NULL, "(");
        }
        printf("%d\n", pilha_tamanho(p));
        char *token2 = strtok(vec->elementos[i].str, ")");

        while (token2 != NULL)
        {
            if (!strcmp(token2, ")"))
            {
                if (pilha_tamanho(p) > 0)
                {
                    pilha_pop(p);
                }
                else
                    //escrever na equacao que NOK
                    flag = 1;
            }

            token2 = strtok(NULL, ")");
        }
        if (pilha_tamanho(p)>0)
        {
            flag=1;
        }
        else if (!pilha_tamanho(p))
        {
            flag=0;
        }
        else
            return 0;
        
        if (flag == 0)
        {
            fprintf(f, " %s -> OK\n", vec2->elementos[i].str, stdout);
        }
        if (flag == 1)
        {
            fprintf(f, "%s -> NOK\n", vec2->elementos[i].str, stdout);
        }
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