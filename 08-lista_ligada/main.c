#include <stdio.h>
#include <stdlib.h>

struct TLista
{
    struct TLista *proximo;
    int valor;
};
typedef struct TLista TLista;

TLista *criarLista()
{
    TLista *registro = (struct TLista *)malloc(sizeof(struct TLista));
    registro->proximo = NULL;
    registro->valor = 0;
    return registro;
}

TLista *criarListaComValor(int valor)
{
    TLista *registro = criarLista();
    registro->valor = valor;
    return registro;
}

TLista *buscarPosicao(TLista *primeiro, int posicao){
    if (primeiro != NULL)
    {
        printf("Lista[");
        int contador = 0;
        TLista *registro = primeiro;
        while (1)
        {
            if (registro->proximo == NULL)
            {
                registro = NULL;
                break;
            }
            else
            {
                registro = registro->proximo;
            }
            if(contador == posicao){
                break;
            }
            contador++;
        };
        return registro;
    }
    return NULL;
}

void exibirLista(TLista *primeiro)
{
    if (primeiro != NULL)
    {
        printf("Lista[");
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

TLista * adicionar(TLista *primeiro, int posicao, int valor)
{
    TLista *novo = criarListaComValor(valor);
    if (primeiro != NULL)
    {
        if(posicao == 0){
            novo->proximo = primeiro;
            return novo;
        }else if(posicao > 0) {
            TLista *atual = buscarPosicao(primeiro, posicao - 1);
            TLista *registro = buscarPosicao(primeiro, posicao);
            atual->proximo = novo;
            novo->proximo = registro;
        }
    }
    return primeiro;
}

TLista *remover(TLista *primeiro, int posicao)
{
    if (primeiro != NULL)
    {
        if(posicao == 0){
            TLista *proximo = primeiro->proximo;    
            free(primeiro);
            return proximo;
        } else if(posicao > 0) {
            // Pega o registro da posicao anterior
            TLista *atual = buscarPosicao(primeiro, posicao -1);
            // Pega o registro da posicao
            TLista *registro = atual->proximo;
            // Faz o anterior apontar para o proximo registro depois do que sera removido
            atual->proximo = registro->proximo;
            registro->proximo = NULL;
            free(registro);
            return primeiro;
        }
        return primeiro;
    }
    return NULL;
}

int main()
{
    // Para poder controlar a Lista precisamos de um ponteiro com o primeiro registro
    TLista *primeiro = criarListaComValor(5);
    primeiro = adicionar(primeiro, 0, 3);
    exibirLista(primeiro);
    primeiro = adicionar(primeiro, 0, 1);
    exibirLista(primeiro);
    primeiro = adicionar(primeiro, 1, 4);
    exibirLista(primeiro);
    primeiro = adicionar(primeiro, 1, 2);
    exibirLista(primeiro);

    primeiro = remover(primeiro, 2);
    exibirLista(primeiro);
    primeiro = remover(primeiro, 1);
    exibirLista(primeiro);
    primeiro = remover(primeiro, 0);
    exibirLista(primeiro);
    primeiro = remover(primeiro, 0);
    exibirLista(primeiro);
    primeiro = remover(primeiro, 0);
    exibirLista(primeiro);

    return 0;
}