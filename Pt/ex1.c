
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lista1.h"

int main()
{

    lista *l = lista_nova();
    if (l == NULL)
    {
        printf("Lista não criada!\n");
        return 0;
    }

    char nome_ficheiro[] = {"arquivo.txt"};

    l = lista_importa(l, nome_ficheiro);

    printf("Foram carregados %d jogos\n", l->tamanho);
    lista_imprime(l);
    printf("\n");

    //Fim ex1a inicio ex1b
    char jogo[20] = {"PS2"};
    lista *substring = lista_pesquisa_substring(l, jogo);
    //fim 1b inicio 1c
    lst_pesq_sub_remo(l, jogo);
    printf("Após a remoção de jogos %s a lista tem %d jogos. \n\n", jogo, l->tamanho);
    lista_imprime(l);
    printf("\n");
    //fim 1c inicio 1d

    lista *lst2 = lista_nova();
    lst2 = lista_importa(lst2, "oldies.txt");
    printf("\nForam carregados %d jogos antigos:\n", lst2->tamanho);
    lista_concatena(l, lst2);

    lista_imprime(l);
    printf("\n");
    //fim 1d inicio 1e
    lista_ordena(l);
    printf("\nLista ordenada: \n");
    lista_imprime(l);
    //fim 1e inicio 1f

    int i=0;
    l_elemento *jogo_pesquisa = lista_pesquisa(l, "Duke Nukem (PS3)", LISTA_INICIO);
    if (!jogo_pesquisa)
    {
        printf("\nElemento não encontrado.\n");
        return -1;
    }
    while (1)
    {
        if (lista_elemento(l, i)== jogo_pesquisa)
        {
            printf("\nO jogo %s encontra-se na posição %d.\n",jogo_pesquisa->str, i);
            break;
        }
        i++;
        
    }
    //fim 1f inicio 1g
    printf("O jogo Minesweeper (PC) foi inserido na posição %d\n\n", lista_insere_ordenada(l, "Minesweeper (PC) "));
    //lista_imprime(l);

    lista_apaga(l);
    lista_apaga(substring);
    lista_apaga(lst2);


    return 0;
}