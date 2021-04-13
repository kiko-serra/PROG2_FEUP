#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NMAX 80
void imprime_vetor(vetor *v)
{
    for(int i = 0; i < vetor_tamanho(v); i++)
    {
        printf("[%d] %s\n", i, vetor_elemento(v, i));
    }
}
int main(){
    char str[NMAX];
    int pos;
    vetor *frases= vetor_novo();
    vetor *frases2 = vetor_novo();
    if (frases==NULL)
    {
        printf("Erro ao criar o vetor frases. \n");

    }
    
    // pedir ao user para introduzir 5 frases e gurdar em frases
    for (int i = 0; i < 5; i++)
    {
        printf("Escreva a %dº frase: ", i+1); fgets(str, NMAX, stdin);
        str[strlen(str)-1]='\0';
        vetor_insere(frases, str,i);
    }printf("\n");
    printf("Existem %d elementos no vetor:\n", vetor_tamanho(frases));
    
    //imprime as 5 frases pela ordem inicial
    imprime_vetor(frases);
    printf("\nIntroduza uma nova frase: "); fgets(str, NMAX, stdin);str[strlen(str)-1]='\0';
    pos=vetor_pesquisa(frases, str);
    if(pos!=-1){
        vetor_remove(frases, pos);
    }
    else{
        printf("\nFrase não encontrada na lista anterior\n");
        
    }
    printf("\nVetor apos remocao: \n");
    imprime_vetor(frases);
    vetor_ordena(frases);
    printf("\nVetor ordenado:\n");
    imprime_vetor(frases);
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Escreva a %dº frase: ", i+1); fgets(str, NMAX, stdin);
        str[strlen(str)-1]='\0';
        vetor_insere(frases2, str,i);
    }printf("\n");
    //concatena  imprime o concatenado
    vetor *y = vetor_concatena(frases, frases2);
    vetor_apaga(frases);
    vetor_apaga(frases2);
    printf("\nO vetor concatenado destes dois é:[ ");
    for (int i = 0; i < vetor_tamanho(y); i++)
    {
        if (i==vetor_tamanho(y)-1)
        {
            printf("%s ", vetor_elemento(y, i));
        }
        else{printf("%s; ", vetor_elemento(y, i));}
        
    }
    printf("]\n");
    if(!vetor_inverte(y)){printf("Não é possivel inverter o vetor\n");}

    printf("\nO vetor concatenado invertido é:[ ");
    for (int i = 0; i < vetor_tamanho(y); i++)
    {
        if (i==vetor_tamanho(y)-1)
        {
            printf("%s ", vetor_elemento(y, i));
        }
        else{printf("%s; ", vetor_elemento(y, i));}
        
    }
    printf("]\n");


    //free de tudo o que usamos
    free(frases->elementos);    
    free(frases);
    free(frases2->elementos);
    free(frases2);
    free(y->elementos);
    free(y);
    frases=NULL;
    frases2=NULL;
    y=NULL;

    return 0;
}