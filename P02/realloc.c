#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCAR 80

int main(){
    char *s;
    s= (char *) malloc(NCAR);
    printf("Escreva uma frase: ");
    fgets(s, NCAR, stdin);
    printf("%s\n", s);
    s= (char*) realloc(s, 20);
    strcpy(s, "Bom dia! ");
    printf("%s\n", s);
}