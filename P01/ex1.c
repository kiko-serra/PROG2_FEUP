#include <stdio.h>

int main()
{
    FILE *f;
    int c, total = 0;
    int perc[26]={};
    char nomef[100];
    //printf("Qual o nome do ficheiro? ");
    //scanf("%s", nomef);
    f = fopen("lusiadas.txt", "r");
    while (!feof(f))
    {
        c = getc(f);
       

        if ((c >= 192 && c <= 195) || (c >= 224 && c <= 227))
        {
            c = 'a';
        }
        else if ((c >= 211 && c <= 213) || (c >= 243 && c <= 245))
        {
            c = 'o';
        }
        else if (c == 205 || c == 237)
        {
            c = 'i';
        }
        else if ((c >= 201 && c <= 202) || (c >= 233 && c <= 234))
        {
            c = 'e';
        }
        else if (c == 218 || c == 250)
        {
            c = 'u';
        }
        else if (c == 199 || c == 231)
        {
            c = 'c';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c += 32;
        }

        if (c >= 'a' && c <= 'z')
        {
            total++;
            perc[c-'a']++;
        }
    }

    fclose(f);
    printf("O número total de letras do ficheiro é: %d\n", total);
    for (int i = 0; i < 26; i++)
    {
        printf("Letra %c = %.2f%%\n", i +'a', ((float)perc[i]/total)*100);
    }
    return 0;
}