/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include "grafo.h"
void tabela_imprime(tabela_dispersao *tab);

tabela_dispersao *tabela_nova(int capacidade, hash_func *hfunc, sond_func *sfunc)
{

    if (capacidade < 0 || !hfunc || !sfunc)
    {
        return NULL;
    }
    tabela_dispersao *tab = (tabela_dispersao *)malloc(sizeof(tabela_dispersao));
    if (!tab)
    {
        return NULL;
    }
    //criar vetor de estados das celucas tudo a 0
    tab->estado_celulas = (int *)malloc(sizeof(int) * capacidade);
    if (!tab->estado_celulas)
    {
        free(tab);
        return NULL;
    }

    for (int i = 0; i < capacidade; i++)
    {
        tab->estado_celulas[i] = 0;
    }

    //criar memoria para os elementos
    tab->nos = (no_grafo **)calloc(capacidade, sizeof(no_grafo *));
    if (!tab->nos)
    {
        //se nao conseguir alocar a memoria apaga a tabela
        free(tab);
        return NULL;
    }
    //passa os parametros para a tabela
    tab->capacidade = capacidade;
    tab->hfunc = hfunc;
    tab->sfunc = sfunc;

    return tab;
}

int tabela_adiciona(tabela_dispersao *td, no_grafo *entrada)
{
    //tentar fazer uma funcao para nao repetirmos o codigo
    if (!td || !entrada)
    {
        return -1;
    }
    //temos que ver se o estado do index é -1 ou 1 pq so podemos inserir no 0;
    unsigned long index;
    //while difernte de 0 condição de saida quando encountrou
    index = td->hfunc(entrada->cidade, td->capacidade);
    if (td->estado_celulas[index] == 1 || td->estado_celulas[index] == -1)
    {
        unsigned long index2=index;
        int count = 1;
        while(td->estado_celulas[index2]!=0)
        { //descobrir qual a proxima posicao disponivel
            index2 = td->sfunc(index, count, td->capacidade);
            //aumenta o numero de tentativas que fizemos
            count++;
        }
        td->nos[index2] = entrada;
        td->estado_celulas[index2] = 1;
        td->tamanho++;
        return index2;
    }
    else //se o estado da posicao que hash deu for 0 podemos guardar la a entrada
    {
        td->nos[index] = entrada;
        td->estado_celulas[index] = 1;
        td->tamanho++;

        return index;
    }

    return -1;
}

int tabela_remove(tabela_dispersao *td, no_grafo *saida)
{
    if (!td || !saida)
    {
        return -1;
    }
    //descobrir a posicao
    unsigned long index;
    index = td->hfunc(saida->cidade, td->capacidade);
    if (td->estado_celulas[index] == 0 )
    {
        return -1;
    }
    unsigned long index2 = index;
    int count =1;
    while(td->estado_celulas[index2]!=0)
    { //descobrir qual a posicao disponivel
       if(td->estado_celulas[index2]!=-1){
        if (!strcmp(saida->cidade, td->nos[index2]->cidade))
        {
            break;
        }
    }
        index2 = td->sfunc(index, count, td->capacidade);
        //aumenta o numero de tentativas que fizemos
        count++;
    }
    //este nó é o que queremos remover
    if(td->estado_celulas[index2]==0) return -1;

    td->estado_celulas[index2] = -1;
   td->tamanho--;
    td->nos[index2]=NULL;

    return 0;
}

void tabela_apaga(tabela_dispersao *td)
{
    if (!td)
    {
        return;
    }
    //vamos a cada posicao do vetor e verificamos se esta NULL
    for (int i = 0; i < td->capacidade; i++)
    {
        //se nao estiver fazemos free
        if (td->estado_celulas[i]==1)
        {
            td->nos[i]=NULL;
        }
    }
        free(td->nos);
        free(td);
        td = NULL;
}

int tabela_existe(tabela_dispersao *td, const char *cidade)
{
    if (!td || !cidade)
    {
        return -1;
    }
    int indice = -1;

    for (int i = 0; i < td->capacidade; i++)
    {
        if (td->estado_celulas[i] == 1)
        {
            if (strcmp(td->nos[i]->cidade, cidade) == 0)
            {
                indice = i;
            }
        }
    }

    return indice;
}

tabela_dispersao *tabela_carrega(grafo *g, int tamanho)
{
    if (!g || tamanho < 0)
    {
        return NULL;
    }
    tabela_dispersao *tab = tabela_nova(tamanho, hash_krm, sond_rh);
    if (!tab)
    {
        return NULL;
    }

    for (int i = 0; i < g->tamanho; i++)
    {
        if (tabela_adiciona(tab, g->nos[i]) == -1)
        {
            return NULL;
        }
    }

    return tab;
}

 void tabela_imprime(tabela_dispersao *tab)
{
    if (!tab)
    return;
    for (int i = 0; i < tab->capacidade; i++)
    {
        if(tab->estado_celulas[i]==1){
            printf("[%d] estado: %d, cidade- %s \n", i,tab->estado_celulas[i], tab->nos[i]->cidade);
        }

    }
}


/*================================================================================*/
unsigned long sond_rh(int pos, int tentativas, int tamanho)
{

    return (pos + tentativas * tentativas) % tamanho;
}

unsigned long hash_krm(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)chave[c];
    }

    return hash % tamanho;

    return 0;
}
