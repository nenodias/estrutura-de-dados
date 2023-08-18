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
    arquivo = fopen ("dados.txt", "wb");
    if (arquivo == NULL) {
      fprintf(stderr, "Error to open the file");
      exit (1);
    }
    TPessoa p1 = TPessoa{1, "Usuário", 20};
    fwrite (&p1, sizeof(TPessoa), 1, arquivo);
    if(fwrite != 0){
      printf("Contents to file written successfully !");
    }else{
      printf("Error writing file !");
    }
    fclose (arquivo);
    printf("Hello world");
    return 0;
}