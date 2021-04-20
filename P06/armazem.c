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
	if (armz == NULL || fila_tamanho(armz->contentores) == 0)
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
	if (armz->comprimento == armz->contentores->tamanho)
	{
		if (armz->altura == fila_back(armz->contentores)->tamanho)
		{
			return 1;
		}
	}

	/* devolve nao cheio */

	return 0;
}

/* alinea e) */
int armazenar_contentor(armazem *armz, contentor *contr)
{
	/* devolve nao ha' espaco */
	if (armz == NULL || contr == NULL||armazem_cheio(armz))
	{
		return 0;
	}
	pilha *back = fila_back(armz->contentores);  // última pilha da fila
    if(back && (back->tamanho < armz->altura))  // se pilha criada e com espaço livre
        pilha_push(back, contr);  // adiciona novo contentor
    else  // se pilha não criada ou cheia
    {
        back = pilha_nova();  // cria a pilha
        if(!back)
            return 0;
        fila_push(armz->contentores, back);  // adiciona-a à fila
        pilha_push(back, contr);  // adiciona novo contentor à nova pilha
    }
	return 1;
}

/* alinea f) */
contentor *expedir_contentor(armazem *armz)
{
	if (armazem_vazio(armz) || armz == NULL)
	{
		return NULL;
	}
	contentor *aux = contentor_novo(pilha_top(fila_front(armz->contentores))->destino, pilha_top(fila_front(armz->contentores))->valor);
	if (fila_front(armz->contentores)->tamanho == 1)
	{
		fila_pop(armz->contentores);
		return aux;
	}
	pilha_pop(fila_front(armz->contentores));
	return aux;
}
