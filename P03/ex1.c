#include <stdio.h>
#include <string.h>
#include "lista.h"
#define NMAX 150

int main(){
    char str[NMAX]={};
    lista *l = lista_nova();
        printf("Lista nova criada\n");
    if (l==NULL)
    {
        printf("Lista não criada\n");
        return 0;
    }
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
    
    
    fclose(f);
}