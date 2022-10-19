#include <stdio.h>
#include <stdlib.h>

struct TFila
{
    struct TFila *proximo;
    int valor;
};
typedef struct TFila TFila;

TFila *criarFila()
{
    TFila *registro = (struct TFila *)malloc(sizeof(struct TFila));
    registro->proximo = NULL;
    registro->valor = 0;
    return registro;
}

TFila *criarFilaComValor(int valor)
{
    TFila *registro = criarFila();
    registro->valor = valor;
    return registro;
}

void exibirFila(TFila *topo)
{
    if (topo != NULL)
    {
        printf("Fila[");
        while (1)
        {
            printf("%d,", topo->valor);
            if (topo->proximo == NULL)
            {
                break;
            }
            else
            {
                topo = topo->proximo;
            }
        };
        printf("]\n");
    }
    else
    {
        printf("NULL\n");
    }
}

TFila *enfileirar(TFila *final, int valor)
{
    TFila *novo = criarFilaComValor(valor);
    if(final != NULL){
        final->proximo = novo;
    }
    return novo;
}

TFila *desenfileirar(TFila *topo)
{
    if (topo != NULL)
    {
        TFila *proximo = topo->proximo;
        topo->proximo = NULL;
        free(topo);
        return proximo;
    }
    return NULL;
}

int main()
{
    TFila *topo = criarFilaComValor(1);
    TFila *final = topo;
    final = enfileirar(final, 2);
    exibirFila(topo);
    final = enfileirar(final, 3);
    exibirFila(topo);
    final = enfileirar(final, 4);
    exibirFila(topo);
    final = enfileirar(final, 5);
    exibirFila(topo);

    topo = desenfileirar(topo);
    exibirFila(topo);
    topo = desenfileirar(topo);
    exibirFila(topo);
    topo = desenfileirar(topo);
    exibirFila(topo);
    topo = desenfileirar(topo);
    exibirFila(topo);
    topo = desenfileirar(topo);
    exibirFila(topo);

    return 0;
}