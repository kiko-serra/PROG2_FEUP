#include <stdio.h>
#include <stdlib.h>


int main()
{
    int pares=0, impares=0;

    int n;
    printf("Número de elementos: \n");
    scanf("%d", &n);
    int *v = (int *)malloc(sizeof(int) * n);
    if (!v)
    {
        printf("Falha ao alocar memória para o vetor V\n");
        return -1;
    }

    int *v_pares=NULL;
    int *v_impares=NULL;
    for (int i = 0; i < n; i++)
    {
        printf("Introduza o %dº elemento: ", i + 1);
        scanf("%d", &v[i]);
        
        if (v[i]%2==0)
        {
            v_pares=(int*)realloc(v_pares, sizeof(int)*(++pares));
            v_pares[pares-1]=v[i];
        }
        else{
            
            v_impares=(int*)realloc(v_impares, sizeof(int)*(++impares));
            v_impares[impares-1]=v[i];
        
        }
        
    }
    printf("Vetor originar: [ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("]\nNúmeros pares: [ ");
    for (int i = 0; i < pares; i++)
    {
        printf("%d ", v_pares[i]);
    }
    printf("]\nNúmeros impares: [ ");
    for (int i = 0; i < impares; i++)
    {
        printf("%d ", v_impares[i]);
    }
    printf("]\n");
    free(v);
    free(v_impares);
    free(v_pares);
    v = NULL;
    v_pares = NULL;
    v_impares = NULL;
    return 0;
}
