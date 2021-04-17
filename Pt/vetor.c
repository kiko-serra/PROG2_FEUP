/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2020/21          */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

vetor *vetor_novo()
{
	vetor *vec;

	/* aloca memoria para a estrutura vetor */
	vec = (vetor *)malloc(sizeof(vetor));
	if (vec == NULL)
		return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
}

void vetor_apaga(vetor *vec)
{
	int i;

	if (vec == NULL)
		return;

	/* liberta memoria de cada string */
	for (i = 0; i < vec->tamanho; i++)
	{
		free(vec->elementos[i].str);
	}

	/* liberta memoria dos apontares para as strings */
	free(vec->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec);
}

int vetor_atribui(vetor *vec, int pos, const char *valor)
{
	unsigned int len_valor;

	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
		return -1;

	len_valor = strlen(valor);

	/* reserva mais espaco se necessario */
	if (len_valor > strlen(vec->elementos[pos].str))
	{
		vec->elementos[pos].str = (char *)realloc(vec->elementos[pos].str, (len_valor + 1) * sizeof(char));
		if (vec->elementos[pos].str == NULL)
			return -1;
	}

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);

	return pos;
}

int vetor_tamanho(vetor *vec)
{
	if (vec == NULL)
		return -1;

	return vec->tamanho;
}

const char *vetor_elemento(vetor *vec, int indice)
{
	if (vec == NULL || indice < 0 || indice >= vec->tamanho)
		return NULL;

	return vec->elementos[indice].str;
}

int vetor_insere(vetor *vec, const char *valor, int pos)
{
	int i, n;

	if (vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if (vec->tamanho == vec->capacidade)
	{
		if (vec->capacidade == 0)
			vec->capacidade = 1;
		else
			vec->capacidade *= 2;

		vec->elementos = (v_elemento *)realloc(vec->elementos, vec->capacidade * sizeof(v_elemento));
		if (vec->elementos == NULL)
			return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if (pos == -1)
		pos = vec->tamanho;

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for (i = vec->tamanho - 1; i >= pos; i--)
	{
		vec->elementos[i + 1] = vec->elementos[i];
	}

	/* aloca espaco para a nova string na posicao pos */
	vec->elementos[pos].str = (char *)calloc(strlen(valor) + 1, sizeof(char));
	if (vec->elementos[pos].str == NULL)
		return -1;

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);

	vec->tamanho++;

	return pos;
}

int vetor_remove(vetor *vec, int pos)
{
	int i;

	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
		return -1;

	/* liberta string na posicao a remover */
	free(vec->elementos[pos].str);

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for (i = pos + 1; i < vec->tamanho; i++)
	{
		vec->elementos[i - 1] = vec->elementos[i];
	}

	vec->tamanho--;

	return 0;
}

int vetor_pesquisa(vetor *vec, const char *valor)
{
	int i;

	if (vec == NULL)
		return -1;

	/* pesquisa sequencial */
	for (i = 0; i < vec->tamanho; i++)
	{
		if (strcmp(vec->elementos[i].str, valor) == 0)
			return i;
	}

	return -1;
}

int vetor_ordena(vetor *vec)
{
	int i, j;
	char *tmp;

	if (vec == NULL)
		return -1;

	/* ordenacao por insercao */
	for (i = 1; i < vec->tamanho; i++)
	{
		tmp = vec->elementos[i].str;
		for (j = i; j > 0 && strcmp(tmp, vec->elementos[j - 1].str) < 0; j--)
		{
			vec->elementos[j] = vec->elementos[j - 1];
		}
		vec->elementos[j].str = tmp;
	}

	return 0;
}
//cria um novo vetor que resulta da concatenação de dois outros vetores
vetor *vetor_concatena(vetor *vec1, vetor *vec2)
{
	vetor *v = vetor_novo();
	for (int i = 0; i < vetor_tamanho(vec1); i++)
	{
		vetor_insere(v, vetor_elemento(vec1, i), -1);
	}
	for (int i = 0; i < vetor_tamanho(vec2); i++)
	{
		vetor_insere(v, vetor_elemento(vec2, i), -1);
	}

	return v;
}
//inverte os elementos do vetor
int vetor_inverte(vetor *vec)
{
	if (!vec)
		return -1;

	char a[100] = {};
	int l = vetor_tamanho(vec) - 1, i = 0;
	while (i < vetor_tamanho(vec) / 2)
	{
		strcpy(a, vec->elementos[i].str);
		strcpy(vec->elementos[i].str, vec->elementos[l].str);
		strcpy(vec->elementos[l].str, a);
		l--;
		i++;
	}
	return 0;
}
//cria um novo vetor com os mesmos elementos do vetor vec mas guardados em posições aleatórias

vetor *vetor_baralha(vetor *vec)
{
	if (!vec)
		return NULL;

	vetor *vec_shuf = vetor_novo();

	// copy vec to vec_shuf
	for (int i = 0; i < vetor_tamanho(vec); i++)
	{
		char *v_i = vec->elementos[i].str;

		if (vetor_insere(vec_shuf, v_i, -1) == -1)
		{
			printf("Falha a inserir elemento no vetor\n");
			vetor_apaga(vec_shuf);
			return NULL;
		}
	}

	// shuffle vec_shuf
	for (int i = 0; i < vetor_tamanho(vec_shuf); i++)
	{
		// generate random index
		int ridx = rand() % vetor_tamanho(vec_shuf);

		// keep the reference for the i-th string in a temporary variable
		v_elemento tmp = vec_shuf->elementos[i];

		// element at position ridx goes to position i and vice-versa
		vec_shuf->elementos[i] = vec_shuf->elementos[ridx];
		vec_shuf->elementos[ridx] = tmp;
	}

	return vec_shuf;
}

vetor *vetor_importa(vetor *vec, char *nome_ficheiro)
{
	FILE *f = fopen(nome_ficheiro, "r");
	char str[80] = {};
	while (fgets(str, 80, f) != NULL)
	{
		str[strlen(str) - 1] = '\0';
		vetor_insere(vec, str, -1);
	}

	return vec;
}