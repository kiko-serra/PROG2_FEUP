#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem *armazem_novo(int comprimento, int altura)
{
    if (comprimento < 1 || altura < 1)
    {
        return NULL;
    }
    //cria novo armazem
    armazem *arma = (armazem *)malloc(sizeof(armazem));
    if (arma == NULL)
    {
        return NULL;
    }
    //passa os parametros da funcao para dentro do armazem
    arma->altura = altura;
    arma->comprimento = comprimento;
    arma->contentores = fila_nova();

    return arma;
}

/* alinea c) */
int armazem_vazio(armazem *armz)
{
    if (armz == NULL || fila_tamanho(armz->contentores) == 0)
    {
        return 1;
    }
    return 0; //nao esta vazio
}

/* alinea d) */
int armazem_cheio(armazem *armz)
{ /* devolve nao cheio */
    if (armz == NULL)
    {
        return 0;
    }
    if (armz->comprimento == armz->contentores->tamanho)
    {
        if (armz->altura == fila_back(armz->contentores)->tamanho)
        {
            return 1; // está cheio
        }
    }
    return 0;
}

/* alinea e) */
//caso 1-> ultima pilha cheia mas fila nao cheia -> done
//caso 2-> ultima pilha nao cheia -> done
//caso 3->armazem cheio retornar 0-> done
/*  int armazenar_contentor(armazem *armz, contentor *contr)
{
    
    //caso3 done
    if (armz == NULL || contr == NULL || armazem_cheio(armz))
    {
        return 0;
    }
    pilha *aux = fila_back(armz->contentores);

    //caso1 done
    if ((aux->tamanho < armz->altura) && aux)
    {
        pilha_push(aux, contr);
    }
    else
    {
        aux=pilha_nova();
        if (aux==NULL)
        {
            return 0;
        }
        
        fila_push(armz->contentores, aux);
        pilha_push(aux, contr);
    }
    //caso 2 done
    
    return 1;
}  */
int armazenar_contentor(armazem *armz, contentor *contr)
{
	/* devolve nao ha' espaco */
	if (armz == NULL || contr == NULL||armazem_cheio(armz))
	{
		return 0;
	}
	pilha *back = fila_back(armz->contentores);  // última pilha da fila
    if(back && (back->tamanho < armz->altura))  // se pilha criada e com espaço livre
        pilha_push(back, contr);  // adiciona novo contentor
    else  // se pilha não criada ou cheia
    {
        back = pilha_nova();  // cria a pilha
        if(!back)
            return 0;
        fila_push(armz->contentores, back);  // adiciona-a à fila
        pilha_push(back, contr);  // adiciona novo contentor à nova pilha
    }
	return 1;
}

/* alinea f) */
//retirar contentor pilha_top
//pilha_apaga quando pilha_tamanho==0
//caso 1 -> retirar ultimo contentor da pilha
//caso 2 -> retirar contentor da pilha sem ser ultimo
contentor *expedir_contentor(armazem *armz)
{
    if (armz == NULL || armazem_vazio(armz)==1)
    {
        return NULL;
    }
    contentor *aux = contentor_novo(pilha_top(fila_front(armz->contentores))->destino, pilha_top(fila_front(armz->contentores))->valor);
    if (aux == NULL)
    {
        return NULL;
    }
    //caso 1
    if (pilha_tamanho(fila_front(armz->contentores)) == 1)
    {
        fila_pop(armz->contentores);
        return aux;
    }
    //caso 2

    pilha_pop(fila_front(armz->contentores));

    return aux;
}