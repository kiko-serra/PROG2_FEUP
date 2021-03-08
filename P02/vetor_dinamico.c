#include <stdio.h>
#include <stdlib.h>
int* criavetor(int n){
    int *pi, i;
    pi=(int *)malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        printf("Introduza o %dº elemento: ", i+1); scanf("%d", &pi[i]);
    }
    return pi;
}
int main(){
    int *pi, i, n;
    printf("Quantos elementos tem o vetor? "); scanf("%d", &n);
    pi=criavetor(n);
    for (i = 0; i < n; i++)
    {
        printf("%d\n", pi[i]);
    }
    return 0;
}