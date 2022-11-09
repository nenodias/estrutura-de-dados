// #include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CONTAS 5
#define MAX_PROCESS 5
#define MAX_BUFFER 80
#define PORT 8080
#define SA struct sockaddr

struct TServidor
{
    int sockfd;
    struct sockaddr_in socket;
};
typedef struct TServidor TServidor;

struct TConexao
{
    int sockfd;
    int connfd;
    struct sockaddr_in *cli;
};
typedef struct TConexao TConexao;

// SERVIDOR
int init_server(TServidor *servidor)
{
    // socket create and verification
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }
    bzero(&servidor->socket, sizeof(struct sockaddr_in));

    // assign IP, PORT
    servidor->socket.sin_family = AF_INET;
    servidor->socket.sin_addr.s_addr = htonl(INADDR_ANY);
    servidor->socket.sin_port = htons(PORT);
    servidor->sockfd = sockfd;
    return sockfd;
}

void binding(TServidor *servidor)
{
    // Binding newly created socket to given IP and verification
    int len = sizeof(struct sockaddr_in);
    int bind_return = bind(servidor->sockfd, (SA *)&servidor->socket, len);
    if (bind_return != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
}

void listening(TServidor *servidor)
{
    // Now server is ready to listen and verification
    if ((listen(servidor->sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
}

int accept_connections(TConexao *servidor)
{
    int len = sizeof(struct sockaddr_in);
    // Accept the data packet from client and verification
    int connfd = accept(servidor->sockfd, (SA *)servidor->cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    {
        printf("server acccept the client...\n");
    }
    servidor->connfd = connfd;
    return connfd;
}

void deal_connections(TConexao *servidor)
{
    accept_connections(servidor);
    process(servidor->connfd);
    printf("Finalizou conexao %d\n", servidor->connfd);
}

// BUSINESS

struct TConta
{
    int numero;
    char nome[50];
    float valor;
};
typedef struct TConta TConta;

struct TRetorno
{
    int operacao;
    char mensagem[80];
};
typedef struct TRetorno TRetorno;

TRetorno *saldo(TConta *conta)
{
    TRetorno *retorno = (TRetorno *)malloc(sizeof(TRetorno));
    retorno->operacao = 1;
    sprintf(retorno->mensagem, "OPERACAO: SALDO -> [%d, %s, %.2f]\n", conta->numero, conta->nome, conta->valor);
    return retorno;
}

TRetorno *sacar(TConta *conta, float valor)
{
    TRetorno *retorno = (TRetorno *)malloc(sizeof(TRetorno));
    retorno->operacao = 0;
    if (valor >= 0 && conta->valor >= valor)
    {
        float antigo = conta->valor;
        conta->valor = conta->valor - valor;
        sprintf(retorno->mensagem, "OPERACAO: SAQUE -> [%d, %s, %.2f] - %.2f = %.2f\nOPERACAO: OK", conta->numero, conta->nome, antigo, valor, conta->valor);
        retorno->operacao = 1;
        return retorno;
    }
    else
    {
        sprintf(retorno->mensagem, "OPERACAO: SAQUE -> [%d, %s, %.2f] - %.2f\nOPERACAO: NEGADA", conta->numero, conta->nome, conta->valor, valor);
        return retorno;
    }
}

TRetorno *depositar(TConta *conta, float valor)
{
    TRetorno *retorno = (TRetorno *)malloc(sizeof(TRetorno));
    retorno->operacao = 0;
    if (valor >= 0)
    {
        float antigo = conta->valor;
        conta->valor = conta->valor + valor;
        sprintf(retorno->mensagem, "OPERACAO: DEPOSITO -> [%d, %s, %.2f] + %.2f = %.2f\nOPERACAO: OK", conta->numero, conta->nome, antigo, valor, conta->valor);
        retorno->operacao = 1;
        return retorno;
    }
    else
    {
        sprintf(retorno->mensagem, "OPERACAO: DEPOSITO -> [%d, %s, %.2f] - %.2f\nOPERACAO: NEGADA", conta->numero, conta->nome, conta->valor, valor);
        return retorno;
    }
    return 0;
}

TConta contas[MAX_CONTAS] = {
    {1, "Cliente 1\0", 100},
    {2, "Cliente 2\0", 150},
    {3, "Cliente 3\0", 200},
    {4, "Cliente 4\0", 250},
    {5, "Cliente 5\0", 0},
};

// MUTEX
pthread_mutex_t mutex_conta;

// PROCESS

void process(int sockfd)
{
    char buff[MAX_BUFFER];
    int n;

    // Limpando o buffer
    bzero(buff, MAX_BUFFER);

    // lendo mensagem recebida do cliente/usuario
    read(sockfd, buff, sizeof(buff));

    int conta;
    char operacao;
    float valor;

    // lendo valores para as variaveis
    sscanf(buff, "%d,%c,%f\n", &conta, &operacao, &valor);
    // Exibindo os valores recuperados
    printf("Conta: %i\nOperação: %c\nValor: %.2f\n", conta, operacao, valor);
    if (conta >= 0 && conta < MAX_CONTAS)
    {
        TRetorno *ret;
        // Fazendo lock para evitar operacoes concorrentes e causa um estado invalido
        pthread_mutex_lock(&mutex_conta);

        // Recuperando a conta pelo indice
        TConta tconta = contas[conta];
        if (operacao == 'S')
        {
            ret = sacar(&tconta, valor);
        }
        else if (operacao == 'D')
        {
            ret = depositar(&tconta, valor);
        }
        else
        {
            // Tratando o possivel caso de uma operacao invalida ser recebida pelo cliente
            ret = (TRetorno *)malloc(sizeof(TRetorno));
            sprintf(ret->mensagem, "Operacao desconhecida\n");
        }

        // Liberando o lock
        pthread_mutex_unlock(&mutex_conta);

        // Exibindo a mensagem de retorno que sera enviada para o cliente
        printf(ret->mensagem);
        printf("\n");
        // Copiando o retorno para o buffer
        strcpy(buff, ret->mensagem);

        // Enviando a resposta para o cliente
        write(sockfd, buff, sizeof(buff));

        // Limpando o buffer
        bzero(buff, MAX_BUFFER);
    }
    else
    {
        // Copiando o retorno para o buffer
        strcpy(buff, "Conta invalida\0");

        // Enviando a resposta para o cliente
        write(sockfd, buff, sizeof(buff));

        // Limpando o buffer
        bzero(buff, MAX_BUFFER);
    }
}

int main()
{
    // SERVER
    int connfd[MAX_PROCESS];
    struct sockaddr_in server, cli[5];
    TServidor *servidor = (TServidor *)malloc(sizeof(TServidor));
    servidor->sockfd = 0;
    TConexao *conexoes[MAX_PROCESS] = {NULL, NULL, NULL, NULL, NULL};

    init_server(servidor);
    binding(servidor);
    listening(servidor);

    pthread_t workers[MAX_PROCESS];
    pthread_mutex_init(&mutex_conta, NULL);

    while (1)
    {
        for (int i = 0; i < MAX_PROCESS; i++)
        {
            printf("Criando conexao %d\n", i);
            conexoes[i] = (TConexao *)malloc(sizeof(TConexao));
            conexoes[i]->connfd = 0;
            conexoes[i]->sockfd = servidor->sockfd;
            conexoes[i]->cli = &cli[i];
            printf("Criando thread conexao %d\n", conexoes[i]->connfd);
            pthread_create(&workers[i], NULL, deal_connections, (void *)conexoes[i]);
        }
        for (int i = 0; i < MAX_PROCESS; i++)
        {
            printf("Join thread %d\n", i);
            if (workers[i] != NULL)
            {
                pthread_join(workers[i], NULL);
                printf("Join conexao %d\n", i);
                free(conexoes[i]);
                conexoes[i] = NULL;
            }
        }
    }
    // After chatting close the socket
    close(servidor->sockfd);
    return 0;
}
