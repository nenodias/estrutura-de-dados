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

void trocar(int vetor[], int i, int j)
{
    int temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

int dividir(int vetor[], int inicio, int fim)
{
    int pivo, left, right = fim;
    left = inicio + 1;
    pivo = vetor[inicio];

    while (left <= right)
    {
        /* Vai correr o vetor ate que ultrapasse o outro ponteiro
          ou ate que o elemento em questão seja menor que o pivô. */
        while (left <= right && vetor[left] <= pivo)
        {
            left++;
        }

        /* Vai correr o vetor ate que ultrapasse o outro ponteiro
          que o elemento em questão seja maior que o pivô. */
        while (right >= left && vetor[right] > pivo)
        {
            right--;
        }

        /* Caso os ponteiros ainda nao tenham se cruzado, significa que valores
          menores e maiores que o pivô foram localizados em ambos os lados.
          Trocar estes elementos de lado. */
        if (left < right)
        {
            trocar(vetor, right, left);
            left++;
            right--;
        }
    }

    trocar(vetor, inicio, right);
    return right;
}

void quick_sort_recursivo(int vetor[], int inicio, int fim)
{
    if (fim > inicio)
    {
        // Chamada da rotina que ira dividir o vetor em 3 partes.
        int index_pivo = dividir(vetor, inicio, fim);
        /* Chamada recursiva para redivisao do vetor de elementos menores
          que o pivô. */
        quick_sort_recursivo(vetor, inicio, index_pivo - 1);
        /* Chamada recursiva para redivisao do vetor de elementos maiores
          que o pivô. */
        quick_sort_recursivo(vetor, index_pivo + 1, fim);
    }
}

void quick_sort(int vetor[], int tamanho)
{
    quick_sort_recursivo(vetor, 0, tamanho);
}

int main()
{
    int vetor[] = {24, 66, 87, 43, 11, 27, 4, 2, 7, 8, 4, 5,
     12, 53, 42, 22, 1, 5, 9, 13, 16, 23, 13, 7, 55, 67,
     92, 22, 33, 27, 19};
    // Pegando o tamanho do array, só é possível onde o array é definido
    size_t tamanho = sizeof(vetor) / sizeof(vetor[0]);
    exibeVetor(vetor, tamanho);
    quick_sort(vetor, tamanho);
    exibeVetor(vetor, tamanho);
    return 0;
}