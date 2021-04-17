
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lista1.h"


int main(){
    
    lista *l = lista_nova();
    if (l==NULL)
    {
        printf("Lista não criada!\n");
        return 0;
    }
   
    char nome_ficheiro[]={"arquivo.txt"};
    char str[]={};
    FILE *f=fopen("arquivo.txt", "r");
     
    while (1){
        printf("merda\n");
        if (!fgets(str, 80, f))
        {
            break;
        }
        str[strlen(str)-1]='\0';
        printf("merda2\n");
        
        if(!lista_insere(l, str, NULL)){
            printf("Erro a inserir na lista!\n");
            return -1;
        }
        
    }
    printf("Foram carregados %d jogos\n", l->tamanho);
    lista_imprime(l);
    printf("\n");


    fclose(f);
    return 0;
}