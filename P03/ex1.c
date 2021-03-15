#include <stdio.h>
#include <string.h>
#include "lista.h"
#define NMAX 150

int main(){
    char str[NMAX]={};
    lista *l = lista_nova();
    int i=0;

    //1a    
    if (l==NULL)
    {
        printf("Lista não criada\n");
        return 0;
    }
    printf("Lista nova criada\n");
    FILE *f = fopen("arquivo.txt", "r");
    while (1)
    {
        if(!fgets(str,NMAX, f)) break;
        str[strlen(str)-1]='\0';
        if(!lista_insere(l, str, NULL)){
            printf("Erro a inserir na lista!\n");
            return -1;
        }
    }
    printf("A lista tem %d elementos.\n", l->tamanho);
    //1b
    lista *novalista = lista_pesquisa_substring(l, "PS2");
    printf("%d\n", novalista->tamanho);
    //1c
    lista_pesq_substring_remove(l, "PS2");
    printf("%d\n", l->tamanho);
    //1d
    lista *l2 = lista_nova();
    if (l2==NULL)
    {
        printf("Lista não criada\n");
        return 0;
    }
    printf("Lista nova criada\n");
    
    FILE *f2 = fopen("oldies.txt", "r");
    while (1)
    {
        if(!fgets(str,NMAX, f2)) break;
        str[strlen(str)-1]='\0';
        if(!lista_insere(l2, str, NULL)){
            printf("Erro a inserir na lista!\n");
            return -1;
        }
    }
    printf("Foram carregados %d jogos antigos.\n", l2->tamanho);
    lista_concatena(l, l2);
    printf("A lista depois de concatenada tem %d elementos.\n", l->tamanho);
    //1e
    if(lista_ordena(l)==-1){
        printf("Erro a ordenar a lista.\n");
        return -1;
    }
    printf("Lista ordenada:\n"); 
    lista_imprime(l);
    //1f
    l_elemento *jogo = lista_pesquisa(l, "Duke Nukem (PS3)", LISTA_INICIO);
    if (!jogo)
    {
        printf("Elemento não encontrado.\n");
        return -1;
    }
    while (1)
    {
        if (lista_elemento(l, i)== jogo)
        {
            printf("O jogo Duke Nukem (PS3) encontra-se na posição %d.\n", i);
            break;
        }
        i++;
        
    }
    
    
    

    fclose(f);
    fclose(f2);
    return 0;
}