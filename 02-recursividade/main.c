#include <stdio.h>
#include <stdlib.h>

int fatorial(int numero)
{
    // Algoritmos recursivos precisam de um termo de saída para ficar em um loop/laço infinito
    if (numero == 0 || numero == 1)
    {
        return 1;
    }
    return numero * fatorial(numero - 1);
}

int main()
{
    printf("%d", fatorial(5));
    return 0;
}