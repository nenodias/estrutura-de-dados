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

void exibirFila(TFila *primeiro)
{
    if (primeiro != NULL)
    {
        printf("Fila[");
        while (1)
        {
            printf("%d,", primeiro->valor);
            if (primeiro->proximo == NULL)
            {
                break;
            }
            else
            {
                primeiro = primeiro->proximo;
            }
        };
        printf("]\n");
    }
    else
    {
        printf("NULL\n");
    }
}

TFila *enfileirar(TFila *ultimo, int valor)
{
    // Ao enfileirar, o valor adicionado vai para o ultimo da fila
    TFila *novo = criarFilaComValor(valor);
    if (ultimo != NULL)
    {
        // Se já existia alguém no final da fila, ele vai apontar para o novo, que será o ultimo da fila
        ultimo->proximo = novo;
    }
    return novo;
}

TFila *desenfileirar(TFila *primeiro)
{
    if (primeiro != NULL)
    {
        // Para desenfileirar recebemos o primeiro/começo da fila
        TFila *proximo = primeiro->proximo;
        primeiro->proximo = NULL;
        free(primeiro);
        // Retornamos o próximo da fila que estava em segundo lugar, e ele passa a ser o primeiro
        return proximo;
    }
    return NULL;
}

int main()
{
    // Para poder controlar a fila precisamos de um ponteiro com o primeiro e o ultimo da fila
    TFila *primeiro = criarFilaComValor(1);
    // No início o primeiro da fila tambem e o ultimo
    TFila *ultimo = primeiro;
    ultimo = enfileirar(ultimo, 2);
    exibirFila(primeiro);
    ultimo = enfileirar(ultimo, 3);
    exibirFila(primeiro);
    ultimo = enfileirar(ultimo, 4);
    exibirFila(primeiro);
    ultimo = enfileirar(ultimo, 5);
    exibirFila(primeiro);

    primeiro = desenfileirar(primeiro);
    exibirFila(primeiro);
    primeiro = desenfileirar(primeiro);
    exibirFila(primeiro);
    primeiro = desenfileirar(primeiro);
    exibirFila(primeiro);
    primeiro = desenfileirar(primeiro);
    exibirFila(primeiro);
    primeiro = desenfileirar(primeiro);
    exibirFila(primeiro);

    return 0;
}