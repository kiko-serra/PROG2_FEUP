#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem *armazem_novo(int comprimento, int altura)
{
	if (comprimento < 1 || altura < 1)
	{
		return NULL;
	}
	armazem *arma = (armazem *)malloc(sizeof(armazem));
	if (arma == NULL)
	{
		return NULL;
	}
	arma->altura = altura;
	arma->comprimento = comprimento;
	arma->contentores = fila_nova();
	return arma;
}

/* alinea c) */
int armazem_vazio(armazem *armz)
{
	if (armz == NULL || armz->contentores->tamanho == 0)
	{
		return 1;
	}
	return 0;
}

/* alinea d) */
int armazem_cheio(armazem *armz)
{
	if (armz == NULL)
	{
		return 0;
	}
	//ver se o comprimento do armazem é igual ao tamanho da fila
	// e ver se o tamanho da ultima pilha é igual a altura do armazem
	if ((armz->comprimento == armz->contentores->tamanho) && (armz->altura == fila_back(armz->contentores)->tamanho))
	{
		return 1;
	}

	/* devolve nao cheio */
	if ((armz->comprimento > armz->contentores->tamanho) || (armz->altura > fila_back(armz->contentores)->tamanho))
	{
		return 0;
	}
}

/* alinea e) */
int armazenar_contentor(armazem *armz, contentor *contr)
{
	/* devolve nao ha' espaco */
	if (armz == NULL || contr == NULL)
	{
		return 0;
	}
	if (armazem_cheio(armz))
	{
		return 0;
	}
	if (fila_back(armz->contentores)->raiz->elemento->tamanho == armz->altura)
	{
		pilha *pilhan = pilha_nova();
		fila_push(armz->contentores, pilhan);

		pilha_push(fila_back(armz->contentores), contr);

		return 1;
	}
}

/* alinea f) */
contentor *expedir_contentor(armazem *armz)
{
	if (!armazem_vazio(armz) || armz == NULL)
	{
		return NULL;
	}
	if (pilha_top(fila_front(armz->contentores))==pilha_down(fila_front(armz->contentores)))
	{
		/* code */
	}
	
	return pilha_top(fila_front(armz->contentores));
}
