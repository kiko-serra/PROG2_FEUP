/*****************************************************************/
/*    Estrutura nova a implementar | PROG2 | MIEEC | 2020/21     */
/*****************************************************************/

#ifndef _STNOVA_H_
#define _STNOVA_H_

#include "grafo.h"
#include "tabdispersao.h"

/* podem criar mais struct que achem necessá rias */
typedef unsigned long hash_func(const char *, int);

typedef unsigned long sond_func(int, int, int);

typedef struct
{
    hash_func *hfunc;    /* apontador para função de dispersão */
  sond_func *sfunc;    /* apontador para função de sondagem */
  int capacidade;      /* número de posições alocadas de ‘nos’ */
  int tamanho;         /* número de posições preenchidas de ‘nos’ */
  no_grafo **nos;      /* vetor de apontadores para nó */
  int *estado_celulas;
    
} estrutura;

/*
*  cria e inicializa a estrutura criada
*  retorna a estrutura se bem-sucedido ou NULL caso contrário
*/
estrutura *st_nova();

/*
*  importa todo o conteúdo do grafo g para o novo formato de acesso
*  parametro st - apontador para a estrutura criada 
*  parametro g - apontador para o grafo
*  retorna 0 se bem-sucedido ou -1 em contrário
*/
int st_importa_grafo(estrutura *st, grafo *g);

/* obtém o código de voo do par origem-destino com menor preço 
*  a instância retornada deverá ser mantida, i.e., deverá ficar uma cópia dela no respetivo elemento de ‘st’
*  NOTA: esta função será avaliada pelo tempo de execução!
*  parametro st - apontador para a estrutura
*  parametro origem - nome da cidade de origem dos voos a pesquisar
*  parametro destino - nome da cidade de destino dos voos a pesquisar
*  retorna o código do voo ou em caso de insucesso, retorna NULL
*/
char *st_pesquisa(estrutura *st, char *origem, char *destino);

/*
*  elimina todas as instâncias presentes na estrutura st e desaloca toda a memória da mesma
*  NOTA: esta função será avaliada pelo tempo de execução!
*  parametro st - apontador para a estrutura 
*  retorna 0 se bem-sucedido e -1 se ocorrer algum erro
*/
int st_apaga(estrutura *st);

/*
*  função de dispersão
*  calcula hash com base na seguinte fórmula:
*            hash(i) = hash(i-1) + chave[i]
*    em que hash(0) = 7
*
*  parametro chave - string para a qual se pretende calcular o chave de hash
*  parametro tamanho - capacidade da tabela de dispersão
*  nota - chave[i] é o caracter no índice de i da chave
*  retorna o índice correspondente à ‘chave’
*/
unsigned long hash_kr(const char *chave, int tamanho);

/*
*  função de resolução de colisões, implementada por sondagem quadrática
*  parametro pos - índice base onde ocorreu a colisão
*  parametro tentativas - passo/número de tentativas atual
*  parametro tamanho - capacidade da tabela de dispersão
*  retorna um índice alternativo, correspondente à 'tentativa'
*  deve usar esta função sempre que se verificar uma colisão
*/
unsigned long sond_r(int pos, int tentativas, int tamanho);

int estrutura_adiciona(estrutura *st, no_grafo *entrada);

int estrutura_existe(estrutura *st, const char *cidade);

void imprime_st(estrutura *st);

#endif
