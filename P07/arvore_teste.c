#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "bst.h"

int main()
{
    // alinea a)
    arvore_bst *arvore = bst_nova();
    if (arvore == NULL)
    {
        return 0;
    }
    bst_insere(arvore, "G");
    bst_insere(arvore, "C");
    bst_insere(arvore, "A");
    bst_insere(arvore, "F");
    bst_insere(arvore, "L");
    bst_insere(arvore, "J");
    bst_insere(arvore, "V");
    bst_insere(arvore, "M");
    bst_insere(arvore, "N");
    bst_insere(arvore, "O");

    // alinea b)
    printf("A altura da arvore é %d e a raiz é %s \n", bst_altura(arvore->raiz), arvore->raiz->str);
    
    
}