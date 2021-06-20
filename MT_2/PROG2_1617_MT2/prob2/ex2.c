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
	//criar o vetor onde vamos retornar a solução
	vetor *vec = vetor_novo();
	if (!vec)
	{
		return NULL;
	}
	//heap auxiliar para ajudar a ordenar as strings
	heap *h = heap_nova(v->tamanho);
	if (!h)
	{
		return NULL;
	}
	vetor *vec_aux = vetor_novo();
	if (!vec_aux)
	{
		return NULL;
	}

	int prio;
	//inserir todas as strings na heap cada uma com a sua prioridade
	for (int i = 0; i < v->tamanho; i++)
	{
		prio = (v->elementos[i].str[0] << 8) + v->elementos[i].str[1];
		if (heap_insere(h, v->elementos[i].str, prio) == 0)
		{
			heap_apaga(h);
			return NULL;
		}
	}
	int tam = h->tamanho;
	for (int i = 0; i < tam; i++)
	{
		if (vetor_insere(vec, heap_remove(h), -1) == -1)
		{
			vetor_apaga(vec);
			heap_apaga(h);
			return NULL;
		}
	}
	heap_apaga(h);

	//alterar a ordem do vetor
	for (int i = 0; i < tam; i++)
	{
		vetor_insere(vec_aux, vec->elementos[tam - 1 - i].str, i);
	}
	//ou podemos inverter assim:
	/*    for (int i = 0; i < v_ord->tamanho / 2; i++)
    {
        v_elemento aux = vec->elementos[i];
        vec->elementos[i] = vec->elementos[vec->tamanho - i - 1];
        vec->elementos[vec->tamanho - i - 1] = aux;

		return vec;
    }
	*/

	return vec_aux;
}

/*** problema 2.2 ***/
/*
complexidade do algoritmo:
	O(n*log(n)) onde n tamanho do vetor
justificacao:
	n insercoes na heap: n*O(log(n))= O(n*log(n));
	n remocoes da heap: n*O(log(n))= O(n*log(n));
	n insercoes no vetor fim do vetor: n*O(1)= O(n);
	inversao do vetor : O(n);

	TOTAL: O(n*log(n)) + O(n*log(n)) + O(n) + O(n)= O(n*log(n));
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
