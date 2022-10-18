#include <stdio.h>
#include <stdlib.h>

struct TPilha
{
    struct TPilha *proximo;
    int valor;
};
typedef struct TPilha TPilha;

TPilha *criarPilha()
{
    TPilha *registro = (struct TPilha *)malloc(sizeof(struct TPilha));
    registro->proximo = NULL;
    registro->valor = 0;
    return registro;
}

TPilha *criarPilhaComValor(int valor)
{
    TPilha *registro = criarPilha();
    registro->valor = valor;
    return registro;
}

TPilha *empilhar(TPilha *pilha, int valor)
{
    if (pilha != NULL)
    {
        struct TPilha *topo = criarPilhaComValor(valor);
        topo->proximo = pilha;
        return topo;
    }
    return NULL;
}

TPilha *desempilhar(TPilha *pilha)
{
    if (pilha != NULL)
    {
        TPilha *proximo = pilha->proximo;
        free(pilha);
        return proximo;
    }
    return NULL;
}

void exibirPilha(TPilha *pilha)
{
    if (pilha != NULL)
    {
        printf("Pilha[");
        while (1)
        {
            printf("%d,", pilha->valor);
            if (pilha->proximo == NULL)
            {
                break;
            }
            else
            {
                pilha = pilha->proximo;
            }
        };
        printf("]\n");
    }
    else
    {
        printf("NULL\n");
    }
}

int main()
{
    TPilha *pilha = criarPilhaComValor(5);
    exibirPilha(pilha);
    pilha = empilhar(pilha, 4);
    exibirPilha(pilha);
    pilha = empilhar(pilha, 3);
    exibirPilha(pilha);
    pilha = empilhar(pilha, 2);
    exibirPilha(pilha);
    pilha = empilhar(pilha, 1);
    exibirPilha(pilha);

    pilha = desempilhar(pilha);
    exibirPilha(pilha);
    pilha = desempilhar(pilha);
    exibirPilha(pilha);
    pilha = desempilhar(pilha);
    exibirPilha(pilha);
    pilha = desempilhar(pilha);
    exibirPilha(pilha);
    pilha = desempilhar(pilha);
    exibirPilha(pilha);

    return 0;
}