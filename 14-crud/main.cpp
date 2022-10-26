#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <iostream>

#define TRUE 1
#define FALSE 0

using namespace std;

struct Pessoa
{
    int codigo;
    char nome[100];
    int idade;
};

FILE *arquivo = NULL;

/** ARQUIVO */
void criar_arquivo();
void fechar_arquivo();

/** INTERFACE */
void menu();
void executar(char tecla);

/** CRUD */
void inserir();
void pesquisar();

int main()
{
    // Aceitando Acentos
    setlocale(LC_ALL, "Portuguese");
    criar_arquivo();
    menu();
    fechar_arquivo();
    return 0;
}

void criar_arquivo()
{
    // Acessando variável estática arquivo --Poderia ser sem os dois pontos,
    // porém utilizando os dois pontos estou explicitamente pegando a variável global
    ::arquivo = fopen("arquivo.dat", "w+b");

    int tamanho = sizeof(struct Pessoa);
    FILE *arquivo_principal = fopen("dados.dat", "r+b");
    if (arquivo_principal != NULL)
    {
        struct Pessoa *entidade = (struct Pessoa *)malloc(tamanho);

        fseek(arquivo_principal, 0, SEEK_SET);

        do
        {
            fread(entidade, tamanho, 1, arquivo_principal);
            fwrite(entidade, tamanho, 1, arquivo);
        } while (!feof(arquivo_principal));

        fclose(arquivo_principal);
    }
}

void fechar_arquivo()
{
    FILE *arquivo_principal = fopen("dados.dat", "w+b");

    struct Pessoa *entidade = (struct Pessoa *)malloc(sizeof(struct Pessoa));

    fseek(arquivo, 0, SEEK_SET);
    do
    {
        fread(entidade, sizeof(struct Pessoa), 1, arquivo);
        fwrite(entidade, sizeof(struct Pessoa), 1, arquivo_principal);
    } while (!feof(arquivo));

    fclose(arquivo_principal);
    fclose(arquivo);
}

void menu()
{
    char tecla;
    while (tecla != 'Q' && tecla != 'q')
    {
        cout << "1 - Para Inserir um registro;" << endl;
        cout << "2 - Para Pesquisar um registro;" << endl;
        cout << "3 - Para Remover um registro;" << endl;
        cout << "4 - Para Mostrar todos os registros;" << endl;
        cout << "Q/q - Para Sair;" << endl;
        cout << " O que deseja fazer? ";
        cin >> tecla;
        if (tecla != 'Q' && tecla != 'q')
        {
            executar(tecla);
        }
    }
}

void executar(char tecla)
{
    if (tecla == '1')
    {
        inserir();
    }
    else if (tecla == '2')
    {
        pesquisar();
    }
}

void inserir()
{
    struct Pessoa *entidade = (struct Pessoa *)malloc(sizeof(struct Pessoa));
    int codigo;
    cout << "Digite o codigo (Maior que zero):" << endl;
    cin >> entidade->codigo;
    cout << "Digite o nome:" << endl;
    cin >> entidade->nome;
    cout << "Digite a idade:" << endl;
    cin >> entidade->idade;
    fseek(arquivo, 0, SEEK_END);
    fwrite(entidade, sizeof(struct Pessoa), 1, arquivo);
}
/**
SEEK_SET - Parte do início do arquivo e avança <n> bytes
SEEK_END - Parte do final do arquivo e retrocede <n> bytes
SEEK_CUR - Parte do local atual e avança <n> bytes
*/
void pesquisar()
{
    struct Pessoa *entidade = (struct Pessoa *)malloc(sizeof(struct Pessoa));
    int codigo;
    cout << "Digite o codigo:" << endl;
    cin >> codigo;
    fseek(arquivo, 0, SEEK_SET);
    do
    {
        fread(entidade, sizeof(struct Pessoa), 1, arquivo);
        if (codigo == entidade->codigo)
        {
            break;
        }
    } while (!feof(arquivo));

    if (entidade != NULL && codigo == entidade->codigo)
    {
        cout << "{" << endl;
        cout << "Codigo: " << entidade->codigo << "," << endl;
        cout << "Nome: " << entidade->nome << "," << endl;
        cout << "Idade: " << entidade->idade << endl;
        cout << "}" << endl;
    }
    else
    {
        cout << "Registro não encontrado";
    }
    cout << endl;
}