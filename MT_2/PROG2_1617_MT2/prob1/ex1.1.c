#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "grafo.h"

/*** problema 1.1 ***/
char *avl_maiorstring(no_avl *no)
{
    /* complexidade do algoritmo: O(n*log(n)) */
    if (!no)
    {
        return NULL;
    }

    char *str_no = no->str;
    char *str_esq = avl_maiorstring(no->esquerda);
    char *str_dir = avl_maiorstring(no->direita);
    int max, tam=0, tam_esq=0, tam_dir=0;
    if (str_no!=NULL)
    {
        tam = strlen(str_no);
    }
    if (str_esq!=NULL)
    {
        tam_esq = strlen(str_esq);
    }
    if (str_dir!=NULL)
    {
        tam_dir = strlen(str_dir);
    }
    max = tam;
    char *res=str_no;
    if (tam_esq > max)
    {
        max = tam_esq;
        res = str_esq;
    }
    if (tam_dir > max)
    {
        max = tam_dir;
        res = str_dir;
    }
    return res;
}

/*** problema 1.2 ***/
int grafo_maisdistante(grafo *g, int origem, int *distancia)
{
    if (!g || origem<0 || distancia<0)
    {
        return -1;
    }
    int v[g->tamanho];
    int n;
    for (int i = 0; i < g->tamanho; i++)
    {
        grafo_bfs(g, origem, i, &n);
        v[i]=n-1;
    }
    int max=0, pos=0;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (v[i]>max)
        {
            max=v[i];
            pos=i;
        }
        
    }
    *distancia=max;
    return pos;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    FILE *fp = fopen("paises.txt", "r");
    char str_aux[MAX_STR], *str;

    /* teste problema 1.1 */
    {
        arvore_avl *arv;
        puts("* Problema 1.1 *");
        arv = avl_nova();
        while (fgets(str_aux, MAX_STR, fp) != NULL)
        {
            if (str_aux[strlen(str_aux) - 1] == '\n')
                str_aux[strlen(str_aux) - 1] = '\0';
            avl_insere(arv, str_aux);
        }
        str = avl_maiorstring(arv->raiz);
        printf("Maior string: ");
        if (str != NULL)
            puts(str);
        else
            puts("(null)");
        avl_apaga(arv);
    }

    /* teste problema 1.2 */
    {
        grafo *g;
        int vertice, comprimento;
        puts("\n* Problema 1.2 *");
        g = grafo_novo(8, DIGRAFO);
        grafo_adiciona(g, 0, 4);
        grafo_adiciona(g, 1, 0);
        grafo_adiciona(g, 1, 5);
        grafo_adiciona(g, 2, 1);
        grafo_adiciona(g, 3, 2);
        grafo_adiciona(g, 4, 3);
        grafo_adiciona(g, 5, 4);
        grafo_adiciona(g, 6, 3);
        grafo_adiciona(g, 7, 2);
        grafo_adiciona(g, 7, 6);

        vertice = grafo_maisdistante(g, 1, &comprimento);
        if (vertice != -1)
            printf("Mais distante do vertice 1: %d (distancia %d)\n", vertice, comprimento);
        vertice = grafo_maisdistante(g, 6, &comprimento);
        if (vertice != -1)
            printf("Mais distante do vertice 6: %d (distancia %d)\n", vertice, comprimento);

        grafo_apaga(g);
    }

    fclose(fp);
    return 0;
}