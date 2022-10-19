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

void bubble_sort(int vetor[], int tamanho)
{
    int aux = 0;
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < (tamanho - i) -1; j++)
        {
            if (vetor[j] < vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int main()
{
    int vetor[] = {10, 3, 4, 2, 1, 5};
    //Pegando o tamanho do array, só é possível onde o array é definido
    size_t tamanho = sizeof(vetor)/sizeof(vetor[0]);
    exibeVetor(vetor, tamanho);
    bubble_sort(vetor, tamanho);
    exibeVetor(vetor, tamanho);
    return 0;
}