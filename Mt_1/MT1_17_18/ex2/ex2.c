#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
// criar vetor e ir pondo nome de pessoas sem repetir
// criar outro vetor para contar o numero de cartas que cada um tem
// ambos num ciclo for para a posicao da primeira pessoa ser igual nos dois vetores
vetor* contar_remetente_destinatario(vetor *vrem, vetor *vdest)
{
    if (vrem ==NULL || vdest==NULL)
    {
        return NULL;
    }
    vetor *pessoas= vetor_novo();
    int n_pes_max=vrem->tamanho+vdest->tamanho;
    int cartas[n_pes_max];
    if (pessoas==NULL)
    {
        vetor_apaga(pessoas);
        return NULL;
    }
    char nome[120];
    int i=0, pesq, pos=0;
    for (i = 0; i < vrem->tamanho; i++)
    {
        strcpy(nome, vetor_elemento(vrem, i));
        pesq = vetor_pesquisa(pessoas, nome);
        if (pesq ==-1)
        {
            pos= vetor_insere(pessoas, nome, -1);
            if(pos == -1)
            {
                vetor_apaga(pessoas);
                return NULL;
            }
            cartas[pessoas->tamanho-1]=1;
        }
        else 
            cartas[pesq]++;
    }
    for (i = 0; i < vdest->tamanho; i++)
    {
        strcpy(nome, vetor_elemento(vdest, i));
        pesq = vetor_pesquisa(pessoas, nome);
        if (pesq ==-1)
        {
            pos=vetor_insere(pessoas, nome, -1);
            if(pos == -1)
            {
                vetor_apaga(pessoas);
                return NULL;
            }
            cartas[pessoas->tamanho-1]=1;
        }
        else 
            cartas[pesq]++;
    }
    for (int i = 0; i < pessoas->tamanho; i++)
    {
        printf("%s : %d cartas\n", vetor_elemento(pessoas, i), cartas[i]);
    }
    
		return pessoas;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256
void lerParaVetores(FILE *ficheiro, vetor *vrem, vetor *vdest, vetor *vcp_dest);
int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor *vrem;
	vetor *vdest;
	vetor *vcp_dest;
	vrem = NULL;
	vdest = NULL;
	vcp_dest = NULL;

	fin = fopen("correspondencia.txt", "r");
	if (fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_remetente_destinatario(vrem, vdest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else
	{
		printf("\nNumero de pessoas distintas: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);

	return 0;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/
void lerParaVetores(FILE *ficheiro, vetor *vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL)
		return;

	while (fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}