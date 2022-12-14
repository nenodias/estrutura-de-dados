#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "soma.h"

int main()
{
    setlocale(LC_ALL,"");
    char opcao = '\n';
    int a, b;
    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);
    printf("Qual operação[+,-]:");
    //Resolvendo bug com buffer do teclado
    while(opcao == '\n'){
        scanf("%c\n", &opcao);
    }
    if(opcao == '+' || opcao == '-'){
        // Definindo um ponteiro para a função que retorno int e recebe dois ints
        int (*funcao_operacao)(int, int) = NULL;
        if(opcao == '+') {
            // Pegando o endereco da funcao
            funcao_operacao = &somar;
        } else if(opcao == '-'){
            // Pegando o endereco da funcao
            funcao_operacao = &subtrair;
        }
        int resultado = (*funcao_operacao)(a, b);
        printf("Resultado da operação %d %c %d = %d", a, opcao, b, resultado);
    } else {
        printf("Operação %c desconhecida.", opcao);
    }
    printf("\nFim do programa!!!");
    return 0;
}
