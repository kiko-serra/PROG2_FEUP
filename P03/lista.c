/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2018/19        */
/*****************************************************************/

#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

l_elemento *novo_elemento(const char *valor)
{
	/* aloca memoria para a estrutura lista */
	l_elemento *item = (l_elemento *)malloc(sizeof(l_elemento));
	if (item == NULL)
		return NULL;

	/* aloca memoria para string */
	item->str = (char *)malloc((strlen(valor) + 1) * sizeof(char));
	if (item->str == NULL)
	{
		free(item);
		return NULL;
	}

	/* copia valor */
	strcpy(item->str, valor);

	/* item ainda nao tem proximo */
	item->proximo = NULL;
	item->anterior = NULL;

	return item;
}

lista *lista_nova()
{
	/* cria lista */
	lista *lst = (lista *)malloc(sizeof(lista));
	if (lst == NULL)
		return NULL;

	/* lista esta' vazia */
	lst->inicio = NULL;
	lst->fim = NULL;
	lst->tamanho = 0;

	return lst;
}

void lista_apaga(lista *lst)
{
	l_elemento *aux;

	if (lst == NULL)
		return;

	/* percorre toda a lista e liberta memoria de
	   cada item e respectiva string */
	while (lst->inicio)
	{
		aux = lst->inicio;
		lst->inicio = lst->inicio->proximo;
		free(aux->str);
		free(aux);
	}

	free(lst);
	return;
}

int lista_tamanho(lista *lst)
{
	if (lst == NULL)
		return -1;
	return lst->tamanho;
}

l_elemento *lista_inicio(lista *lst)
{
	if (lst == NULL)
		return NULL;
	return lst->inicio;
}

l_elemento *lista_fim(lista *lst)
{
	if (lst == NULL)
		return NULL;
	return lst->fim;
}

l_elemento *lista_elemento(lista *lst, int pos)
{
	int i;
	l_elemento *curr = NULL;

	if (lst == NULL || pos < 0 || pos >= lst->tamanho)
		return NULL;

	curr = lst->inicio;
	for (i = 0; i < pos; i++)
		curr = curr->proximo;

	return curr;
}

l_elemento *lista_insere(lista *lst, const char *valor, l_elemento *pos)
{
	l_elemento *curr = NULL;

	if (lst == NULL || valor == NULL)
		return NULL;

	/* cria novo item */
	curr = novo_elemento(valor);

	if (curr == NULL)
		return NULL;

	lst->tamanho++;

	/* caso especial: inserir no fim da lista */
	if (pos == NULL)
	{
		/* se e' primeiro l_elemento */
		if (lst->inicio == NULL)
		{
			lst->inicio = lst->fim = curr;
		}
		else
		{
			curr->anterior = lst->fim;
			lst->fim->proximo = curr;
			lst->fim = curr;
		}
		return curr;
	}

	/* caso especial: inserir no inicio da lista */
	if (pos == lst->inicio)
	{
		curr->proximo = lst->inicio;
		lst->inicio->anterior = curr;
		lst->inicio = curr;
		return curr;
	}

	/* troca apontadores para inserir item */
	curr->anterior = pos->anterior;
	curr->proximo = pos;
	pos->anterior->proximo = curr;
	pos->anterior = curr;

	return curr;
}

l_elemento *lista_remove(lista *lst, l_elemento *pos)
{
	l_elemento *aux;

	if (lst == NULL || pos == NULL)
		return NULL;

	lst->tamanho--;

	/* troca apontadores para remover item */
	if (pos->anterior != NULL)
		pos->anterior->proximo = pos->proximo;
	else /* e' o primeiro */
		lst->inicio = pos->proximo;
	if (pos->proximo != NULL)
		pos->proximo->anterior = pos->anterior;
	else /* e' o ultimo */
		lst->fim = pos->anterior;

	/* liberta memoria associada ao item removido */
	aux = pos->proximo;
	free(pos->str);
	free(pos);

	return aux;
}

int lista_atribui(lista *lst, l_elemento *pos, const char *str)
{
	if (lst == NULL || pos == NULL || str == NULL)
		return -1;

	/* realoca memoria para nova string */
	pos->str = (char *)realloc(pos->str, (strlen(str) + 1) * sizeof(char));
	if (pos->str == NULL)
		return -1;
	strcpy(pos->str, str);

	return 0;
}

l_elemento *lista_pesquisa(lista *lst, const char *str, int origem)
{
	l_elemento *aux;

	if (lst == NULL || str == NULL || (origem != LISTA_INICIO && origem != LISTA_FIM))
		return NULL;

	if (origem == LISTA_INICIO)
	{
		/* pesquisa sequencial: a partir do inicio */
		for (aux = lst->inicio; aux != NULL; aux = aux->proximo)
		{
			if (strcmp(aux->str, str) == 0)
			{
				return aux;
			}
		}
		return NULL;
	}

	/* pesquisa sequencial: a partir do fim */
	for (aux = lst->fim; aux != NULL; aux = aux->anterior)
	{
		if (strcmp(aux->str, str) == 0)
		{
			return aux;
		}
	}
	return NULL;
}

int lista_ordena(lista *lst)
{
	l_elemento *next, *curr, *min;
	char *aux;

	if (lst == NULL)
		return -1;

	/* lista vazia ja' esta' ordenada */
	if (lst->tamanho == 0)
		return 0;

	/* algoritmo de ordenacao por seleccao */
	for (curr = lst->inicio; curr->proximo != NULL; curr = curr->proximo)
	{
		min = curr;
		next = curr->proximo;
		while (next != NULL)
		{
			if (strcmp(next->str, min->str) < 0)
				min = next;
			next = next->proximo;
		}
		/* basta trocar strings */
		if (min != curr)
		{
			aux = curr->str;
			curr->str = min->str;
			min->str = aux;
		}
	}

	return 0;
}

lista *lista_pesquisa_substring(lista *lst, char *substring)
{
	lista *novalista = lista_nova();
	l_elemento *aponta;
	aponta = lst->inicio;
	//faz a mesma coisa do que o ciclo while mas de maneira menos eficiente
	/* 	for(int i= 0; i < lista_tamanho(lst); i++){
		l_elemento *aux = lista_elemento(lst, i);
			if(strstr(aux->str, substring)!=NULL){
				lista_insere(novalista, aux->str, NULL);
			}
	} */

	while (aponta != NULL)
	{
		if (strstr(aponta->str, substring) != NULL)
		{
			lista_insere(novalista, aponta->str, NULL);
		}
		aponta = aponta->proximo;
	}
	return novalista;
}

lista *lista_pesq_substring_remove(lista *lst, char *substring)
{
	l_elemento *aponta, *aux;
	aponta = lst->inicio;
	while (aponta != NULL)
	{
		if (strstr(aponta->str, substring) != NULL)
		{
			aux = aponta->proximo;
			lista_remove(lst, aponta);
			aponta = aux;
		}
		else aponta = aponta->proximo;
	}
	return lst;
}
lista *lista_concatena(lista *lst1, lista *lst2)
{
	if (!lst1 || !lst2)
		return NULL;

	l_elemento *aponta2;
	aponta2 = lst2->inicio;
	while (aponta2 != NULL)
	{
		lista_insere(lst1, aponta2->str, NULL);
		aponta2 = aponta2->proximo;
	}

	return lst1;
}

void lista_imprime(lista *lst){
	int i=0;
	l_elemento *lindo=lst->inicio;
	if (!lst)
	{
		return;
	}
	if (lst->tamanho<0 || lst->tamanho==0)
	{
		return;
	}
	
	while (lindo!=NULL)
	{
		printf("Pos %d -> %s\n", i, lindo->str);
		i++;
		lindo=lindo->proximo;
	}
	return;
}