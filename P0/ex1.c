#include <stdio.h>

int main(){
    float a, x, inc, f;
    int min, max;
    printf("Qual o valor de a?\n"); scanf("%f", &a);
    printf("Qual o intervalo ?\n"); scanf("%d %d", &min, &max);
    printf("Qual o incremento?\n"); scanf("%f", &inc);
    x= (float) min;
    while (x<=max)
    {
        f = x * x * a;
        printf("f(%.1f) = %.2f\n", x, f);
        x+=inc;
    }
    return 0;
}