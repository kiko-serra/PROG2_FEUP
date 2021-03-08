#include <stdio.h>
int ordenado(int src[], int n);
int main()
{
    int n, v[100];
    do
    {
        printf("Introduza o número de elementos: ");
        scanf("%d", &n);
    } while (n > 100);
    for (int i = 0; i < n; i++)
    {
        printf("Introduza o %dº elemento: ", i + 1);
        scanf("%d", &v[i]);
    }
    if (ordenado(v, n)==1)
    {
        printf("O vetor esta ordenado.\n");
        printf("Vetor em ordem decrescente:");
        for (int i = 0; i < n; i++)
        {
            printf(" %d", n - i);
        }
        printf("\n");
    }
    else
    {
        printf("O vetor nao está ordenado.\n");
    }

    return 0;
}
int ordenado(int src[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (src[i + 1] < src[i])
        {
            continue;
        }
        else
        {
            return 0;
            break;
        }
    }

    return 1;
}