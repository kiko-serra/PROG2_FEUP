#include "pilha.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

float calcula_total(char* expressao_rpn){
    pilha *p=pilha_nova();

    if (expressao_rpn==NULL || p==NULL)
    {
        return 0;
    }
    char *token=strtok(expressao_rpn, " ");
    int res;

    while (token!=NULL)
    {
        
        if (token[0]>='0' && token[0]<='9')
        {   int c = atoi(token);
            pilha_push(p, c);
        }
        else {
            int op1=pilha_top(p);
            pilha_pop(p);
            int op2=pilha_top(p);
            pilha_pop(p);
            switch (token[0])
            {
            case '+':
                res=op2+op1;
                
                break;
            case '-':
                res=op2-op1;
                
                break;
            case '*':
                res=op2*op1;
                break;
            case '/':
                res=op2/op1;
                break;
            case '%':
                res=op2%op1;
                break;
            
            default:
            pilha_apaga(p);
                return 0000;
                break;
            }
            pilha_push(p, res);
        }
        token=strtok(NULL, " ");
    }
    int res_final=pilha_top(p);
    pilha_pop(p);

    pilha_apaga(p);
    return res_final;
}




int main(){
    printf("Expressão: ");
    char string[128];
    fgets(string, 128, stdin);
    string[strlen(string)-1]='\0';

    printf("Resultado : %.0f\n", calcula_total(string));
    return 0;
}