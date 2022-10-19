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
    int vetor[] = {10, 3, 4, 2, 1, 5};
    //Pegando o tamanho do array, só é possível onde o array é definido
    size_t tamanho = sizeof(vetor)/sizeof(vetor[0]);
    exibeVetor(vetor, tamanho);
    selection_sort(vetor, tamanho);
    exibeVetor(vetor, tamanho);
    return 0;
}