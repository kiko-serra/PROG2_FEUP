#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include <time.h>
#include "lista.h"

int main(){
    clock_t inicio, fim;
    double tempo;inicio = clock();
        char string[100];
        tabela_dispersao *tab= tabela_nova(100000, hash_djbm);
        FILE *f = fopen("englishwords.txt", "r");
        do
        {
            tabela_adiciona(tab, string, string);
        } while (fgets(string, 100, f)!=NULL);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);

    fseek(f, 0, SEEK_SET);
    inicio = clock();
        lista *lst = lista_nova();
        char string1[100];
        do
        {
            strlen
            lista_insere(lst, string1, NULL);
        } while (fgets(string1, 100, f)!=NULL);
        
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    
    
    


}