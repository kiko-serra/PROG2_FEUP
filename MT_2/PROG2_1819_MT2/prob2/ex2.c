#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "avl.h"

//2.1
//Sugere ao utilizador u um conjunto de amizades, que sao:
//amigos dos amigos do utilizador u que ainda nao sao amigos deste.
//Retorna as sugestoes numa arvore avl.
//Em caso de erro retorna NULL (grafo nao existe ou utilizador u nao existe)
arvore_avl *sugestao_amizade(grafo *g, int u)
{
		if (g == NULL || u < 0 || u > g -> tamanho) return NULL;

	arvore_avl *resultado = avl_nova();
	int n = 0, n2;
	int * vetor = grafo_adjacentes (g, u , &n);
	int * aux;

	for (int i = 0; i < n; i++)
	{
		n2 = 0;
		aux = grafo_adjacentes (g, vetor[i] , &n2);

		for (int j = 0; j < n2; j++)
		{
			if (grafo_aresta (g, u, aux[j]) == 0 && u != aux [j]) avl_insere (resultado, (const int) aux[j]);

		}
	}
	
	return resultado;
}

/********************************************************************/
/********************************************************************/
grafo *init_rede()
{
	grafo *g = grafo_novo(10, NAODIRECIONADO);
	if (!g)
		return NULL;
	grafo_adiciona(g, 1, 2);
	grafo_adiciona(g, 1, 3);
	grafo_adiciona(g, 2, 3);
	grafo_adiciona(g, 2, 4);
	grafo_adiciona(g, 2, 5);
	grafo_adiciona(g, 3, 5);
	grafo_adiciona(g, 3, 6);
	grafo_adiciona(g, 3, 7);
	grafo_adiciona(g, 7, 6);
	return g;
}

int main()
{
	grafo *rede = init_rede();
	arvore_avl *sugestoes = NULL;

	sugestoes = sugestao_amizade(rede, 2);
	if (sugestoes == NULL)
		printf("\nUtilizador '2' ou rede nao existe\n");
	else
	{
		printf("\nSugestoes de amizade para '2': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	sugestoes = sugestao_amizade(rede, 12);
	if (sugestoes == NULL)
		printf("\nUtilizador '12' ou rede nao existe\n");
	else
	{
		printf("\nSugestoes de amizade para '9': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	grafo_apaga(rede);
	return 1;
}
