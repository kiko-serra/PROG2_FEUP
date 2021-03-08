#include <stdio.h>
#include <stdlib.h>
int* criavetor(int n);
int main(){
    int *pi, i, n, j;
    printf("Quantos elementos tem o vetor? "); scanf("%d", &n);
    pi=criavetor(n);
    printf("Vetor original:[ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", pi[i]);
    }
    printf("]\n Números pares:[ ");
    for (j = 0; j < n; j++)
    {
        if (pi[j]%2==0)
        {
            printf("%d ", pi[j]);
        }   
    }
    printf("]\n Números impares:[ ");
    for (j = 0; j < n; j++)
    {
        if (pi[j]%2!=0)
        {
            printf("%d ", pi[j]);
        }   
    }
    printf("]\n");
    

    return 0;
}
int* criavetor(int n){
    int *pi, i;
    pi=(int *)malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        printf("Introduza o %dº elemento: ", i+1); scanf("%d", &pi[i]);
    }
    return pi;
}