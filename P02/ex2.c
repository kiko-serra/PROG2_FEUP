#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#define NMAX 80

int main(){
    int i, a;
    char str[NMAX];
    vetor *v = vetor_novo();
    printf("Vetor novo criado\n");
    if (v==NULL)
    {
        printf("Vetor não criado\n");
        return 0;
    }
    
    //Solicita 5 frases com máximo de 80 caracteres e guarda em v
    for (i = 0; i < 5; i++)
    {
        printf("Insira a %dº frase: ", i+1); fgets(str, NMAX, stdin); str[strlen(str)-1]='\0';
        vetor_insere(v, str, i);
    }
    //imprime as 5 strings do vetor
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", vetor_elemento(v, i));
    }
    printf("Existem %d elementos no vetor\n", vetor_tamanho(v));
    printf("Escreva uma frase: "); fgets(str, NMAX, stdin); str[strlen(str)-1]='\0';
    //se a frase ja existir no vetor apagar essa frase do vetor
    a=vetor_pesquisa(v, str);
    if(a!=-1){
        vetor_remove(v, a);
    }
    //imprimir o vetor
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", vetor_elemento(v, i));
    }
    //ordenar o vetor por ordem alfabetica
    vetor_ordena(v);
    //imprimir o vetor
    printf("Vetor ordenado por ordem alfabética: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", vetor_elemento(v, i));
    }
    printf("Existem %d elementos no vetor antes de ser invertido\n", vetor_tamanho(v));
    vetor_inverte(v);
    for (int i = 0; i < vetor_tamanho(v); i++)
    {
        printf("%s\n", v->elementos[i].str);
    }
    
    

    return 0;
}