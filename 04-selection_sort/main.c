#include <stdio.h>
#include <stdlib.h>

void exibeVetor(int vetor[], int tamanho)
{
    printf("[");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d,", vetor[i]);
    }
    printf("]\n");
}

void selection_sort(int vetor[], int tamanho)
{
    int aux = 0;
    for (int i = 0; i < tamanho; i++)
    {
        int i_menor = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            if (vetor[j] < vetor[i_menor])
            {
                i_menor = j;
            }
        }
        aux = vetor[i];
        vetor[i] = vetor[i_menor];
        vetor[i_menor] = aux;
    }
}

int main()
{
    int vetor[] = {24, 66, 87, 43, 11, 27, 4, 2, 7, 8, 4, 5,
     12, 53, 42, 22, 1, 5, 9, 13, 16, 23, 13, 7, 55, 67,
     92, 22, 33, 27, 19};
    // Pegando o tamanho do array, só é possível onde o array é definido
    size_t tamanho = sizeof(vetor) / sizeof(vetor[0]);
    exibeVetor(vetor, tamanho);
    selection_sort(vetor, tamanho);
    exibeVetor(vetor, tamanho);
    return 0;
}