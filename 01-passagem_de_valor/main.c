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

void exibeVetor(int vetor[])
{
    printf("[");
    // Pegando o tamanho do array do tipo int
    int size = sizeof(vetor) / sizeof(int);
    for (int i = 0; i <= size; i++)
    {
        printf("%d,", vetor[i]);
    }
    printf("]\n");
}

void passagemDeArrayPorReferencia(int vetor[])
{
    exibeVetor(vetor);
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
    int vetor[] = {10, 20, 30};
    printf("Antes: passagemDeArrayPorReferencia\n");
    passagemDeArrayPorReferencia(vetor);
    printf("Depois: passagemDeArrayPorReferencia\n");
    exibeVetor(vetor);
    printf("Antes: passagemDeValorPorReferencia\n");
    passagemDeValorPorReferencia(vetor);
    exibeVetor(vetor);
    return 0;
}