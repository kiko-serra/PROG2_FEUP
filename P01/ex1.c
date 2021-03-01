#include <stdio.h>

int main(){
    FILE *f;
    int c;
    char nomef[100];
    printf("Qual o nome do ficheiro? "); scanf("%s", nomef);
    f=fopen(nomef, "r");
    while (!feof(f))
    {
        c=getc(f);

        printf("%d - %c", c, c);
    }
    fclose(f);
    return 0;
}