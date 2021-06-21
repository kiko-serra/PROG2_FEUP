#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "heap.h"

/*** problema 2.1 ***/
vetor *heap_ordena(vetor *v)
{
	if (!v)
	{
		return NULL;
	}
	heap *h = heap_nova(v->tamanho);
	if (!h)
	{
		return NULL;
	}
	vetor *vec = vetor_novo();
	if (!vec)
	{
		return NULL;
	}

	for (int i = 0; i < v->tamanho; i++)
	{
		//testa se insere bem
		if (!heap_insere(h, v->elementos[i].str, (v->elementos[i].str[0] << 8) + v->elementos[i].str[1]))
		{
			heap_apaga(h);
			h = NULL;
			return NULL;
		}
	}
	int tam = v->tamanho;
	for (int i = 0; i < tam; i++)
	{
		vetor_insere(vec, heap_remove(h), -1);
	}
	heap_apaga(h);
	h=NULL;
	//falta ordenar o vetor
	v_elemento aux;
	int tam2=v->tamanho;
 	for (int i = 0; i < tam2/2; i++)
	{
		aux = vec->elementos[i];
		vec->elementos[i] = vec->elementos[tam2 - 1 - i];
		vec->elementos[tam2 - 1 - i] = aux;
	}

	return vec;
}

/*** problema 2.2 ***/
/*
complexidade do algoritmo:O(n*log(n))

justificacao:
	inserir na heap n vezes: O(n*log(n));
	remover da heap n vezes : O(n*log(n));
	inserir no vetor n vezes: O(n);
	inversao do vetor : O(n);

	TOTAL = O(n*log(n)) + O(n*log(n)) O(n) + O(n)= O(n*log(n))
*/

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE 100

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	/* teste problema 2.1 */
	{
		int i, j;
		char cidade[MAX_LINE];
		vetor *v, *res;
		FILE *fp;

		puts("* Problema 2.1 *");
		v = vetor_novo();
		fp = fopen("cidades.txt", "r");
		while (fgets(cidade, MAX_LINE, fp) != NULL)
		{
			*strchr(cidade, ',') = '\0';
			vetor_insere(v, cidade, v->tamanho);
		}
		res = heap_ordena(v);
		if (res != NULL)
		{
			for (i = 0; i < 3 && i < vetor_tamanho(res); i++)
				printf("%s\n", vetor_elemento(res, i));
			if (vetor_tamanho(res) > 3)
			{
				if (vetor_tamanho(res) > 6)
					puts("...");
				j = i;
				if (vetor_tamanho(res) - 3 > j)
					j = vetor_tamanho(res) - 3;
				for (i = j; i < vetor_tamanho(res); i++)
					printf("%s\n", vetor_elemento(res, i));
			}
		}
		vetor_apaga(v);
		vetor_apaga(res);
	}

	return 0;
}