#include "pilha.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#define MAX 128
#define erro 00000;

float calcula_total(char *expressao){
    pilha *pilhan=pilha_nova();
    char *token = strtok(expressao, " ");
    while (token)
    {
        if (token[0]>='0'&& token[0]<='9') // número, token[0], para vermos na primeira posicao da string se é um número ou nao
        {
            int elemento= atoi(token);
            pilha_push(pilhan, elemento);
        }
        else{
            int b = pilha_top(pilhan);
            pilha_pop(pilhan);
            int a = pilha_top(pilhan);
            pilha_pop(pilhan);
            int res;
            switch (token[0])
            {
            case '+':
                res= a+b;
                break;
            case '-':
                res= a-b;
                break;
            case '*':
                res= a*b;
                break;
            case '/':
                res= a/b;
                break;
            case '%':
                res= a%b;
                break;    
            default:
                pilha_apaga(pilhan);
                
                return erro;
                break;
            }
            pilha_push(pilhan, res);
        }
        token = strtok(NULL, " ");
        
    }
    int res_final=pilha_top(pilhan);
    pilha_pop(pilhan);
    if(pilha_tamanho(pilhan) != 0)  // se a pilha não ficou vazia no fim, algo correu mal
    {
        pilha_apaga(pilhan);
        return erro;
    }
    pilha_apaga(pilhan);
    return res_final;
    
}



int main(){
    char expressao[MAX+1];
    printf("Expressão: ");
    fgets(expressao, MAX, stdin);
    expressao[strlen(expressao)-1]='\0';
    
    
    int res = calcula_total(expressao);
    printf("Resultado: %d\n", res);
    return 0;
}