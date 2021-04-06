#include <stdio.h>

int main()
{
    FILE *f;
    int c, total = 0;
    int perc[26]={};
    char nomef[100];
    f = fopen("lusiadas-utf8.txt", "r");
    if(!f)
        {
            printf("Erro a abrir \n");
            return -1;
        }
    int char_hist[3]={};
    // read until EOF
    for(int c, c_prev = 0x00; (c = getc(f)) != EOF;)
    {
        if(c_prev==0xC3)
        {
            if(c==0x83 || c==0xA3)
                char_hist[0]++;
            else if(c==0x95 || c==0xB5)
                char_hist[1]++;
            else if(c==0x87 || c==0xA7)
                char_hist[2]++;
        }
        c_prev = c;
    }
    fclose(f);

    printf("Letra A com til: %d\n", char_hist[0]);
    printf("Letra O com til: %d\n", char_hist[1]);
    printf("Letra C com cedilha: %d\n", char_hist[2]);
    return 0;
}