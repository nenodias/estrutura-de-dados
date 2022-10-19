#include <stdio.h>
#include <stdlib.h>

void passagemDeValorPorCopia(int valor)
{
    printf("passagemDeValorPorCopia\n");
    printf("Antes: %d\n", valor);
    valor = 2;
    printf("Depois: %d\n", valor);
}

void passagemDeValorPorReferencia(int *valor)
{
    printf("passagemDeValorPorReferencia\n");
    printf("Antes: %d\n", *valor);
    *valor = 2;
    printf("Depois: %d\n", *valor);
}

void exibeVetor(int vetor[], int tamanho)
{
    printf("[");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d,", vetor[i]);
    }
    printf("]\n");
}

void passagemDeArrayPorReferencia(int vetor[], int tamanho)
{
    exibeVetor(vetor, tamanho);
    vetor[0] = 0;
}

int main()
{
    int valor = 10;
    // Ao passar o valor por cópia a variável NÃO é alterado fora da função
    passagemDeValorPorCopia(valor);
    printf("Main: %d\n", valor);
    int *ponteiro_valor = &valor;
    // Ao passar o valor por referência a variável é alterado fora da função
    passagemDeValorPorReferencia(ponteiro_valor);
    printf("Main: %d\n", valor);

    // Exemplo de que todo vetor/array é passado por referência
    int vetor[] = {10, 20, 30, 40};
    //Pegando o tamanho do array, só é possível onde o array é definido
    size_t tamanho = sizeof(vetor)/sizeof(vetor[0]);
    printf("Antes: passagemDeArrayPorReferencia\n");
    passagemDeArrayPorReferencia(vetor, tamanho);
    printf("Depois: passagemDeArrayPorReferencia\n");
    exibeVetor(vetor, tamanho);
    printf("Antes: passagemDeValorPorReferencia\n");
    passagemDeValorPorReferencia(vetor);
    exibeVetor(vetor, tamanho);
    return 0;
}