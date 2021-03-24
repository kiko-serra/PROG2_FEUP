#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char uc[15], letivo[100];
    int ano;
    char linha[100] = "Programação 2-1-2020/20  21";

    char *token;
    token=strtok(linha, "-");
    strcpy(uc, token);
    token = strtok(NULL, "-");
    ano = atoi(token);
    // o ultimo le ate acabar a linha
    token = strtok(NULL, "-");
    strcpy(letivo, token);
    printf("%s %d %s\n", uc, ano, letivo);

//o que fazer se tiver uma planta errada? colecao null ou planta esquecer
  
}