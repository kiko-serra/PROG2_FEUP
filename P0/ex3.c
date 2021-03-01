#include <stdio.h>
float avg(float x[]);
float max(float x[]);
float min(float x[]);
int main()
{
    float v[10];
    for (int i = 0; i < 10; i++)
    {
        printf("Introduza o %dº elemento\n", i + 1);
        scanf("%f", &v[i]);
    }
    printf("Media: %.2f\n", avg(v));
    printf("Máximo: %.2f\n", max(v));
    printf("Mínimo: %.2f\n", min(v));
    printf("Vetor:");
    for (int i = 0; i < 10; i++)
    {
        printf(" %.2f", v[i]);
    }
    printf("\n");
    return 0;
}
float avg(float x[])
{
    float soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += x[i];
    }
    return (float)soma / 10;
}
float max(float x[])
{
    float max;
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            max = x[i];
        }
        else
        {
            if (x[i] > max)
            {
                max = x[i];
            }
        }
    }
    return max;
}
float min(float x[]){
    float min;
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            min = x[i];
        }
        else
        {
            if (x[i] < min)
            {
                min = x[i];
            }
        }
    }
    return min;
}