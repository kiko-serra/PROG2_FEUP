#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include <time.h>
#include "lista.h"

int main(){
    //1.1
    clock_t inicio, fim;
    double tempo;inicio = clock();
        char string[100];
        tabela_dispersao *tab= tabela_nova(100000, hash_djbm);
        FILE *f = fopen("englishwords.txt", "r");
        while (fgets(string, 100, f)!=NULL)
        {
            string[strlen(string)-1]='\0';
            tabela_adiciona(tab, string, string);
        } 
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos de inserir por tabela: %lf\n", tempo);

    fseek(f, 0, SEEK_SET); // volta ao inicio do ficheiro

    inicio = clock();
        lista *lst = lista_nova();
        char string1[100];
        while (fgets(string1, 100, f)!=NULL)
            {
            string1[strlen(string1)-1]='\0';
            lista_insere(lst, string1, NULL);
        } 
        
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos de inserir por lista: %lf\n", tempo);
    //1.2
    fseek(f, 0, SEEK_SET); // volta ao inicio do ficheiro

    int n;
    objeto *ob= tabela_elementos(tab, &n);
    int val;
    val= rand() % n; // gera um elemento aleatorio
    inicio = clock();
        tabela_valor(tab, ob[val].chave);
        
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos de pesquisar na tabela: %lf\n", tempo);



}