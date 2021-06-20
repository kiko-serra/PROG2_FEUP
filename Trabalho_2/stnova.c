/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stnova.h"

estrutura *st_nova()
{
    //usando a tabela temos que descobrir uma maneira mais rapida de termos a chave de cada voo
    //descobrir algo unico de cada voo que seja mais simples

    //fazer uma funcao hash super eficiente ou nem ter que fazer de todo
    //e sondagem
    estrutura *est = (estrutura *)malloc(sizeof(estrutura));
    if (!est)
    {
        return NULL;
    }
    //criar vetor de estados das celucas
    est->estado_celulas = (int *)malloc(sizeof(int));
    if (!est->estado_celulas)
    {
        free(est);
        return NULL;
    }

    //passa os parametros para a tabela
    est->hfunc = hash_kr;
    est->sfunc = sond_r;

    return est;
}

int st_importa_grafo(estrutura *st, grafo *g)
{
    if (!st || !g)
    {
        return -1;
    }
    //copiar as funcoes feitas e mudar a funcao hash
    if (!g || g->tamanho < 0)
    {
        return -1;
    }

    st->estado_celulas = (int *)realloc(st->estado_celulas, sizeof(int) *2* g->tamanho);
    if (!st->estado_celulas)
    {
        free(st->estado_celulas);
        free(st);
        return -1;
    }
    //criar vetor de estados das celucas tudo a 0
    for (int i = 0; i < 2*g->tamanho; i++)
    {
        st->estado_celulas[i] = 0;
    }
    //criar memoria para os elementos
    st->nos = (no_grafo **)calloc(g->tamanho*2, sizeof(no_grafo *));
    if (!st->nos)
    {
        //se nao conseguir alocar a memoria apaga a tabela
        free(st->nos);
        free(st->estado_celulas);
        free(st);
        return -1;
    }
    //passa os parametros para a tabela
    st->capacidade = g->tamanho*2;

    for (int i = 0; i < g->tamanho; i++)
    {
        if (estrutura_adiciona(st, g->nos[i]) == -1)
        {
            return -1;
        }
        //printf("i=%d\n",i);
    }
   // printf("%d\n",g->tamanho);
 
   //imprime_st(st);
    return 0;
}

char *st_pesquisa(estrutura *st, char *origem, char *destino)
{
    if (!st || !origem || !destino)
    {
        return NULL;
    }
    int indice1, pos_min = -1;
    float preco_min = 9000000;
    indice1 = estrutura_existe(st, origem);
    for (int i = 0; i < st->nos[indice1]->tamanho; i++)
    {
        if (!strcmp(st->nos[indice1]->arestas[i]->destino->cidade, destino))
        {
            if (preco_min > st->nos[indice1]->arestas[i]->preco)
            {
                preco_min = st->nos[indice1]->arestas[i]->preco;
                pos_min = i;
            }
        }
    }

    if (pos_min == -1)
    {
        return NULL;
    }

    return st->nos[indice1]->arestas[pos_min]->codigo;
}

int st_apaga(estrutura *st)
{
    if (!st)
    {
        return -1;
    }
        //vamos a cada posicao do vetor e verificamos se esta NULL
    for (int i = 0; i < st->capacidade; i++)
    {
        //se nao estiver fazemos free
        if (st->estado_celulas[i]==1)
        {
            st->nos[i]=NULL;
        }
    }
        free(st->estado_celulas);
        free(st->nos);
        free(st);
        st = NULL;
    return 0;
}
unsigned long sond_r(int pos, int tentativas, int tamanho)
{

    return (pos + tentativas * tentativas) % tamanho;
}

unsigned long hash_kr(const char *chave, int tamanho)
{
    int c, t = strlen(chave);
    unsigned long soma = 0;

    for (c = 1; c < t; c++)
    {
        soma += (int)chave[c];
    }

    return soma % tamanho;

    return 0;
}
int estrutura_adiciona(estrutura *st, no_grafo *entrada)
{
    //tentar fazer uma funcao para nao repetirmos o codigo
    if (!st || !entrada)
    {
        return -1;
    }
    //temos que ver se o estado do index é -1 ou 1 pq so podemos inserir no 0;
    unsigned long index;
    //while difernte de 0 condição de saida quando encountrou
    index = st->hfunc(entrada->cidade, st->capacidade);
    if (st->estado_celulas[index] == 1 || st->estado_celulas[index] == -1)
    {
        unsigned long index2 = index;
        int count = 1;
        while (st->estado_celulas[index2] != 0)
        { //descobrir qual a proxima posicao disponivel
            index2 = st->sfunc(index, count, st->capacidade);
            //aumenta o numero de tentativas que fizemos
            count++;
        }
        st->nos[index2] = entrada;
        st->estado_celulas[index2] = 1;
        st->tamanho++;
        return index2;
    }
    else //se o estado da posicao que hash deu for 0 podemos guardar la a entrada
    {
        st->nos[index] = entrada;
        st->estado_celulas[index] = 1;
        st->tamanho++;

        return index;
    }

    return -1;
}
int estrutura_existe(estrutura *st, const char *cidade)
{
    if (!st || !cidade)
    {
        return -1;
    }
    unsigned long indice = -1;
    unsigned long index2 = indice;
    int count = 1;
    indice = st->hfunc(cidade, st->capacidade);
    if (st->estado_celulas[indice] == 1)
    {
        if (strcmp(cidade, st->nos[indice]->cidade))
        {
            while (st->estado_celulas[index2] != 0)
            { //descobrir qual a proxima posicao disponivel
                if (!strcmp(cidade, st->nos[index2]->cidade))
                {
                    return index2;
                }

                index2 = st->sfunc(indice, count, st->capacidade);
                //aumenta o numero de tentativas que fizemos
                count++;
            }
            return -1;
        }
        else
        {
            return indice;
        }
    }
    else //se o estado da posicao que hash deu for 0 podemos guardar la a entrada
    {

        return -1;
    }

    return indice;
}

void imprime_st(estrutura *st){

 for(int i=0;i<st->capacidade;i++){
        if(st->estado_celulas[i]==1){
            printf("%s\n",st->nos[i]->cidade);
        }
    }
}