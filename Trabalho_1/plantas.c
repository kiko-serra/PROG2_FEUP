/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	return NULL;
}

colecao *colecao_nova(const char *tipo_ordem)
{
	return NULL;
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
	return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}
planta *planta_remove(colecao *c, const char *nomep)
{
	return NULL;
}

int planta_apaga(planta *p)
{
	return -1;
}
int colecao_apaga(colecao *c)
{
	return -1;
}
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	return NULL;
}
int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}