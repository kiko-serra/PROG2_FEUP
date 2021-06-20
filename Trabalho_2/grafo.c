/*****************************************************************/
/*          Grafo direcionado | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"
#include <limits.h>
#include <stdbool.h>
#define INFINITO 9000000

void dijkstra_mais_rapido(grafo* g, char *source, data partida);
void dijkstra_menos_transbordos(grafo* g, char *source);
void grafo_imprime(grafo *g);

grafo *grafo_novo()
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->tamanho = 0;
    g->nos = NULL;

    return g;
}

no_grafo *encontra_no(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // pesquisa por cidade no vetor de nós
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, cidade) == 0)
            return g->nos[i];
    }
    return NULL;
}

no_grafo *no_insere(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    // verifica se o nó já existe
    no_grafo *no = encontra_no(g, cidade);
    if (no)
        return NULL;

    // cria o novo nó para o user
    no = (no_grafo *)malloc(sizeof(no_grafo));
    if (!no)
        return NULL;

    // aloca espaço para o campo cidade
    no->cidade = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    if (!no->cidade)
    {
        free(no);
        return NULL;
    }
    // inicializa todos os campos
    strcpy(no->cidade, cidade);
    no->tamanho = 0;
    no->arestas = NULL;
    no->p_acumulado = 0;
    no->anterior = NULL;
    no->dataatualizada = NULL;

    // insere o nó criado no final do vetor de nós
    g->nos = (no_grafo **)realloc(g->nos, (g->tamanho + 1) * sizeof(no_grafo *));
    if (!g->nos)
    {
        free(no->cidade);
        free(no);
        return NULL;
    }
    // incrementa o tamanho do numero de nós e insere no vetor de apontadores de nós
    g->tamanho++;
    g->nos[g->tamanho - 1] = no;

    return no;
}

// função auxiliar que retorna 1 se existir a aresta para destino ou 0,
// se a aresta não existir, -1 se der erro
int existe_aresta(no_grafo *origem, no_grafo *destino, char *codigo)
{

    if (!origem || !destino)
        return -1;

    //pesquisa em todas as arestas se existe
    for (int i = 0; i < origem->tamanho; i++)
    {

        if ((origem->arestas[i]->destino == destino) && ((strcmp(origem->arestas[i]->codigo, codigo) == 0)))
            return 1;
    }

    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *companhia, data partida, data chegada, float preco, int lugares)
{
    if (!origem || !destino || !codigo || !companhia)
        return -1;

    if (preco < 0 || lugares < 0)
        return -1;

    // verifica se a ligação já existe
    if (existe_aresta(origem, destino, codigo) > 0)
        return -1;

    // cria a nova ligação
    aresta_grafo *ag = (aresta_grafo *)malloc(sizeof(aresta_grafo));
    if (!ag)
        return -1;

    ag->destino = destino;
    ag->preco = preco;
    ag->lugares = lugares;
    // aloca espaço para o código
    ag->codigo = (char *)malloc((strlen(codigo) + 1) * sizeof(char));
    if (!ag->codigo)
    {
        free(ag);
        return -1;
    }
    strcpy(ag->codigo, codigo);
    // aloca espaço para o companhia
    ag->companhia = (char *)malloc((strlen(companhia) + 1) * sizeof(char));
    if (!ag->companhia)
    {
        free(ag->codigo);
        free(ag);
        return -1;
    }
    strcpy(ag->companhia, companhia);

    // inicializa todos os campos
    ag->partida.tm_year = partida.tm_year;
    ag->partida.tm_mon = partida.tm_mon;
    ag->partida.tm_mday = partida.tm_mday;
    ag->partida.tm_hour = partida.tm_hour;
    ag->partida.tm_min = partida.tm_min;
    ag->partida.tm_sec = 0;
    ag->partida.tm_isdst = 0;

    // inicializa todos os campos
    ag->chegada.tm_year = chegada.tm_year;
    ag->chegada.tm_mon = chegada.tm_mon;
    ag->chegada.tm_mday = chegada.tm_mday;
    ag->chegada.tm_hour = chegada.tm_hour;
    ag->chegada.tm_min = chegada.tm_min;
    ag->chegada.tm_sec = 0;
    ag->chegada.tm_isdst = 0;

    // insere a nova ligação no vetor de ligações
    origem->arestas = (aresta_grafo **)realloc(origem->arestas, (origem->tamanho + 1) * sizeof(aresta_grafo *));
    if (!origem->arestas)
    {
        free(ag->codigo);
        free(ag->companhia);
        free(ag);
        return -1;
    }
    origem->tamanho++;
    origem->arestas[origem->tamanho - 1] = ag;

    return 0;
}

no_grafo *no_remove(grafo *g, char *cidade)
{
    if (!g || !cidade)
        return NULL;

    //descobrir a posicao
    int i;
    //flag verifica se o parametro cidade é mesmo uma cidade ou um nome aleatorio
    // se for cidade funciona normalmente se nao for retorna null para acabar ali a execucao
    int flag = 0;
    for (i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, cidade) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        return NULL;
    }

    int pos = g->nos[i]->tamanho;
    //apaga arestas que "saiem" do nó
    for (int j = 0; j < pos; j++)
    {
        if (aresta_apaga(g->nos[i]->arestas[j]) == -1)
        {
            return NULL;
        }
    }
    g->nos[i]->tamanho = 0;
    no_grafo *aux = g->nos[i];
    if (!aux)
    {
        free(aux);
        return NULL;
    }

    //mudar os apontadores do vetor
    for (int j = i; j < g->tamanho - 1; j++)
    {
        g->nos[j] = g->nos[j + 1];
    }
    //as 2 linhas ao trocar a ordem passa de  572 definitivos e 10 mil indiretos blocos perdidos e 0 reachable para
    //8 definitivos 5 indiretos e 109 reachable
    g->tamanho--;
    g->nos = (no_grafo **)realloc(g->nos, sizeof(no_grafo *) * (g->tamanho - 1));
    //apagar arestas com destino a nossa cidade
    int k;
    for (int j = 0; j < g->tamanho; j++)
    {
        for (k = 0; k < g->nos[j]->tamanho; k++)
        {
            if (!strcmp(g->nos[j]->arestas[k]->destino->cidade, cidade))
            {
                if (aresta_apaga(g->nos[j]->arestas[k]) == -1)
                    return NULL;
                else
                {
                    for (int q = k; q < (g->nos[j]->tamanho) - 1; q++)
                    {
                        g->nos[j]->arestas[q] = g->nos[j]->arestas[q + 1];
                    }
                    g->nos[j]->tamanho--;
                    k--;
                    //realloc de memória para novo tamanho de arestas
                    g->nos[j]->arestas = (aresta_grafo **)realloc(g->nos[j]->arestas, (g->nos[j]->tamanho) * sizeof(aresta_grafo *));
                }
            }
        }
    }
    return aux;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if (!aresta)
    {
        return -1;
    }
    free(aresta->codigo);
    free(aresta->companhia);
    free(aresta);
    aresta = NULL;

    return 0;
}

int no_apaga(no_grafo *no)
{
    if (!no)
    {
        return -1;
    }
    for (int i = 0; i < no->tamanho; i++)
    {
        if (aresta_apaga(no->arestas[i]) == -1)
        {
            return -1;
        }
        else
        {
            for (int q = i; q < no->tamanho - 1; q++)
            {
                no->arestas[q] = no->arestas[q + 1];
                no->tamanho--;
            }
        }
    }
    free(no);
    no = NULL;
    return 0;
}

void grafo_apaga(grafo *g)
{
    if (!g)
        return;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (no_apaga(g->nos[i]) == -1)
        {
            return;
        }
    }

    //apagar as arestas
    free(g);
    g = NULL;
}

no_grafo *encontra_voo(grafo *g, char *codigo, int *aresta_pos)
// PERGUNTA: nao ha codigos repetidos? vou ter 2 nos com a mesma aresta pois é a mesma viagem
// logo vou descobrir 2 vezes a aresta
{
    if (!g || !codigo || !aresta_pos)
    {
        return NULL;
    }
    //testar se o codigo é valido
    if (strlen(codigo) != 12 || codigo[0] != 'N')
    {
        return NULL;
    }

    int i, j;
    int flag = 0;
    for (i = 0; i < g->tamanho; i++)
    {

        for (j = 0; j < g->nos[i]->tamanho; j++)
        {
            if (!strcmp(g->nos[i]->arestas[j]->codigo, codigo))
            {
                //j é a posicao da aresta no nó
                *aresta_pos = j;
                flag = 1;
                break;
            }
        }
        //se descobrir a aresta com o codigo acaba e retorna o nó
        if (flag)
        {
            break;
        }
    }
    //se nao existir nenhuma aresta com o codigo acaba
    if (!flag)
    {
        return NULL;
    }

    return g->nos[i];
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, data chegada, double preco_max, int *n)
{

    if (!g || !destino /*|| !chegada*/ || preco_max < 0)
    {
        return NULL;
    }
    // vetor para retornar os nós finais

    no_grafo **aux = (no_grafo **)malloc(sizeof(no_grafo *));
    if (!aux)
    {
        return NULL;
    }
    int count = 0;

    data *fim_dia = (data *)malloc(sizeof(data)); //aloca memoria para a variavel
    //guarda as 23h59min59seg do dia que nos dão
    fim_dia->tm_hour = 23;
    fim_dia->tm_min = 59;
    fim_dia->tm_sec = 59;
    fim_dia->tm_mon = chegada.tm_mon;
    fim_dia->tm_year = chegada.tm_year;
    fim_dia->tm_mday = chegada.tm_mday;
    fim_dia->tm_isdst = 0;
    time_t fim_dia_int = mktime(fim_dia);

    data *inicio_dia = (data *)malloc(sizeof(data)); //guarda as 00h00min00seg do dia que nos dão
    inicio_dia->tm_hour = 0;
    inicio_dia->tm_min = 0;
    inicio_dia->tm_sec = 0;
    inicio_dia->tm_mon = chegada.tm_mon;
    inicio_dia->tm_year = chegada.tm_year;
    inicio_dia->tm_mday = chegada.tm_mday;
    inicio_dia->tm_isdst = 0;
    time_t inicio_dia_int = mktime(inicio_dia);

    data *nossa_data = (data *)malloc(sizeof(data)); //guarda as horas minutos segundos dia mes ano da aresta que descobrimos
    for (int i = 0; i < g->tamanho; i++)
    {
        for (int j = 0; j < g->nos[i]->tamanho; j++)
        {
            //verificar se o destino da aresta é o destino pretendido e se o preco está no intervalo
            if (!strcmp(g->nos[i]->arestas[j]->destino->cidade, destino) && g->nos[i]->arestas[j]->preco <= preco_max)
            {
                *nossa_data = g->nos[i]->arestas[j]->chegada;
                time_t nossa_data_int = mktime(nossa_data);
                if (difftime(fim_dia_int, nossa_data_int) > 0 && difftime(inicio_dia_int, nossa_data_int) < 0)
                {
                    if (count > 0)
                    {
                        aux = (no_grafo **)realloc(aux, sizeof(no_grafo *) * (count + 1));
                    }
                    aux[count] = g->nos[i];
                    count++;
                }
            }
        }
    }
    // se nao houver voos para o destino dado
    if (!count)
    {
        return NULL;
    }
    //libertar memoria usada pelas datas
    free(fim_dia);
    free(inicio_dia);
    free(nossa_data);

    *n = count;
    return aux;
    // ver que o dia ano e mes tem que bater certo
    // ou usar o mktime e o difftime
    // ver se a data esta entre as 00h00min00seg e as 23h59min59seg de um dia
}

no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, data partida, int *n)
{
    //algoritmo dijkstra:
    //1- definir o peso do nó inicial a zero e os restantes a infinito
    //2- relaxar cada aresta, atualizar o peso acumulado (tempo do voo);
    //3-nós na heap! e retirar o menor
    //duvida: como fazer para descobrir caminho até ao destino
    //ter atencao as horas de saida e chegada dos voos -- um voo que chega as 8 ao porto nao pode
    //sair as 7 do porto para fora
    if (!g || !origem || !destino || n < 0)
    {
        return NULL;
    }
    int flag = 0;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, origem) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        return NULL;
    }
    flag = 0;
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->cidade, destino) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        return NULL;
    }

    no_grafo **aux = (no_grafo **)malloc(sizeof(no_grafo *));
    if (!aux)
    {
        return NULL;
    }
    data *fim_dia = (data *)malloc(sizeof(data)); //aloca memoria para a variavel
    //guarda as 23h59min59seg do dia que nos dão
    fim_dia->tm_hour = 23;
    fim_dia->tm_min = 59;
    fim_dia->tm_sec = 59;
    fim_dia->tm_mon = partida.tm_mon;
    fim_dia->tm_year = partida.tm_year;
    fim_dia->tm_mday = partida.tm_mday;
    fim_dia->tm_isdst = 0;
    time_t fim_dia_int = mktime(fim_dia);

    data *inicio_dia = (data *)malloc(sizeof(data)); //guarda as 00h00min00seg do dia que nos dão
    inicio_dia->tm_hour = 0;
    inicio_dia->tm_min = 0;
    inicio_dia->tm_sec = 0;
    inicio_dia->tm_mon = partida.tm_mon;
    inicio_dia->tm_year = partida.tm_year;
    inicio_dia->tm_mday = partida.tm_mday;
    inicio_dia->tm_isdst = 0;
    time_t inicio_dia_int = mktime(inicio_dia);

    data *nossa_data = (data *)malloc(sizeof(data)); //guarda as horas minutos segundos dia mes ano do nó

    //verificar se o nó é compativel com as parametros
    *nossa_data = partida;
    time_t nossa_data_int = mktime(nossa_data);

    if (difftime(fim_dia_int, nossa_data_int) > 0)
    {
        if (difftime(nossa_data_int,inicio_dia_int ) == 0)
        {
            dijkstra_mais_rapido(g, origem, partida);
        }
    }

    int j;
    no_grafo *help;
    for (j = 0; j < g->tamanho; j++)
    {
        if (!strcmp(g->nos[j]->cidade, destino))
        {
            help = g->nos[j];
            break;
        }
    }
    if(g->nos[j]->anterior==NULL) return NULL;
    int q = 1;

    aux[0] = help;
    while (help != NULL)
    {
        aux = (no_grafo **)realloc(aux, (q+1) * sizeof(no_grafo *));
        q++;
        aux[q-1] = help->anterior;
        if (!strcmp(aux[q-1]->cidade, origem))
        {
            break;
        }
        else
            help = help->anterior;
    }
    
    *n = q;
    int d = q;
    no_grafo **aux2 = (no_grafo **)calloc(q, sizeof(no_grafo *));
    for (int i = 0; i < q; i++)
    {
        d--;
        aux2[i] = aux[d];
    }

    free(fim_dia);
    free(inicio_dia);
    free(nossa_data);

    for(int i=0;i<q;i++){
        aux[i]=NULL;
         free(aux[i]);
    }
    free(aux);

    return aux2;
}

no_grafo **menos_transbordos(grafo *g, char *origem, char *destino, data partida, int *n)
{
    //testar parametros
    if (g == NULL || origem == NULL || destino == NULL)
        return NULL;

        dijkstra_menos_transbordos(g,origem);

no_grafo **aux = (no_grafo **)malloc(sizeof(no_grafo *));
    if (!aux)
    {
        return NULL;
    }
         int j;
    no_grafo *help;
    for (j = 0; j < g->tamanho; j++)
    {
        if (!strcmp(g->nos[j]->cidade, destino))
        {
            help = g->nos[j];
            break;
        }
    }
    if(g->nos[j]->anterior==NULL) return NULL;
    int q = 1;

    aux[0] = help;
    while (help != NULL)
    {
        aux = (no_grafo **)realloc(aux, (q+1) * sizeof(no_grafo *));
        q++;
        aux[q-1] = help->anterior;
        if (!strcmp(aux[q-1]->cidade, origem))
        {
            break;
        }
        else
            help = help->anterior;
    }
    
    *n = q;
    int d = q;
    no_grafo **aux2 = (no_grafo **)calloc(q, sizeof(no_grafo *));
    for (int i = 0; i < q; i++)
    {
        d--;
        aux2[i] = aux[d];
    }

    for(int i=0;i<q;i++){
        aux[i]=NULL;
         free(aux[i]);
    }
    free(aux);

    return aux2;
}

aresta_grafo **atualiza_lugares(char *ficheiro, grafo *g, int *n)
{
    *n=0;
    //testar parametros
    if (ficheiro == NULL || g == NULL)
        return NULL;

    FILE *f = fopen(ficheiro, "r");

    char *token, linha[500] = {}, codigo[12];
    int npass, tzero = 0;
   
    aresta_grafo **aux=NULL;

    while (fgets(linha, 500, f) != NULL)
    {
        linha[strlen(linha) - 1] = '\0';
        token = strtok(linha, ",");
        //testar se código de voo é válido
        if (strlen(token) != 12)
            continue;
        strcpy(codigo, token);
        if (codigo[0] != 'N')
            continue;

        token = strtok(NULL, ",");
        npass = atoi(token);
        //testar se numero de passageios é válido

        if (npass < 0)
            continue;
        for (int i = 0; i < g->tamanho; i++)
        {
            for (int j = 0; j < g->nos[i]->tamanho; j++)
            {
                //printf("-%s-%s-\n", g->nos[i]->arestas[j]->codigo, codigo);
                if (!strcmp(g->nos[i]->arestas[j]->codigo, codigo))
                {
                    if (npass == 0)
                    {
                        aux = (aresta_grafo **)realloc(aux, sizeof(aresta_grafo *) * (tzero + 1));
                        aux[tzero] = g->nos[i]->arestas[j];

                        int q;
                        for (q = j; q < (g->nos[i]->tamanho) - 1; q++)
                        {
                            g->nos[i]->arestas[q] = g->nos[i]->arestas[q + 1];
                        }
                        g->nos[i]->tamanho--;
                        j--;
                        //realloc de memória para novo tamanho de arestas
                        g->nos[i]->arestas = (aresta_grafo **)realloc(g->nos[i]->arestas, (g->nos[i]->tamanho) * sizeof(aresta_grafo *));

                        tzero++;
                    }
                    else
                    {
                        g->nos[i]->arestas[j]->lugares = npass;
                    }
                }
            }
        }
    }

    fclose(f);
    *n = tzero;
    for(int i=0;i<tzero;i++){
        printf("%s\n teste", aux[i]->codigo);
    }
    return aux;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, companhia[4] = {0};
    int lugares = 0;
    double preco = 0;
    struct tm partida, chegada;

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ",");
        if (!token)
            break;
        strcpy(codigo, token);

        token = strtok(NULL, ",");
        strcpy(origem, token);

        token = strtok(NULL, ",");
        strcpy(destino, token);

        token = strtok(NULL, ",");
        partida.tm_year = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        partida.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        partida.tm_min = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_year = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_mon = atoi(token) - 1;

        token = strtok(NULL, ",");
        chegada.tm_mday = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_hour = atoi(token);

        token = strtok(NULL, ",");
        chegada.tm_min = atoi(token);

        token = strtok(NULL, ",");
        preco = atof(token);

        token = strtok(NULL, ",");
        lugares = atoi(token);

        token = strtok(NULL, ",");
        strcpy(companhia, token);

        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {

            no_origem = no_insere(g, origem);

            if (!no_origem)
            {
                fclose(f);
                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
            no_destino = no_insere(g, destino);

            if (!no_destino)
            {
                fclose(f);
                return NULL;
            }
        }

        if (existe_aresta(no_origem, no_destino, codigo) == 0)
        {

            ret = cria_aresta(no_origem, no_destino, codigo, companhia, partida, chegada, preco, lugares);

            if (ret == -1)
            {
                fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}
void dijkstra_mais_rapido(grafo *g, char *source, data partida)
//para menos tranbordos
{
    no_grafo *n, *u, *t;
    heap *H, *h_aux;

    H = heap_nova(g->tamanho);
    if(H==NULL){
        heap_apaga(H);
        return;
    }
    n = encontra_no(g, source);
    for (int i = 0; i < g->tamanho; i++)
    {
        g->nos[i]->p_acumulado = INFINITO; //(infinito)
        g->nos[i]->anterior = NULL;
    }
    n->p_acumulado = 0;
    //passa todas as informacoes do grafo para a heap
    for (int i = 0; i < g->tamanho; i++)
    {
        heap_insere(H, g->nos[i], g->nos[i]->p_acumulado);
    }
    u = heap_remove(H);
    while (u != NULL)
    {
        for (int i = 0; i < u->tamanho; i++)
        {
            data *chegada_no = (data *)malloc(sizeof(data));
            data *nossa_data_inicio = (data *)malloc(sizeof(data));
            *chegada_no = u->arestas[i]->chegada;
            *nossa_data_inicio = partida;
            double aux = difftime(mktime(chegada_no), mktime(nossa_data_inicio));

            //falta ver como fazer par voos n sairem antes de chegarem ao nó
            //atualiza o peso do nó
            //diff do mktime da partida do no com partida da funcao >=p_acumulado anterior
            data *partida_no = (data *)malloc(sizeof(data));
            *partida_no = u->arestas[i]->partida;
            if (difftime(mktime(partida_no), mktime(nossa_data_inicio)) >= u->p_acumulado)
            {
                // aux= diff mktime chegada da aresta onde estou com partida da funcao
                if (aux < u->arestas[i]->destino->p_acumulado)
                {
                    u->arestas[i]->destino->p_acumulado = aux;

                    u->arestas[i]->destino->anterior = u;
                    int tam = H->tamanho;
                    //atualiza a heap
                    h_aux = heap_nova(tam);
                    for (int j = 0; j < tam; j++)
                    {
                        t = heap_remove(H);
                        heap_insere(h_aux, t, t->p_acumulado);
                    }
                    for (int j = 0; j < tam; j++)
                    {
                        t = heap_remove(h_aux);
                        heap_insere(H, t, t->p_acumulado);
                    }

                    //remover e inserir numa heap aux e remover da aux e inserir na H
                    //como atualizamos o peso ao inserirmos na nova heap ja vai atualizar tudo direito
                    //e depois so passar para heap principal e vai ficar atualizada
                    //criar variavel que guarde heap->tamanho
                }
            }
            free(chegada_no);
            free(nossa_data_inicio);
            free(partida_no);
        }
        u = heap_remove(H);
    
    }
    heap_apaga(H);
    heap_apaga(h_aux);
    
}
void dijkstra_menos_transbordos(grafo *g, char *source)
{
    no_grafo *n, *u, *t;
    heap *H, *h_aux;

    H = heap_nova(g->tamanho);
    n = encontra_no(g, source);
    for (int i = 0; i < g->tamanho; i++)
    {
        g->nos[i]->p_acumulado = INFINITO; //(infinito)
        g->nos[i]->anterior = NULL;
    }
    n->p_acumulado = 0;
    //passa todas as informacoes do grafo para a heap
    for (int i = 0; i < g->tamanho; i++)
    {
        heap_insere(H, g->nos[i], g->nos[i]->p_acumulado);
    }
    u = heap_remove(H);
    while (u != NULL)
    { 
        for (int i = 0; i < u->tamanho; i++)
        {
            if (u->p_acumulado + 1 < u->arestas[i]->destino->p_acumulado)
            {
                u->arestas[i]->destino->p_acumulado = u->p_acumulado + 1;

                u->arestas[i]->destino->anterior = u;
                int tam = H->tamanho;
                //atualiza a heap
                h_aux = heap_nova(tam);
                for (int j = 0; j < tam; j++)
                {
                    t = heap_remove(H);
                    heap_insere(h_aux, t, t->p_acumulado);
                }
                for (int j = 0; j < tam; j++)
                {
                    t = heap_remove(h_aux);
                    heap_insere(H, t, t->p_acumulado);
                    //remover e inserir numa heap aux e remover da aux e inserir na H
                    //como atualizamos o peso ao inserirmos na nova heap ja vai atualizar tudo direito
                    //e depois so passar para heap principal e vai ficar atualizada
                    //criar variavel que guarde heap->tamanho
                }
            }
        }
            u = heap_remove(H);
    }
     heap_apaga(H);
    heap_apaga(h_aux);
}
void grafo_imprime(grafo *g)
{

    for (int i = 0; i < g->tamanho; i++)
    {
        printf("%s--\n", g->nos[i]->cidade);
        for (int j = 0; j < g->nos[i]->tamanho; j++)
        {
            printf("        %s\n", g->nos[i]->arestas[j]->destino->cidade);
        }
    }
}