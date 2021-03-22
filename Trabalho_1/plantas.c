/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define N_MAX 200
planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
    return NULL;
}

colecao *colecao_nova(const char *tipo_ordem)
{
    colecao *cole = (colecao *)malloc(sizeof(colecao));
    //guarda memoria para o espaco de colecao
    if (cole == NULL)
    {
        printf("Sem memória no sistema\n");
        return NULL;
    }

    cole->tamanho = 0;
    strcpy(cole->tipo_ordem, tipo_ordem);
    cole->plantas = NULL;
    return cole;
}
int insere_alcunhas(planta *p1, planta *p2)
{
    return -1;
}
int planta_insere(colecao *c, planta *p)
{
    return -1;
}
int colecao_tamanho(colecao *c)
{
    if (c == NULL)
        return -1;
    return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
    return NULL;
}
planta *planta_remove(colecao *c, const char *nomep)
{
    planta *removida;
    if (c == NULL)
        return NULL;
    // fazer a funcao que pesquisa para ver onde esta esse nomep;
    ////->->->pergunta? o que fazer se houver mais do que uma planta com esse nome???
    //diferente de coleçao_pesquisa_nome;
    //copiar essa planta para removida;
    //zerar os valores da planta da colecao;
    return removida;
}

int planta_apaga(planta *p)
{
    if (p==NULL)
    {
        return -1;
    }
    free(p->ID);
    free(p->nome_cientifico);
    free(p->alcunhas);
    //free(p->n_alcunhas);
    // esta em comentario porque nao se pode dar free a inteiros 
    // mas como apagar a memoria que n_sementes ocupa?? ->free(p->n_sementes);
    free(p);
    return 0;
}
int colecao_apaga(colecao *c)
{
    int i = 0;
    if (c == NULL)
        return -1;
    //percorre todo o vetor plantas da colecao e liberta a memoria de cada apontador
    for(i=0;i<c->tamanho;i++)
    {
        planta_apaga(c->plantas[i]);
    }
    //free(c->plantas);
    //free(c->tamanho);
    //free(c->tipo_ordem); <- quando pus em comentario deixou de dizer free(): invalid pointer \n Aborted
    free(c);
    c = NULL;
    return 0;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
    return NULL;
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
    int i, j;
    planta *aux;
    if (c == NULL || aux == NULL)
    {
        return -1;
    }
    if (c->tamanho == 0)
    {
        return 0;
    }
    strcpy(c->tipo_ordem, tipo_ordem);
    if (!strcmp(c->tipo_ordem, "nome"))
    {
        for (i = 0; i < c->tamanho; i++)
        {
            for (j = i + 1; j < c->tamanho; j++)
            {
                if (strcmp(c->plantas[i]->nome_cientifico, c->plantas[j]->nome_cientifico) > 0)
                {
                    aux = c->plantas[i];
                    c->plantas[i] = c->plantas[j];
                    c->plantas[j] = aux;
                }
            }
        }
    }
    else if (!strcmp(c->tipo_ordem, "id"))
    {
        for (i = 0; i < c->tamanho; i++)
        {
            for (j = i + 1; j < c->tamanho; j++)
            {
                if (strcmp(c->plantas[i]->ID, c->plantas[j]->ID) > 0)
                {
                    aux = c->plantas[i];
                    c->plantas[i] = c->plantas[j];
                    c->plantas[j] = aux;
                }
            }
        }
    }

    return 1;
}