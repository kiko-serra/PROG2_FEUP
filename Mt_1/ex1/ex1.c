#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/
void lista_imprime(lista *lst)
{
    lista_ordena(lst);
    l_elemento *aponta = lst->inicio;
    while (aponta != NULL)
    {
        printf("%s\n", aponta->str);
        aponta = aponta->proximo;
    }
}
/*** problema 1.1 ***/
lista *junta_nomes(lista *lst1, lista *lst2)
{
    /* complexidade do algoritmo: ______________  -> como ainda nao demos nao sai no teste*/
    if (!lst1 || !lst2)
    {
        return NULL;
    }
    lista *lis = lista_nova();
    l_elemento *aponta1 = lst1->inicio;
    l_elemento *aponta2 = lst2->inicio;
    if (!lis)
    {
        return NULL;
    }
    while (aponta1)
    {
        lista_insere(lis, aponta1->str, NULL);
        aponta1 = aponta1->proximo;
    }
    while (aponta2)
    {
        lista_insere(lis, aponta2->str, NULL);
        aponta2 = aponta2->proximo;
    }
    //lista_imprime(lis);
    return lis;
}

/*** problema 1.2 ***/
lista *lista_remove_duplicados(lista *lst)
{
    if (lst->tamanho == 0 || lst == NULL)
    {
        return NULL;
    }
    lista *lis = lista_nova();
    l_elemento *aponta = lst->inicio;
    l_elemento *aux;
    l_elemento *aux2;
    if (lis == NULL)
    {
        return NULL;
    }
    lista_ordena(lst);
    while (aponta != NULL)
    {

        aux = aponta->proximo;
        if (aux == NULL)
        {
            break;
        }

        if (!strcmp(aponta->str, aux->str))
        {
            lista_insere(lis, aux->str, NULL);
            aponta = lista_remove(lst, aux);
        }
        else
            aponta = aponta->proximo;
    }

    return lis;
}

/*** problema 1.3 ***/
fila *pesquisa_nomes(lista *lst, char *nome)
{
    if (lst->tamanho == 0 || lst == NULL || nome == NULL)
    {
        return NULL;
    }
    fila *fil = fila_nova();
    if (fil == NULL)
    {
        return NULL;
    }
    l_elemento *aponta = lst->inicio;
    while (aponta != NULL)
    {
        if (strstr(aponta->str, nome) != NULL)
        {
            fila_push(fil, aponta->str);
        }
        aponta = aponta->proximo;
    }

    return fil;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaLista(FILE *ficheiro, lista *l)
{
    char buffer[256], *nlptr;

    if (ficheiro == NULL || l == NULL)
        return;

    while (fgets(buffer, 255, ficheiro) != NULL)
    {
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';
        lista_insere(l, buffer, NULL);
    }
}

int main()
{
    FILE *f;
    lista *l1 = NULL, *l2 = NULL, *l12 = NULL, *l = NULL, *duplicados = NULL;
    fila *resultado = NULL;
    l_elemento *e;

    /* testes */
    f = fopen("nomes1.txt", "r");
    if (f == NULL)
    {
        printf("Erro ao ler ficheiro de entrada.\n");
        return 1;
    }
    l12 = lista_nova();
    l1 = lista_nova();
    lerParaLista(f, l1);
    rewind(f);
    lerParaLista(f, l12);
    fclose(f);

    f = fopen("nomes2.txt", "r");
    if (f == NULL)
    {
        printf("Erro ao ler ficheiro de entrada.\n");
        return 1;
    }
    l2 = lista_nova();
    lerParaLista(f, l2);
    rewind(f);
    lerParaLista(f, l12);
    fclose(f);

    /* inicio teste prob1.1 */
    l = junta_nomes(l1, l2);
    if (l)
        printf("\nLista resultante contem %d nomes.\n", lista_tamanho(l));
    else
        printf("\njunta_nomes retornou NULL\n");
    /* fim teste prob1.1 */

    /* inicio teste prob1.2 */
    duplicados = lista_remove_duplicados(l12);
    if (duplicados)
    {
        int n = 0;
        printf("\nNomes duplicados (total de %d):\n", lista_tamanho(duplicados));
        for (e = duplicados->inicio; e != NULL && n < 3; e = e->proximo, n++)
            printf("%s\n", e->str);
        if (lista_tamanho(duplicados) > 5)
        {
            puts("...");
            for (; e->proximo != NULL; e = e->proximo)
                ;
            printf("%s\n", e->str);
        }
        else
            for (; e != NULL; e = e->proximo)
                printf("%s\n", e->str);
        if (lista_tamanho(l12) != 302)
            printf("Nem todos os nomes duplicados foram removidos da lista (tamanho: %d; esperado: 302)\n", lista_tamanho(l12));
    }
    else
        printf("\nlista_remove_duplicados retornou NULL\n");
    /* fim teste prob1.2 */

    /* inicio teste prob1.3 */
    resultado = pesquisa_nomes(l1, "SILVA");
    if (resultado)
    {
        int n = 0;
        printf("\nNomes encontrados (%d): \n", fila_tamanho(resultado));
        while (!fila_vazia(resultado) && n < 3)
        {
            printf("%s\n", fila_front(resultado));
            fila_pop(resultado);
            n++;
        }
        if (fila_tamanho(resultado) > 2)
        {
            puts("...");
            while (fila_tamanho(resultado) > 1)
                fila_pop(resultado);
            printf("%s\n", fila_front(resultado));
            fila_pop(resultado);
        }
        else
        {
            while (!fila_vazia(resultado))
            {
                printf("%s\n", fila_front(resultado));
                fila_pop(resultado);
            }
        }
    }
    else
        printf("\npesquisa_nomes retornou NULL\n\n");
    /* fim teste prob1.3 */

    lista_apaga(l);
    lista_apaga(l1);
    lista_apaga(l2);
    lista_apaga(duplicados);
    fila_apaga(resultado);

    return 0;
}