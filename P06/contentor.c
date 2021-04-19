#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "contentor.h"

/* alinea a) */
/**
 *  \brief cria um novo contentor
 *  \param dest destino do contentor
 *  \param val valor das mercadorias no contentor
 *  \return apontador para o contentor; NULL se erro
 */
contentor* contentor_novo(char* dest, float val)
{
	if (dest==NULL || val<0)
	{
		return NULL;
	}
	
	contentor *cont = (contentor*) malloc(sizeof(contentor));
	if(cont == NULL) 
		return NULL;

	cont->destino = (char *)malloc((strlen(dest) + 1) * sizeof(char));
	strcpy(cont->destino, dest);
	
	cont->valor = val;
	return cont;
}

/**
 *  \brief apaga contentor (liberta memoria correspondente)
 *  \param contr apontador para o contentor
 *  \remark se contr = NULL retorna sem fazer nada
 */
void contentor_apaga(contentor* contr)
{
	if (contr==NULL)
	{
		return;
	}
	free(contr->destino);
	free(contr);
	
}

/**
 *  \brief imprime dados do contentor
 *  \param contr apontador para o contentor
 */
void contentor_imprime(contentor* contr)  {
	if (contr == NULL)
		printf("Contentor nulo\n");
	else
		printf("Destino: %s, valor da carga: %.2f K Euros\n", contr->destino, contr->valor);
}
