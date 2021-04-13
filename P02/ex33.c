#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 80
#define NSTRINGS 3

int main()
{
    char **v;
    char str[NMAX];
    int i, pos;
    v = malloc(NSTRINGS * sizeof(char*));
    for (int i = 0; i < NSTRINGS; i++)
    {
        v[i]=NULL;
    }
    
    while(1)
    {
        for(i = 0; i < NSTRINGS; i++)
		{
			printf("[%d] ", i+1);
			if(v[i] == NULL)
				printf("(vazio)\n");
			else
            	printf("%s\n", v[i]);
		}

		do        
		{
            printf("Posicao para nova string (1 a %d): ", NSTRINGS);
            scanf("%d", &pos);
            getchar(); /* elimina \n */
		}
		while(pos < 0 || pos > NSTRINGS);

        if (pos == 0)
            break;

        printf("Nova String: ");
        fgets(str, NMAX, stdin);
        str[strlen(str) - 1] = '\0';

        v[pos - 1] = realloc(v[pos - 1], strlen(str)+1);
		strcpy(v[pos - 1], str);
    }
    for (int i = 0; i < NSTRINGS; i++)
    {
        free(v[i]);
        v[i]=NULL;
    }
    free(v);
    v=NULL;
    return 0;
}
