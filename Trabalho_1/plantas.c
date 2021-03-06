/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define N_MAX 200


int colecao_atualiza(colecao *c, planta *p, int i);
planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
    planta *plt = (planta *)malloc(sizeof(planta));
    
    if (plt == NULL || sizeof(ID) > 10 || ID == NULL || sizeof(nome_cientifico) > N_MAX || nome_cientifico == NULL || n_sementes < 0 || n_alcunhas < 0)
        return NULL;

    strcpy(plt->ID, ID);
    strcpy(plt->nome_cientifico, nome_cientifico);
    plt->n_sementes = n_sementes;
    plt->n_alcunhas = n_alcunhas;
    if (n_alcunhas > 0)
    {
        for (int i = 0; i < n_alcunhas; i++)
        {
            if (i > 0)
            {
                plt->alcunhas = (char **)realloc(plt->alcunhas, sizeof(char *) * (i + 1));
            }
            else
            {
                plt->alcunhas = (char **)malloc(sizeof(char *));
            }
            plt->alcunhas[i] = (char *)malloc(sizeof(char) * (strlen(alcunhas[i])+1));
            strcpy(plt->alcunhas[i], alcunhas[i]);

        }
    }
    else if (n_alcunhas == 0)
    {
        
      plt->alcunhas = NULL;
    }

    return plt;
}

colecao *colecao_nova(const char *tipo_ordem)
{
    if (tipo_ordem == NULL)
        return NULL;

    colecao *c = (colecao *)malloc(sizeof(colecao));
    //guarda memoria para o espaco de colecao
    if (c == NULL)
    {
        printf("Sem memória no sistema\n");
        return NULL;
    }

    c->tamanho = 0;
    strcpy(c->tipo_ordem, tipo_ordem);
    c->plantas = NULL;
    return c;
}
int planta_insere(colecao *c, planta *p)
{
    if (c == NULL || p == NULL || p->n_alcunhas < 0 || p->n_sementes < 0 || p == NULL || sizeof(p->ID) > 10 || sizeof(p->nome_cientifico) > N_MAX)
    {
        return -1;
    }

    for (int i = 0; i < c->tamanho; i++)
    {
        if (!strcmp(c->plantas[i]->ID, p->ID))
        {
            //se passarem valores de alcunhas ou sementes negativos colecao_atualiza da erro
            if (colecao_atualiza(c, p, i) == -1)
            {
                return -1;
            }
            else
            {
                colecao_reordena(c, c->tipo_ordem);
                return 1;
            }
        }
    }
    c->plantas = (planta **)realloc(c->plantas, sizeof(planta *) * (c->tamanho + 1));
    c->tamanho++;
    c->plantas[c->tamanho - 1] = p;

    colecao_reordena(c, c->tipo_ordem);
    return 0;
}
int colecao_tamanho(colecao *c)
{
    if (c == NULL)
        return -1;
    return c->tamanho;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
    if (nome_ficheiro == NULL || tipo_ordem == NULL)
    {
        return NULL;
    }
    
    planta *p;
    FILE *f = fopen(nome_ficheiro, "r");
    colecao *c = colecao_nova(tipo_ordem);
    //criar colecao nova
    char linha[500] = {}, id[10], nome_cientifico[N_MAX];
    char **alcunhas;
    int n_alcunhas = 0, n_sementes = 0;
    char *token;

    while (fgets(linha, 500, f) != NULL)
    {
        n_alcunhas = 0;
        linha[strlen(linha) - 1] = '\0';
        token = strtok(linha, ",");
        strcpy(id, token);

        if (strlen(id) > 10 || strlen(id) < 0)
        {
            colecao_apaga(c);
            return NULL;
        }

        token = strtok(NULL, ",");

        strcpy(nome_cientifico, token);
        if (strlen(nome_cientifico) > N_MAX || strlen(nome_cientifico) < 0)
        {
            colecao_apaga(c);
            return NULL;
        }

        token = strtok(NULL, ",");
        n_sementes = atoi(token);
        if (n_sementes < 0)
        {
            colecao_apaga(c);
            return NULL;
        }
        token = strtok(NULL, ",");
        n_alcunhas = 0;
        alcunhas = NULL;
        while (token != NULL)
        {
          alcunhas= (char **)realloc(alcunhas, (n_alcunhas+1)*sizeof(char *));
          alcunhas[n_alcunhas]= (char *) malloc((strlen(token)+1)*sizeof(char));
          strcpy(alcunhas[n_alcunhas], token);

          token = strtok(NULL, ",");

          n_alcunhas++; 
        }
        
        p = planta_nova(id, nome_cientifico, alcunhas, n_alcunhas, n_sementes);
        int flag;
        flag=planta_insere(c, p);
        if(flag==1 || flag==-1){
            planta_apaga(p);
        }
                

        for (int i = 0; i < n_alcunhas; i++)
        {
            free(alcunhas[i]);
        }
        free(alcunhas);
        alcunhas = NULL;

    }    

    fclose(f);
    return c;
}
planta *planta_remove(colecao *c, const char *nomep)
{
    int i;
    planta *removida;
    if (c == NULL || nomep == NULL)
        return NULL;
    // procurar , apontar com a removida para a que tem o nomep
    // puxar todos os elelmentos da frente uma posicao para tras
    //retornar removida
    for (i = 0; i < c->tamanho; i++)
    {
        if (!strcmp(c->plantas[i]->nome_cientifico, nomep))
        {
            if (c->plantas[i]->n_alcunhas < 0 || c->plantas[i]->n_sementes < 0)
            {
                return NULL;
            }

            removida = planta_nova(c->plantas[i]->ID, c->plantas[i]->nome_cientifico, c->plantas[i]->alcunhas, c->plantas[i]->n_alcunhas, c->plantas[i]->n_sementes);

            break;
        }
        else
            return NULL;
    }
    for (int j = i + 1; j < c->tamanho; j++)
    {
        c->plantas[j - 1] = c->plantas[j];
    }
    c->tamanho--;
    c->plantas = (planta **)realloc(c->plantas, sizeof(planta *) * (c->tamanho));

    return removida;
}

int planta_apaga(planta *p)
{
    if (p == NULL)
    {
        return -1;
    }

    for (int i = 0; i < p->n_alcunhas; i++)
    {
        free(p->alcunhas[i]);
    }

    free(p->alcunhas);
    free(p);
    p = NULL;
    return 0;
}
int colecao_apaga(colecao *c)
{
    int i = 0;
    if (c == NULL)
        return -1;
    //percorre todo o vetor plantas da colecao e liberta a memoria de cada apontador
    for (i = 0; i < c->tamanho; i++)
    {
        planta_apaga(c->plantas[i]);
    }
    free(c->plantas);

    free(c);
    c = NULL;
    return 0;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
    if (c == NULL || nomep == NULL)
    {
        return NULL;
    }

    int t = 0;
    int *ind = NULL;
    for (int i = 0; i < colecao_tamanho(c); i++)
    {
        if (!strcmp(c->plantas[i]->nome_cientifico, nomep))
        {
            ind = (int *)realloc(ind, sizeof(int) * (t + 1));
            ind[t] = i;
            t++;
            continue;
        }

        if (c->plantas[i]->n_alcunhas > 0)
        {
            for (int k = 0; k < c->plantas[i]->n_alcunhas; k++)
            {
                if (!strcmp(c->plantas[i]->alcunhas[k], nomep))
                {
                    ind = (int *)realloc(ind, sizeof(int) * (t + 1));
                    ind[t] = i;
                    t++;
                    continue;
                }
            }
        }
    }
    *tam = t;
    if (t > 0)
    {
        return ind;
    }
    else
    {
        return NULL;
    }
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{   //se flag ==1 significa que houve uma mudanca de lugares logo a colecao nao estava ordenada e retorna 1
    //se flag==0 nunca houve mudanca de lugares logo colecao ordenada e retorna 0 como pedido
    int flag=0;
    int i, j;
    planta *aux;
    if (c == NULL || strlen(tipo_ordem)>5 ||tipo_ordem==NULL)
    {
        return -1;
    }
    if (c->tamanho == 0)
    {
        return 0;
    }

    
    memcpy(c->tipo_ordem, tipo_ordem, (strlen(tipo_ordem)+1));
   
    if (!strcmp(c->tipo_ordem, "nome"))
    {flag=0;
        for (i = 0; i < (c->tamanho); i++)
        {
            for (j = i + 1; j < (c->tamanho); j++)
            {
                if (strcmp(c->plantas[i]->nome_cientifico, c->plantas[j]->nome_cientifico) > 0)
                {
                    flag=1;
                    aux = c->plantas[i];
                    c->plantas[i] = c->plantas[j];
                    c->plantas[j] = aux;
                }
            }
        }
    }
    else if (!strcmp(c->tipo_ordem, "id"))
    {flag=0;
        for (i = 0; i < (c->tamanho); i++)
        {
            for (j = i + 1; j < (c->tamanho); j++)
            {
                if (strcmp(c->plantas[i]->ID, c->plantas[j]->ID) > 0)
                {
                    flag=1;
                    aux = c->plantas[i];
                    c->plantas[i] = c->plantas[j];
                    c->plantas[j] = aux;
                }
            }
        }
    }
    if (flag==0)
    {
        return 0;
    }
    else{return 1;}
    
}

//atualiza o número de sementes, alcunhas e alcunhas repetidas
int colecao_atualiza(colecao *c, planta *p, int i)
{

    int t = 0;
    if (p->n_sementes < 0 || p->n_alcunhas < 0 || c == NULL || p == NULL || i < 0)
    {
        return -1;
    }

    c->plantas[i]->n_sementes += p->n_sementes;
    for (int j = 0; j < p->n_alcunhas; j++)
    {
        t = 0;
        for (int k = 0; k < c->plantas[i]->n_alcunhas; k++)
        {
            if (!strcmp(c->plantas[i]->alcunhas[k], p->alcunhas[j]))
                t++;
        }
        if (t == 0)
        {
            c->plantas[i]->n_alcunhas++;

            c->plantas[i]->alcunhas = (char **)realloc(c->plantas[i]->alcunhas, sizeof(char *) * (c->plantas[i]->n_alcunhas));
            c->plantas[i]->alcunhas[(c->plantas[i]->n_alcunhas) - 1] = (char *)malloc(sizeof(char) * (strlen(p->alcunhas[j]) + 1));
            strcpy(c->plantas[i]->alcunhas[(c->plantas[i]->n_alcunhas) - 1], p->alcunhas[j]);
        }
    }
    return 0;
}