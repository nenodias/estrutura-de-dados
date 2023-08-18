#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TPessoa{
    int id;
    char nome[100];
    int idade;
};
typedef struct TPessoa TPessoa;

int main()
{
    FILE *arquivo;
    arquivo = fopen ("dados.txt", "w");
    if (arquivo == NULL) {
      fprintf(stderr, "Error to open the file");
      exit (1);
    }
    TPessoa p1 = TPessoa{1, "Usuário", 20};
    fprintf(arquivo, "%010d", p1.id);
    fprintf(arquivo, "%-100s", p1.nome);
    fprintf(arquivo, "%010d", p1.idade);
    fclose (arquivo);
    printf("Hello world");
    return 0;
}