#include <stdio.h>

int main()
{
    int v1[5], v2[5], v3[5], a = 0;
    printf("Vetor 1:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Introduza o %dº número:\n", i + 1);
        scanf("%d", &v1[i]);
    }
    printf("Vetor 2:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Introduza o %dº número:\n", i + 1);
        scanf("%d", &v2[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (v1[i] == v2[j])
            {
                v3[a] = v1[i];
                a++;
            }
        }
    }
    printf("Comuns:");
    for (int i = 0; i < a; i++)
    {
        printf(" %d", v3[i]);
    }
    printf("\n");
    return 0;
}