#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
lista *filtra_titulos(lista *lista1, lista *lista2)
{
	if (lista1 == NULL || lista2 == NULL)
	{
		return NULL;
	}
	lista *lista_n = lista_nova();
	if (lista_n == NULL)
	{
		return NULL;
	}
	l_elemento *aponta = lista1->inicio;
	//l_elemento *aponta2= lista2->inicio;
	while (aponta != NULL)
	{
		if (lista_pesquisa(lista2, aponta->str, LISTA_INICIO) != NULL)
		{
			aponta = aponta->proximo;
		}
		else
		{
			lista_insere(lista_n, aponta->str, NULL);
			aponta = aponta->proximo;
		}
	}
	if (lista_tamanho(lista_n) > lista_tamanho(lista1))
	{
		return NULL;
	}

	return lista_n;
}

/*** problema 1.2 ***/
int retira_comecados_por(lista *lst, char *inicio)
{
	int retirados = 0;
	if (lst == NULL || inicio == NULL)
	{
		return 0;
	}
	l_elemento *aponta = lst->inicio;
	char string[100];

	while (aponta != NULL)
	{
		if (strstr(aponta->str, inicio) != NULL)
		{

			aponta = lista_remove(lst, aponta);
			retirados++;
		}
		else
			aponta = aponta->proximo;
	}
	return retirados;
}

/*** problema 1.3 ***/
// sempre que faco pop tenho que ver se o tilulo é igual
int insere_na_pilha(pilha *p, char *titulo)
{
	char string[120];
	pilha *po = pilha_nova();
	if (p == NULL || titulo == NULL || po == NULL)
	{
		return 0;
	}

	char *aux;
	while (strcmp(titulo, pilha_top(p)) <= 0)
	{
		if (pilha_vazia(p))
		{
			break;
		}

		if (!strcmp(titulo, pilha_top(p)))
		{
			return 0;
		}
		if (strcmp(titulo, pilha_top(p)) < 0)
		{
			aux = pilha_top(p);
			pilha_pop(p);
			pilha_push(po, aux);
		}
	}
	pilha_push(p, titulo);

	for (int i = 0; i < pilha_tamanho(po); i++)
	{
		pilha_push(p, pilha_top(po));
		pilha_pop(po);
	}
	pilha_apaga(po);
	return 1;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

lista *lerParaLista(FILE *ficheiro)
{
	char buffer[256], *nlptr;
	lista *l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while (fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		lista_insere(l, buffer, NULL);
	}

	return l;
}

pilha *lerParaPilha(FILE *ficheiro)
{
	char buffer[256], *nlptr;
	pilha *p;

	if (ficheiro == NULL)
		return NULL;

	p = pilha_nova();

	while (fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		pilha_push(p, buffer);
	}
	return p;
}

void imprimeLista(lista *l, unsigned int n)
{
	if (l->tamanho < n)
		printf("ERRO... Lista possui menos de %d elementos\n", n);
	unsigned int i;
	l_elemento *aux = l->inicio;
	for (i = 0; i < n; i++)
	{
		printf("%dº Livro: %s\n", i + 1, aux->str);
		aux = aux->proximo;
	}
}

int main()
{
	FILE *f;
	lista *l1 = NULL, *l2 = NULL, *l = NULL;
	pilha *p;
	int nmov, res;
	char *tit1;

	/* testes */
	f = fopen("livros1.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l1 = lerParaLista(f);
	fclose(f);

	f = fopen("livros2.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lerParaLista(f);
	fclose(f);

	/* inicio teste prob1.1 */
	l = filtra_titulos(l1, l2);
	if (l)
	{
		printf("\nLista resultante contem %d livros.\n", lista_tamanho(l));
		if (lista_tamanho(l) != 12)
			printf("ERRO.. Tamanho da lista incorreto(tamanho: %d; esperado: 12)\n", lista_tamanho(l));
		else
			imprimeLista(l, lista_tamanho(l));
	}
	else
		printf("\nERRO.. filtra_titulos retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	f = fopen("livros.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	lista_apaga(l);
	l = lerParaLista(f);
	fclose(f);

	nmov = retira_comecados_por(l, "A");
	printf("\nForam retirados %d livros\n", nmov);
	printf("A lista contém %d livros\n", lista_tamanho(l));
	if (nmov != 146)
		printf("ERRO.. Numero de livros removidos incorreto (removidos: %d; esperado: 146\n", nmov);
	else if (lista_tamanho(l) != 389)
		printf("ERRO.. Lista incorreta (tamanho: %d; esperado: 389)\n", lista_tamanho(l));
	else
		printf("9º livro da lista: %s\n", lista_elemento(l, 8)->str);
	/* fim teste prob1.2 */

	/* inicio teste prob1.3 */
	f = fopen("livros2.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	p = lerParaPilha(f);
	fclose(f);

	tit1 = "Fora de Horas";
	res = insere_na_pilha(p, tit1);

	if (res == 0)
	{
		printf("\n'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("\nERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n", pilha_tamanho(p));
	else
	{
		printf("\n'%s' foi inserido na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}

	tit1 = "Mundo incompleto";
	res = insere_na_pilha(p, tit1);

	if (res == 0)
	{
		printf("'%s' já existe na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	else if (pilha_tamanho(p) != 32)
		printf("ERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n", pilha_tamanho(p));
	else
	{
		printf("'%s' foi inserido na pilha\n", tit1);
		printf("Numero de elementos na pilha: %d\n", pilha_tamanho(p));
	}
	puts("");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	pilha_apaga(p);

	return 0;
}